#include "launchwindow.h"
#include "ui_launchwindow.h"
#include "gui/import/jobimportdialog.h"
#include "job/jobspecifications.h"
#include "gui/keyword/keywordmanagergui.h"
#include "keyword/keywordmanager.h"

LaunchWindow::LaunchWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LaunchWindow)
{
    ui->setupUi(this);
    connect(ui->actionSave, &QAction::triggered, this, &LaunchWindow::save);
    connect(ui->actionKeywords, &QAction::triggered, this, &LaunchWindow::openKeywordManagerGui);
    connect(ui->actionImportJob, &QAction::triggered, this, &LaunchWindow::importJob);
}

LaunchWindow::~LaunchWindow()
{
    delete ui;
}

void LaunchWindow::save(){
    ui->resumeTab->save();
    ui->coverLetterTab->save();
    rcl::keyword::KeywordManager::save();
}

void LaunchWindow::importJob(){
    rcl::gui::import::JobImportDialog importDialog;
    if(importDialog.exec() == QDialog::Accepted){
        rcl::job::JobSpecifications job(importDialog.getJobSpecification());
        ui->coverLetterTab->importJob(job);
    }
    return;
}

void LaunchWindow::openKeywordManagerGui(){
    rcl::gui::keyword::KeywordManagerGui dialog(this);
    dialog.exec();
}
