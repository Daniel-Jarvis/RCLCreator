#include "property.h"
#include "ui_property.h"

namespace rcl {
namespace gui {
namespace cl {
namespace properties {

Property::Property(QWidget *parent, QVBoxLayout* owningLayout)
    : ShiftableWidget(parent, owningLayout)
    , ui(new Ui::Property)
{
    ui->setupUi(this);
}

Property::~Property()
{
    delete ui;
}

QPushButton *Property::getShiftUpButton() const{
    return ui->shiftUpBtn;
}

QPushButton *Property::getShiftDownButton() const{
    return ui->shiftDownBtn;
}

void Property::setPropertyName(const QString &propertyName){
    ui->propertyLabel->setText(propertyName);
}

QDomElement Property::toXml(QDomDocument &document){
    QDomElement propertyElement = document.createElement("Property");
    propertyElement.appendChild(document.createTextNode(ui->propertyLabel->text()));
    return propertyElement;
}

QString Property::getPropertyName() const{
    return ui->propertyLabel->text();
}

QString Property::getPropertyValue() const{
    return ui->propertyValueEdit->text();
}

void Property::setPropertyValue(const QString &propertyValue){
    ui->propertyValueEdit->setText(propertyValue);
}

} // namespace properties
} // namespace cl
} // namespace gui
} // namespace rcl
