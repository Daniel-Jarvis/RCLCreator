#pragma once

#include "keyword/keywordmanager.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LaunchWindow;
}
QT_END_NAMESPACE

class LaunchWindow : public QMainWindow
{
    Q_OBJECT

public:
    LaunchWindow(QWidget *parent = nullptr);
    ~LaunchWindow();

private:
    Ui::LaunchWindow *ui;

private slots:
    void save();
    void importJob();
    void openKeywordManagerGui();
};
