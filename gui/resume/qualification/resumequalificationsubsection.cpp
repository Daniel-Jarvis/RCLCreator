#include "resumequalificationsubsection.h"
#include "ui_resumequalificationsubsection.h"
#include "../gui_utils.h"

#include <QTextBlock>
#include <QMenu>

namespace rcl::gui::resume::qualification {
ResumeQualificationSubsection::ResumeQualificationSubsection(QWidget *parent, QVBoxLayout* owningLayout)
    : ShiftableWidget(parent, owningLayout)
    , ui(new Ui::ResumeQualificationSubsection)
{
    ui->setupUi(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &ResumeQualificationSubsection::showCustomContextMenu);
    resizePlainTextArea(ui->subsectionContentsText);
    resizeEventFilter = new ResizeEventFilter(ui->subsectionContentsText, ui->subsectionContentsText);
    ui->subsectionContentsText->installEventFilter(resizeEventFilter);
    setShiftWidgetVisibility();
    collapsed = false;
}

ResumeQualificationSubsection::~ResumeQualificationSubsection(){
    delete ui;
}

QPushButton *ResumeQualificationSubsection::getShiftUpButton() const{
    return ui->shiftUpBtn;
}

QPushButton *ResumeQualificationSubsection::getShiftDownButton() const{
    return ui->shiftDownBtn;
}

bool ResumeQualificationSubsection::isIncluded() const{
    return ui->includeBox->isChecked();
}

void ResumeQualificationSubsection::setIncluded(const bool included){
    Qt::CheckState newState = included ? Qt::CheckState::Checked : Qt::CheckState::Unchecked;
    ui->includeBox->setCheckState(newState);
}

QCheckBox *ResumeQualificationSubsection::getIncludedBox(){
    return ui->includeBox;
}

QString ResumeQualificationSubsection::getDescription() const{
    return ui->subsectionContentsText->toPlainText();
}

QList<ResumeSubsectionDetail *> ResumeQualificationSubsection::getEnabledDetails() const{
    QList<ResumeSubsectionDetail*> list;
    for(int i=0; i<ui->detailsLayout->count(); i++){
        ResumeSubsectionDetail* detail = qobject_cast<ResumeSubsectionDetail*>(ui->detailsLayout->itemAt(i)->widget());
        if(detail->isIncluded())
            list.append(detail);
    }
    return list;
}

QList<ResumeSubsectionDetail *> ResumeQualificationSubsection::getDetails() const{
    QList<ResumeSubsectionDetail*> list;
    for(int i=0; i<ui->detailsLayout->count(); i++){
        list.append(qobject_cast<ResumeSubsectionDetail*>(ui->detailsLayout->itemAt(i)->widget()));
    }
    return list;
}

QDomElement ResumeQualificationSubsection::toXml(QDomDocument &document) const{
    QDomElement subsectionElement = document.createElement("Subsection");
    QDomElement descriptionELement = document.createElement("Description");
    descriptionELement.appendChild(document.createTextNode(getDescription()));
    subsectionElement.appendChild(descriptionELement);

    auto details = getDetails();
    for(int i=0; i<details.size(); i++){
        subsectionElement.appendChild(details.at(i)->toXml(document));
    }

    return subsectionElement;
}

void ResumeQualificationSubsection::loadFromFile(QDomElement &element){
    QDomElement descriptionElement = element.firstChildElement();
    ui->subsectionContentsText->setPlainText(descriptionElement.text());
    resizePlainTextArea(ui->subsectionContentsText);

    QDomElement detailElement = descriptionElement.nextSiblingElement();
    while(!detailElement.isNull()){
        ResumeSubsectionDetail* newDetail = createAndAddDetail();
        newDetail->loadFromFile(detailElement);
        detailElement = detailElement.nextSiblingElement();
    }

    for(int i=0; i<ui->detailsLayout->count(); i++){
        qobject_cast<ShiftableWidget*>(ui->detailsLayout->itemAt(i)->widget())->setShiftWidgetVisibility();
    }
}


void ResumeQualificationSubsection::on_subsectionContentsText_textChanged(){
    resizePlainTextArea(ui->subsectionContentsText);
}

void ResumeQualificationSubsection::on_addSubsectionDetailBtn_clicked(){
    ResumeSubsectionDetail* newDetail = createAndAddDetail();
    newDetail->setShiftWidgetVisibility();

    int prevIndex = ui->detailsLayout->count()-2;
    if(prevIndex < 0)
        return;
    qobject_cast<ShiftableWidget*>(ui->detailsLayout->itemAt(prevIndex)->widget())->setShiftWidgetVisibility();
}

void ResumeQualificationSubsection::on_includeBox_checkStateChanged(const Qt::CheckState &state){
    if(state == Qt::CheckState::Unchecked){
        for(int i=0; i<ui->detailsLayout->count(); i++){
            ResumeSubsectionDetail* detail = qobject_cast<ResumeSubsectionDetail*>(ui->detailsLayout->itemAt(i)->widget());
            detail->setIncluded(false);
        }
    }
}

ResumeSubsectionDetail *ResumeQualificationSubsection::createAndAddDetail(){
    ResumeSubsectionDetail* newDetail = new ResumeSubsectionDetail(this, ui->detailsLayout);

    QPushButton* shiftUpBtn = newDetail->getShiftUpButton();
    connect(shiftUpBtn, &QPushButton::clicked, this, [this, newDetail](){
        newDetail->shiftWidgetUp();
    });
    QPushButton* shiftDownBtn = newDetail->getShiftDownButton();
    connect(shiftDownBtn, &QPushButton::clicked, this, [this, newDetail](){
        newDetail->shiftWidgetDown();
    });

    QCheckBox* includeBox = newDetail->getIncludedBox();
    connect(includeBox, &QCheckBox::checkStateChanged, this, [this](Qt::CheckState state){
        if(state == Qt::CheckState::Checked && ui->includeBox->checkState() != Qt::CheckState::Checked){
            ui->includeBox->setChecked(true);
        }
    });

    ui->detailsLayout->addWidget(newDetail);
    return newDetail;
}

void ResumeQualificationSubsection::on_collapseBtn_clicked(){
    collapsed = !collapsed;
    QString collapsedBtnText = collapsed ? ">" : "v";
    ui->collapseBtn->setText(collapsedBtnText);

    for(int i=0; i<ui->detailsLayout->count(); i++){
        ui->detailsLayout->itemAt(i)->widget()->setVisible(!collapsed);
    }
    ui->addSubsectionDetailBtn->setVisible(!collapsed);
}



}

