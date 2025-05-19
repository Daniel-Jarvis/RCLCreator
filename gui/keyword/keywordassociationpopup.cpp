#include "keywordassociationpopup.h"
#include "ui_keywordassociationpopup.h"
#include "../../keyword/keywordmanager.h"

namespace rcl {
namespace gui {
namespace keyword {

KeywordAssociationPopup::KeywordAssociationPopup(QWidget *parent, rcl::keyword::KeywordOwner* keywordOwner)
    : QDialog(parent), keywordOwner(keywordOwner)
    , ui(new Ui::KeywordAssociationPopup)
{
    ui->setupUi(this);
    auto keywords = rcl::keyword::KeywordManager::getKeywords();
    for(int i=0; i<keywords.size(); i++){
        createAndAddKeywordAssiciation(keywords[i]);
    }
}

void KeywordAssociationPopup::show(QWidget *parent, rcl::keyword::KeywordOwner *keywordOwner){
    KeywordAssociationPopup popup(parent, keywordOwner);
    popup.exec();
}

KeywordAssociationPopup::~KeywordAssociationPopup()
{
    delete ui;
}

void KeywordAssociationPopup::on_doneBtn_clicked(){
    accept();
}

KeywordAssociation *KeywordAssociationPopup::createAndAddKeywordAssiciation(rcl::keyword::Keyword* keyword){
    KeywordAssociation* newKeywordAssociation = new KeywordAssociation(this, keywordOwner, keyword);
    ui->keywordAssociationLayout->addWidget(newKeywordAssociation);
    return newKeywordAssociation;
}


} // namespace keyword
} // namespace gui
} // namespace rcl
