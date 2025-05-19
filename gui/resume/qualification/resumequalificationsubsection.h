#pragma once

#include "resumesubsectiondetail.h"
#include "../shiftablewidget.h"
#include "../resizeeventfilter.h"

#include <QWidget>
#include <QDomDocument>
#include <QDomElement>
#include <QCheckBox>

namespace Ui {
class ResumeQualificationSubsection;
}

namespace rcl::gui::resume::qualification {
class ResumeQualificationSubsection : public ShiftableWidget
{
    Q_OBJECT

public:
    explicit ResumeQualificationSubsection(QWidget *parent = nullptr, QVBoxLayout* owningLayout = nullptr);
    ~ResumeQualificationSubsection();
    QPushButton* getShiftUpButton() const override;
    QPushButton* getShiftDownButton() const override;
    bool isIncluded() const;
    void setIncluded(const bool included);
    QCheckBox* getIncludedBox();
    QString getDescription() const;
    QList<ResumeSubsectionDetail*> getEnabledDetails() const;
    QList<ResumeSubsectionDetail*> getDetails() const;
    QDomElement toXml(QDomDocument& document) const;
    void loadFromFile(QDomElement& element);

private slots:
    void on_subsectionContentsText_textChanged();
    void on_addSubsectionDetailBtn_clicked();

    void on_includeBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_collapseBtn_clicked();

private:
    Ui::ResumeQualificationSubsection *ui;
    ResizeEventFilter* resizeEventFilter;
    bool collapsed;
    void updateSubsectionContentsHeight();
    ResumeSubsectionDetail* createAndAddDetail();
};
}
