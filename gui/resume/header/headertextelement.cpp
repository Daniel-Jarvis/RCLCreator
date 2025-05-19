#include "headertextelement.h"
#include "ui_headertextelement.h"

namespace rcl::gui::resume{

HeaderTextElement::HeaderTextElement(QWidget *parent, QVBoxLayout* owningLayout)
    : HeaderElement(parent, owningLayout)
    , ui(new Ui::HeaderTextElement){
    ui->setupUi(this);
    setShiftWidgetVisibility();
}

QPushButton *HeaderTextElement::getShiftUpButton() const{
    return ui->shiftUpBtn;
}

QPushButton *HeaderTextElement::getShiftDownButton() const{
    return ui->shiftDownBtn;
}

QDomElement HeaderTextElement::toXml(QDomDocument &document) const{
    QDomElement element = document.createElement("HeaderTextElement");
    element.appendChild(document.createTextNode(getText()));
    return element;
}

void HeaderTextElement::loadFromFile(QDomElement &element){
    ui->contentLineEdit->setText(element.text());
}

bool HeaderTextElement::isIncluded() const{
    return ui->includeBox->isChecked();
}

QString HeaderTextElement::getFormattedText() const{
    return ui->contentLineEdit->text();
}

QString HeaderTextElement::getText() const{
    return ui->contentLineEdit->text();
}

HeaderTextElement::~HeaderTextElement(){
    delete ui;
}

}
