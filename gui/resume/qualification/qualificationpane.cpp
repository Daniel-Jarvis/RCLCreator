#include "qualificationpane.h"
#include "ui_qualificationpane.h"

namespace rcl {
namespace gui {
namespace resume {
namespace qualification {

QualificationPane::QualificationPane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QualificationPane)
{
    ui->setupUi(this);
}

QualificationPane::~QualificationPane()
{
    delete ui;
}

QList<ResumeQualificationSection *> QualificationPane::getIncludedQualifications() const{
    QList<ResumeQualificationSection*> list;
    for(int i=0; i<ui->sectionsLayout->count(); i++){
        ResumeQualificationSection* section = qobject_cast<ResumeQualificationSection*>(ui->sectionsLayout->itemAt(i)->widget());
        if(section->isIncluded())
            list.append(section);
    }
    return list;
}

QList<ResumeQualificationSection *> QualificationPane::getQualifications() const{
    QList<ResumeQualificationSection*> list;
    for(int i=0; i<ui->sectionsLayout->count(); i++){
        list.append(qobject_cast<ResumeQualificationSection*>(ui->sectionsLayout->itemAt(i)->widget()));
    }
    return list;
}

QDomElement QualificationPane::toXml(QDomDocument &document) const{
    QDomElement sectionsRoot = document.createElement("Sections");
    auto sections = getQualifications();
    for(int i=0; i<sections.size(); i++){
        sectionsRoot.appendChild(sections.at(i)->toXml(document));
    }
    return sectionsRoot;
}

void QualificationPane::loadFromFile(QDomElement &xml){
    QDomElement sectionElement = xml.firstChildElement();
    while(!sectionElement.isNull()){
        ResumeQualificationSection* newSection = createAndAddSection();
        newSection->loadFromFile(sectionElement);
        sectionElement = sectionElement.nextSiblingElement();
    }

    for(int i=0; i<ui->sectionsLayout->count(); i++){
        qobject_cast<ResumeQualificationSection*>(ui->sectionsLayout->itemAt(i)->widget())->setShiftWidgetVisibility();
    }
}

void QualificationPane::on_addSectionBtn_clicked(){
        ResumeQualificationSection* newSection = createAndAddSection();
        newSection->setShiftWidgetVisibility();
        int prevIndex = ui->sectionsLayout->count()-2;
        if(prevIndex < 0)
            return;
        qobject_cast<ShiftableWidget*>(ui->sectionsLayout->itemAt(ui->sectionsLayout->count()-2)->widget())->setShiftWidgetVisibility();

}

ResumeQualificationSection *QualificationPane::createAndAddSection(){
        ResumeQualificationSection *newSection = new ResumeQualificationSection(this, ui->sectionsLayout);
        QPushButton* shiftUpBtn = newSection->getShiftUpButton();
        connect(shiftUpBtn, &QPushButton::clicked, this, [this, newSection](){
            newSection->shiftWidgetUp();
        });
        QPushButton* shiftDownBtn = newSection->getShiftDownButton();
        connect(shiftDownBtn, &QPushButton::clicked, this, [this, newSection](){
            newSection->shiftWidgetDown();
        });
        ui->sectionsLayout->addWidget(newSection);
        return newSection;
}


} // namespace qualification
} // namespace resume
} // namespace gui
} // namespace rcl
