#include "resumequalificationsection.h"
#include "ui_resumequalificationsection.h"
#include "resumequalificationsubsection.h"

#include <QDebug>
#include <QMenu>
#include <QTimer>

namespace rcl::gui::resume::qualification {

ResumeQualificationSection::ResumeQualificationSection(QWidget *parent, QVBoxLayout* owningLayout)
    : ShiftableWidget(parent, owningLayout)
    , ui(new Ui::ResumeQualificationSection){
    ui->setupUi(this);
    setShiftWidgetVisibility();
    collapsed = false;
}

ResumeQualificationSection::~ResumeQualificationSection(){
    delete ui;
}

QString ResumeQualificationSection::getSectionTitle() const{
    return ui->sectionTitleLineEdit->displayText();
}

QList<ResumeQualificationSubsection *> ResumeQualificationSection::getIncludedSubsections() const{
    QList<ResumeQualificationSubsection*> list;
    for(int i=0; i<ui->subsectionsLayout->count(); i++){
        ResumeQualificationSubsection* subsection = qobject_cast<ResumeQualificationSubsection*>(ui->subsectionsLayout->itemAt(i)->widget());
        if(subsection->isIncluded())
            list.append(subsection);
    }
    return list;
}

QList<ResumeQualificationSubsection *> ResumeQualificationSection::getSubsections() const{

    QList<ResumeQualificationSubsection*> list;
    for(int i=0; i<ui->subsectionsLayout->count(); i++){
        list.append(qobject_cast<ResumeQualificationSubsection*>(ui->subsectionsLayout->itemAt(i)->widget()));
    }
    return list;
}

QPushButton *ResumeQualificationSection::getShiftUpButton() const{
    return ui->shiftUpBtn;
}

QPushButton *ResumeQualificationSection::getShiftDownButton() const{
    return ui->shiftDownBtn;
}

QDomElement ResumeQualificationSection::toXml(QDomDocument &document) const{
    QDomElement subsectionElement = document.createElement("Section");
    QDomElement titleElement = document.createElement("Title");
    titleElement.appendChild(document.createTextNode(getSectionTitle()));
    subsectionElement.appendChild(titleElement);

    auto subsections = getSubsections();
    for(int i=0; i<subsections.size(); i++){
        subsectionElement.appendChild(subsections.at(i)->toXml(document));
    }

    return subsectionElement;
}

void ResumeQualificationSection::loadFromFile(QDomElement &element){
    QDomElement titleElement = element.firstChildElement();
    ui->sectionTitleLineEdit->setText(titleElement.text());

    QDomElement subsectionElement = titleElement.nextSiblingElement();
    while(!subsectionElement.isNull()){
        ResumeQualificationSubsection* newSubsection = createAndAddSubsection();
        newSubsection->loadFromFile(subsectionElement);
        subsectionElement = subsectionElement.nextSiblingElement();
    }

    for(int i=0; i<ui->subsectionsLayout->count(); i++){
        qobject_cast<ResumeQualificationSubsection*>(ui->subsectionsLayout->itemAt(i)->widget())->setShiftWidgetVisibility();
    }
}

QCheckBox* ResumeQualificationSection::getIncludeSectionBox() const{
    return ui->includeSectionCheckBox;
}

bool ResumeQualificationSection::isIncluded() const{
    return ui->includeSectionCheckBox->isChecked();
}

void ResumeQualificationSection::on_addSubsectionBtn_clicked(){
    ResumeQualificationSubsection* newSubsection = createAndAddSubsection();
    newSubsection->setShiftWidgetVisibility();
    int prevIndex = ui->subsectionsLayout->count()-2;
    if(prevIndex < 0)
        return;
    qobject_cast<ShiftableWidget*>(ui->subsectionsLayout->itemAt(prevIndex)->widget())->setShiftWidgetVisibility();
}

void ResumeQualificationSection::on_includeSectionCheckBox_checkStateChanged(const Qt::CheckState &state){
    if(state == Qt::CheckState::Unchecked){
        for(int i=0; i<ui->subsectionsLayout->count(); i++){
            ResumeQualificationSubsection* subsection = qobject_cast<ResumeQualificationSubsection*>(ui->subsectionsLayout->itemAt(i)->widget());
            subsection->setIncluded(false);
        }
    }
}

ResumeQualificationSubsection *ResumeQualificationSection::createAndAddSubsection(){
    ResumeQualificationSubsection* newSubsection = new ResumeQualificationSubsection(this, ui->subsectionsLayout);

    QPushButton* shiftUpBtn = newSubsection->getShiftUpButton();
    connect(shiftUpBtn, &QPushButton::clicked, this, [this, newSubsection](){
        newSubsection->shiftWidgetUp();
    });
    QPushButton* shiftDownBtn = newSubsection->getShiftDownButton();
    connect(shiftDownBtn, &QPushButton::clicked, this, [this, newSubsection](){
        newSubsection->shiftWidgetDown();
    });

    QCheckBox* includeBox = newSubsection->getIncludedBox();
    connect(includeBox, &QCheckBox::checkStateChanged, this, [this](Qt::CheckState state){
        if(state == Qt::CheckState::Checked && ui->includeSectionCheckBox->checkState() != Qt::CheckState::Checked){
            ui->includeSectionCheckBox->setChecked(true);
        }
    });

    ui->subsectionsLayout->addWidget(newSubsection);
    return newSubsection;
}

void ResumeQualificationSection::on_collapseBtn_clicked(){
    collapsed = !collapsed;
    QString collapseBtnText = collapsed ? ">" : "v";
    ui->collapseBtn->setText(collapseBtnText);

    for(int i=0; i<ui->subsectionsLayout->count(); i++){
        ui->subsectionsLayout->itemAt(i)->widget()->setVisible(!collapsed);
    }
    ui->addSubsectionBtn->setVisible(!collapsed);
}




}
