#include "resumesubsectiondetail.h"
#include "ui_resumesubsectiondetail.h"
#include "../gui_utils.h"
#include "../keyword/keywordassociationpopup.h"
#include "../../keyword/keywordmanager.h"

#include <QMenu>
#include <QTimer>
#include <QTextStream>

namespace rcl::gui::resume::qualification{

ResumeSubsectionDetail::ResumeSubsectionDetail(QWidget *parent, QVBoxLayout* owningLayout)
    : ShiftableWidget(parent, owningLayout), rcl::keyword::KeywordOwner(), ui(new Ui::ResumeSubsectionDetail){
    ui->setupUi(this);
    setShiftWidgetVisibility();
    resizePlainTextArea(ui->detailTextEdit);
    resizeEventFilter = new ResizeEventFilter(ui->detailTextEdit, ui->detailTextEdit);
    ui->detailTextEdit->installEventFilter(resizeEventFilter);
    connect(keywordsListener, &rcl::keyword::KeywordListener::included, this, [this](){
        setIncluded(true);
    });

}

ResumeSubsectionDetail::~ResumeSubsectionDetail(){
    delete ui;
}

QPushButton *ResumeSubsectionDetail::getShiftUpButton() const{
    return ui->shiftUpBtn;
}

QPushButton *ResumeSubsectionDetail::getShiftDownButton() const{
    return ui->shiftDownBtn;
}

bool ResumeSubsectionDetail::isIncluded() const{
    return ui->includedBox->isChecked();
}

void ResumeSubsectionDetail::setIncluded(const bool included){
    Qt::CheckState newState = included ? Qt::CheckState::Checked : Qt::CheckState::Unchecked;
    ui->includedBox->setCheckState(newState);
}

QCheckBox* ResumeSubsectionDetail::getIncludedBox() const{
    return ui->includedBox;
}

QString ResumeSubsectionDetail::getDetailText() const{
    return ui->detailTextEdit->toPlainText();
}

QDomElement ResumeSubsectionDetail::toXml(QDomDocument &document) const{
    QDomElement detailElement = document.createElement("Detail");
    QString keywordsString;
    QTextStream stream(&keywordsString);
    auto keywords = getAssociatedKeywords();
    for(int i=0; i<keywords.size(); i++){
        stream << keywords.at(i)->getKeywordName() << ";";
    }
    detailElement.setAttribute("keywords", keywordsString);
    detailElement.appendChild(document.createTextNode(getDetailText()));
    return detailElement;
}

void ResumeSubsectionDetail::loadFromFile(QDomElement &element){
    ui->detailTextEdit->setPlainText(element.text());
    resizePlainTextArea(ui->detailTextEdit);
    QString keywords = element.attribute("keywords", "");
    auto splitKeywords = keywords.split(";", Qt::SkipEmptyParts);
    for(int i=0; i<splitKeywords.size(); i++){
        if(rcl::keyword::KeywordManager::hasKeyword(splitKeywords.at(i)))
            associateKeyword(rcl::keyword::KeywordManager::getKeyword(splitKeywords.at(i)));
    }
}

void ResumeSubsectionDetail::on_detailTextEdit_textChanged(){
    resizePlainTextArea(ui->detailTextEdit);
}

void ResumeSubsectionDetail::showCustomContextMenu(const QPoint &location){
    QMenu* contextMenu = new QMenu("Detail Menu", this);
    QAction* keywordsAction = new QAction("associate keywords", contextMenu);
    connect(keywordsAction, &QAction::triggered, this, [this](){
        rcl::gui::keyword::KeywordAssociationPopup::show(this, this);
    });
    QAction* deleteAction = new QAction("delete", contextMenu);
    connect(deleteAction, &QAction::triggered, this, &QObject::deleteLater);
    contextMenu->addAction(keywordsAction);
    contextMenu->addAction(deleteAction);
    contextMenu->popup(mapToGlobal(location));
}


}
