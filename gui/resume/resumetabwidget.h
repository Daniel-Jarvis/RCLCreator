#pragma once

#include "qualification/resumequalificationsection.h"
#include "../../keyword/keywordmanager.h"

#include <QWidget>
#include <QSplitter>

namespace Ui {
class ResumeTabWidget;
}

namespace rcl::gui::resume{
class ResumeTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResumeTabWidget(QWidget *parent = nullptr);
    ~ResumeTabWidget();
    void save() const;
    // QList<qualification::ResumeQualificationSection*> getSections() const;

public slots:
    void resumeContentChange();
    void buildResume();

private slots:
    void on_printButton_clicked();

private:
    QSplitter* areaSplitter;
    Ui::ResumeTabWidget *ui;
    qualification::ResumeQualificationSection* createAndAddSection();
    void load();
};

}
