#include "keywordassociation.h"
#include "ui_keywordassociation.h"

namespace rcl {
namespace gui {
namespace keyword {

KeywordAssociation::KeywordAssociation(QWidget *parent, rcl::keyword::KeywordOwner* keywordOwner, rcl::keyword::Keyword* keyword)
    : QWidget(parent), keywordOwner(keywordOwner), keyword(keyword)
    , ui(new Ui::KeywordAssociation)
{
    ui->setupUi(this);
    ui->label->setText(keyword->getKeywordName());
    ui->checkBox->setChecked(keywordOwner->isAssociatedKeyword(keyword));
}

KeywordAssociation::~KeywordAssociation()
{
    delete ui;
}

void KeywordAssociation::on_checkBox_checkStateChanged(const Qt::CheckState &checkState){
    if(checkState == Qt::CheckState::Checked){
        keywordOwner->associateKeyword(keyword);
    } else if(checkState == Qt::CheckState::Unchecked){
        keywordOwner->disassociateKeyword(keyword);
    }
}



} // namespace keyword
} // namespace gui
} // namespace rcl
