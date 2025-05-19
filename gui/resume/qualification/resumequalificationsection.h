#pragma once

#include "resumequalificationsubsection.h"
#include "../shiftablewidget.h"

#include <QWidget>
#include <QDomDocument>
#include <QDomElement>
#include <QCheckBox>

namespace Ui {
class ResumeQualificationSection;
}

namespace rcl::gui::resume::qualification {
class ResumeQualificationSection : public ShiftableWidget
{
    Q_OBJECT

public:
    explicit ResumeQualificationSection(QWidget *parent = nullptr, QVBoxLayout* owningLayout = nullptr);
    ~ResumeQualificationSection();
    QCheckBox* getIncludeSectionBox() const;
    bool isIncluded() const;
    QString getSectionTitle() const;
    QList<ResumeQualificationSubsection*> getIncludedSubsections() const;
    QList<ResumeQualificationSubsection*> getSubsections() const;
    QPushButton* getShiftUpButton() const override;
    QPushButton* getShiftDownButton() const override;
    QDomElement toXml(QDomDocument& document) const;
    void loadFromFile(QDomElement& element);

private slots:
    void on_addSubsectionBtn_clicked();

    void on_includeSectionCheckBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_collapseBtn_clicked();

private:
    Ui::ResumeQualificationSection *ui;
    bool collapsed;
    ResumeQualificationSubsection* createAndAddSubsection();
};
}
