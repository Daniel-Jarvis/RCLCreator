#include "keywordmanagergui.h"
#include "ui_keywordmanagergui.h"
#include "keyworddisplay.h"
#include "../../keyword/keywordmanager.h"

namespace rcl {
namespace gui {
namespace keyword {

KeywordManagerGui::KeywordManagerGui(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::KeywordManagerGui)
{
    ui->setupUi(this);
    auto keywords = rcl::keyword::KeywordManager::getKeywords();
    for(int i=0; i<keywords.size(); i++){
        KeywordDisplay* keywordDisplay = new KeywordDisplay(this, keywords.at(i));
        ui->keywordLayout->addWidget(keywordDisplay);
    }
}

KeywordManagerGui::~KeywordManagerGui()
{
    delete ui;
}

void KeywordManagerGui::on_doneBtn_clicked(){
    accept();
}

void KeywordManagerGui::on_addKeywordBtn_clicked(){
    if(rcl::keyword::KeywordManager::hasKeyword(""))
        return;

    rcl::keyword::Keyword* newKeyword = rcl::keyword::KeywordManager::addKeyword("");
    KeywordDisplay* keywordDisplay = new KeywordDisplay(this, newKeyword);
    ui->keywordLayout->addWidget(keywordDisplay);

}



} // namespace keyword
} // namespace gui
} // namespace rcl
