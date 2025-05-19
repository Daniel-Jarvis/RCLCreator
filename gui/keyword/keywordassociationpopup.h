#pragma once

#include "../../keyword/keywordowner.h"
#include "keywordassociation.h"

#include <QDialog>

namespace rcl {
namespace gui {
namespace keyword {

namespace Ui {
class KeywordAssociationPopup;
}

class KeywordAssociationPopup : public QDialog
{
    Q_OBJECT

public:
    ~KeywordAssociationPopup();
    static void show(QWidget* parent, rcl::keyword::KeywordOwner* keywordOwner);

private slots:
    void on_doneBtn_clicked();

private:
    Ui::KeywordAssociationPopup *ui;
    rcl::keyword::KeywordOwner* keywordOwner;
    explicit KeywordAssociationPopup(QWidget *parent = nullptr, rcl::keyword::KeywordOwner* keywordOwner = nullptr);
    KeywordAssociation* createAndAddKeywordAssiciation(rcl::keyword::Keyword* keyword);
};

} // namespace keyword
} // namespace gui
} // namespace rcl
