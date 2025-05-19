#pragma once

#include "../shiftablewidget.h"

#include <QWidget>
#include <QDomDocument>
#include <QDomElement>

namespace rcl {
namespace gui {
namespace cl {
namespace properties {

namespace Ui {
class Property;
}

class Property : public ShiftableWidget
{
    Q_OBJECT

public:
    explicit Property(QWidget *parent = nullptr, QVBoxLayout* owningLayout = nullptr);
    ~Property();
    virtual QPushButton* getShiftUpButton() const override;
    virtual QPushButton* getShiftDownButton() const override;
    QDomElement toXml(QDomDocument& document);
    QString getPropertyName() const;
    void setPropertyName(const QString& propertyName);
    QString getPropertyValue() const;
    void setPropertyValue(const QString& propertyValue);

private:
    Ui::Property *ui;
};

} // namespace properties
} // namespace cl
} // namespace gui
} // namespace rcl
