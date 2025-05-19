#pragma once

#include <../shiftablewidget.h>

#include <QDomDocument>
#include <QDomElement>

namespace rcl {
namespace gui {
namespace resume {

class HeaderElement : public ShiftableWidget
{
    Q_OBJECT
public:
    HeaderElement(QWidget *parent = nullptr, QVBoxLayout* owningLayout = nullptr);
    virtual bool isIncluded()const = 0;
    virtual QString getFormattedText() const = 0;
    virtual QDomElement toXml(QDomDocument& document) const = 0;
};

} // namespace resume
} // namespace gui
} // namespace rcl
