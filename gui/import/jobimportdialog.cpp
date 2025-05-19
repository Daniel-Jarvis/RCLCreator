#include "jobimportdialog.h"
#include "ui_jobimportdialog.h"

namespace rcl {
namespace gui {
namespace import {

JobImportDialog::JobImportDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JobImportDialog)
{
    ui->setupUi(this);
    setWindowTitle("Enter Job Posting");
}

JobImportDialog::~JobImportDialog()
{
    delete ui;
}

QString JobImportDialog::getJobSpecification() const{
    return ui->jobSpecificationEdit->toPlainText();
}

void JobImportDialog::on_importBtn_clicked(){
    accept();
}

void JobImportDialog::on_cancelBtn_clicked(){
    reject();
}



} // namespace import
} // namespace gui
} // namespace rcl
