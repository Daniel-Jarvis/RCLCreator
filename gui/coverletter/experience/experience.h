#pragma once

#include "../../shiftablewidget.h"
#include "../../resizeeventfilter.h"
#include "../../../keyword/keywordowner.h"

#include <QWidget>
#include <QDomDocument>
#include <QDomElement>

namespace rcl {
namespace gui {
namespace cl {
namespace experience {

namespace Ui {
class Experience;
}

class Experience : public ShiftableWidget, public rcl::keyword::KeywordOwner
{
    Q_OBJECT

public:
    explicit Experience(QWidget *parent = nullptr, QVBoxLayout* owningLayout = nullptr);
    ~Experience();
    virtual QPushButton* getShiftUpButton() const override;
    virtual QPushButton* getShiftDownButton() const override;
    QDomElement toXml(QDomDocument& document) const;
    void loadFromFile(const QDomElement& element);
    bool isIncluded() const;
    void setIncluded(const bool included);
    QString getContents() const;

protected slots:
    void showCustomContextMenu(const QPoint &location) override;

private:
    Ui::Experience *ui;
    ResizeEventFilter* resizeEventFilter;
};

} // namespace experience
} // namespace cl
} // namespace gui
} // namespace rcl
