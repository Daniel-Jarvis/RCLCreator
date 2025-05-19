#include "keyworddisplay.h"
#include "ui_keyworddisplay.h"

namespace rcl {
namespace gui {
namespace keyword {

KeywordDisplay::KeywordDisplay(QWidget *parent,rcl::keyword::Keyword* keyword)
    : QWidget(parent), keyword(keyword)
    , ui(new Ui::KeywordDisplay)
{
    ui->setupUi(this);
    ui->keywordEdit->setText(keyword->getKeywordName());
}

KeywordDisplay::~KeywordDisplay()
{
    delete ui;
}

void KeywordDisplay::on_keywordEdit_textChanged(const QString &newKeyword){
    keyword->setKeywordName(newKeyword);
}


} // namespace keyword
} // namespace gui
} // namespace rcl
