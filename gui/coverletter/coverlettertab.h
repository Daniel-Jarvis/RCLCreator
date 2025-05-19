#pragma once

#include "../../job/jobspecifications.h"

#include <QWidget>
#include <QSplitter>
#include <QDomElement>
#include <QMap>

namespace rcl {
namespace gui {
namespace cl {

namespace Ui {
class CoverLetterTab;
}

class CoverLetterTab : public QWidget
{
    Q_OBJECT

public:
    explicit CoverLetterTab(QWidget *parent = nullptr);
    ~CoverLetterTab();
    void save() const;
    void load();
    void setCompanyName(const QString& company);
    void setCompanyLocation(const QString& location);
    void setJobTitle(const QString& title);
    void importJob(const job::JobSpecifications& job);

private slots:
    void on_writeBtn_clicked();

    void on_printBtn_clicked();

private:
    QSplitter* areaSplitter;
    QSplitter* rightSplitter;
    Ui::CoverLetterTab *ui;
    void buildCoverLetter();
    QString replaceProperties(const QString& source, const QMap<QString, QString>& properties);
};

} // namespace cl
} // namespace gui
} // namespace rcl
