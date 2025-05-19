#pragma once

#include <QDialog>

namespace rcl {
namespace gui {
namespace keyword {

namespace Ui {
class KeywordManagerGui;
}

class KeywordManagerGui : public QDialog
{
    Q_OBJECT

public:
    explicit KeywordManagerGui(QWidget *parent = nullptr);
    ~KeywordManagerGui();

private slots:
    void on_doneBtn_clicked();

    void on_addKeywordBtn_clicked();

private:
    Ui::KeywordManagerGui *ui;
};

} // namespace keyword
} // namespace gui
} // namespace rcl
