#pragma once

#include "../../keyword/keywordowner.h"
#include "../../keyword/keyword.h"

#include <QWidget>

namespace rcl {
namespace gui {
namespace keyword {

namespace Ui {
class KeywordAssociation;
}

class KeywordAssociation : public QWidget
{
    Q_OBJECT

public:
    explicit KeywordAssociation(QWidget *parent = nullptr, rcl::keyword::KeywordOwner* keywordOwner = nullptr, rcl::keyword::Keyword* keyword = nullptr);
    ~KeywordAssociation();

private slots:
    void on_checkBox_checkStateChanged(const Qt::CheckState &checkState);

private:
    Ui::KeywordAssociation *ui;
    rcl::keyword::KeywordOwner* keywordOwner;
    rcl::keyword::Keyword* keyword;
};

} // namespace keyword
} // namespace gui
} // namespace rcl
