#pragma once

#include <QWidget>
#include <QDialog>

namespace rcl {
namespace gui {
namespace import {

namespace Ui {
class JobImportDialog;
}

class JobImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JobImportDialog(QWidget *parent = nullptr);
    ~JobImportDialog();
    QString getJobSpecification() const;

private slots:
    void on_importBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::JobImportDialog *ui;
};

} // namespace import
} // namespace gui
} // namespace rcl
