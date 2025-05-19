#include "experience.h"
#include "ui_experience.h"
#include "../../gui_utils.h"
#include "../keyword/keywordassociationpopup.h"
#include "../../keyword/keywordmanager.h"

#include <QMenu>

namespace rcl {
namespace gui {
namespace cl {
namespace experience {

Experience::Experience(QWidget *parent, QVBoxLayout* owningLayout)
    : ShiftableWidget(parent, owningLayout), rcl::keyword::KeywordOwner()
    , ui(new Ui::Experience)
{
    ui->setupUi(this);
    resizeEventFilter = new ResizeEventFilter(this, ui->experienceTextEdit);
    installEventFilter(resizeEventFilter);
    resizePlainTextArea(ui->experienceTextEdit);
    connect(ui->experienceTextEdit, &QPlainTextEdit::textChanged, this, [this](){
        resizePlainTextArea(ui->experienceTextEdit);
    });
    connect(keywordsListener, &rcl::keyword::KeywordListener::included, this, [this](){
        setIncluded(true);
    });
}

Experience::~Experience()
{
    delete ui;
}

QPushButton *Experience::getShiftUpButton() const{
    return ui->shiftUpBtn;
}

QPushButton *Experience::getShiftDownButton() const{
    return ui->shiftDownBtn;
}

QDomElement Experience::toXml(QDomDocument &document) const{
    QDomElement experienceElement = document.createElement("Experience");
    QString keywordsString;
    QTextStream stream(&keywordsString);
    auto keywords = getAssociatedKeywords();
    for(int i=0; i<keywords.size(); i++){
        stream << keywords.at(i)->getKeywordName() << ";";
    }
    experienceElement.setAttribute("keywords", keywordsString);
    experienceElement.appendChild(document.createTextNode(ui->experienceTextEdit->toPlainText()));
    return experienceElement;
}

void Experience::loadFromFile(const QDomElement &element){
    ui->experienceTextEdit->setPlainText(element.text());
    QString keywords = element.attribute("keywords", "");
    auto splitKeywords = keywords.split(";", Qt::SkipEmptyParts);
    for(int i=0; i<splitKeywords.size(); i++){
        if(rcl::keyword::KeywordManager::hasKeyword(splitKeywords.at(i)))
            associateKeyword(rcl::keyword::KeywordManager::getKeyword(splitKeywords.at(i)));
    }
}

bool Experience::isIncluded() const{
    return ui->includeBox->isChecked();
}

void Experience::setIncluded(const bool included){
    ui->includeBox->setChecked(included);
}

QString Experience::getContents() const{
    return ui->experienceTextEdit->toPlainText();
}

void Experience::showCustomContextMenu(const QPoint &location){
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

} // namespace experience
} // namespace cl
} // namespace gui
} // namespace rcl
