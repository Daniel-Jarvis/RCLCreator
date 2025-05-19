#include "headerlinkelement.h"
#include "ui_headerlinkelement.h"

#include <QTextStream>

namespace rcl::gui::resume{

HeaderLinkElement::HeaderLinkElement(QWidget *parent, QVBoxLayout* owningLayout)
    : HeaderElement(parent, owningLayout)
    , ui(new Ui::HeaderLinkElement){
    ui->setupUi(this);
    setShiftWidgetVisibility();
}

HeaderLinkElement::~HeaderLinkElement(){
    delete ui;
}

bool rcl::gui::resume::HeaderLinkElement::isIncluded() const{
    return ui->includeBox->isChecked();
}

QString HeaderLinkElement::getFormattedText() const{
    QString formattedText = "";
    QTextStream stream(&formattedText);
    if(!ui->textLabelEdit->displayText().isEmpty())
        stream << ui->textLabelEdit->displayText() << ": ";
    stream << "<a href=\"";
    stream << ui->textLinkToEdit->displayText() << "\">";
    stream << ui->textDisplayEdit->displayText() << "</a>";
    return formattedText;
}

QString HeaderLinkElement::getLabelText() const{
    return ui->textLabelEdit->displayText();
}

QString HeaderLinkElement::getDisplayText() const{
    return ui->textDisplayEdit->displayText();
}

QString HeaderLinkElement::getLinkText() const{
    return ui->textLinkToEdit->displayText();
}

QPushButton *HeaderLinkElement::getShiftUpButton() const{
    return ui->shiftUpBtn;
}

QPushButton *HeaderLinkElement::getShiftDownButton() const{
    return ui->shiftDownBtn;
}

QDomElement HeaderLinkElement::toXml(QDomDocument &document) const{
    QDomElement linkElement = document.createElement("HeaderLinkElement");

    QDomElement labelText = document.createElement("HeaderLinkLabel");
    labelText.appendChild(document.createTextNode(getLabelText()));
    linkElement.appendChild(labelText);

    QDomElement displayText = document.createElement("HeaderLinkDisplay");
    displayText.appendChild(document.createTextNode(getDisplayText()));
    linkElement.appendChild(displayText);

    QDomElement linkText = document.createElement("HeaderLinkLink");
    linkText.appendChild(document.createTextNode(getLinkText()));
    linkElement.appendChild(linkText);

    return linkElement;
}

void HeaderLinkElement::loadFromFile(QDomElement &element){
    QDomElement node = element.firstChildElement();
    ui->textLabelEdit->setText(node.text());

    node = node.nextSiblingElement();
    ui->textDisplayEdit->setText(node.text());

    node = node.nextSiblingElement();
    ui->textLinkToEdit->setText(node.text());
}

}
