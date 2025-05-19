#pragma once

#include "../shiftablewidget.h"
#include "../resizeeventfilter.h"
#include "../../../keyword/keywordowner.h"

#include <QWidget>
#include <QDomDocument>
#include <QDomElement>
#include <QCheckBox>

namespace Ui {
class ResumeSubsectionDetail;
}

namespace rcl::gui::resume::qualification {

class ResumeSubsectionDetail : public ShiftableWidget, public rcl::keyword::KeywordOwner
{
    Q_OBJECT

public:
    explicit ResumeSubsectionDetail(QWidget *parent = nullptr, QVBoxLayout* owningLayout = nullptr);
    ~ResumeSubsectionDetail();
    QPushButton* getShiftUpButton() const override;
    QPushButton* getShiftDownButton() const override;
    bool isIncluded() const;
    void setIncluded(const bool included);
    QCheckBox* getIncludedBox() const;
    QString getDetailText() const;
    QDomElement toXml(QDomDocument& document) const;
    void loadFromFile(QDomElement& element);

private slots:
    void on_detailTextEdit_textChanged();

protected slots:
    void showCustomContextMenu(const QPoint &location) override;

private:
    Ui::ResumeSubsectionDetail *ui;
    ResizeEventFilter* resizeEventFilter;
};

}
