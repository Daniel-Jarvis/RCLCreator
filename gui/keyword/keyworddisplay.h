#pragma once

#include "../../keyword/keyword.h"

#include <QWidget>

namespace rcl {
namespace gui {
namespace keyword {

namespace Ui {
class KeywordDisplay;
}

class KeywordDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit KeywordDisplay(QWidget *parent = nullptr, rcl::keyword::Keyword* keyword = nullptr);
    ~KeywordDisplay();

private slots:
    void on_keywordEdit_textChanged(const QString &newKeyword);

private:
    Ui::KeywordDisplay *ui;
    rcl::keyword::Keyword* keyword;
};

} // namespace keyword
} // namespace gui
} // namespace rcl
