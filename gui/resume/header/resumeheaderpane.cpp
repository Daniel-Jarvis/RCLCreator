#include "resumeheaderpane.h"
#include "ui_resumeheaderpane.h"
#include "headertextelement.h"
#include "headerlinkelement.h"

#include <QMenu>

namespace rcl::gui::resume{

ResumeHeaderPane::ResumeHeaderPane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResumeHeaderPane){
    ui->setupUi(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &ResumeHeaderPane::showContextMenu);
}

ResumeHeaderPane::~ResumeHeaderPane(){
    delete ui;
}

QString ResumeHeaderPane::getName() const{
    return ui->nameLineEdit->displayText();
}

QList<HeaderElement *> ResumeHeaderPane::getIncludedElements() const{
    QList<HeaderElement*> includedElements;
    for(int i=0; i<ui->headerPartLayout->count(); i++){
        HeaderElement* element = qobject_cast<HeaderElement*>(ui->headerPartLayout->itemAt(i)->widget());
        if(element->isIncluded())
            includedElements.append(element);
    }
    return includedElements;
}

QList<HeaderElement *> ResumeHeaderPane::getElements() const{
    QList<HeaderElement*> elements;
    for(int i=0; i<ui->headerPartLayout->count(); i++){
        elements.append(qobject_cast<HeaderElement*>(ui->headerPartLayout->itemAt(i)->widget()));
    }
    return elements;
}

QDomElement ResumeHeaderPane::toXml(QDomDocument &document) const{
    QDomElement headerRoot = document.createElement("Header");

    QDomElement name = document.createElement("Name");
    name.appendChild(document.createTextNode(getName()));
    headerRoot.appendChild(name);

    for(int i=0; i<ui->headerPartLayout->count(); i++){
        HeaderElement* headerElement = qobject_cast<HeaderElement*>(ui->headerPartLayout->itemAt(i)->widget());
        headerRoot.appendChild(headerElement->toXml(document));
    }

    return headerRoot;
}

void ResumeHeaderPane::loadFromFile(QDomElement &xml){
    QDomNode node = xml.firstChild();

    QDomElement nameElement = node.toElement();
    ui->nameLineEdit->setText(nameElement.text());
    node = node.nextSibling();

    while(!node.isNull()){
        //load the header element
        QDomElement headerElement = node.toElement();
        if(headerElement.tagName() == "HeaderTextElement"){
            HeaderTextElement* textElement = createAndAddHeaderTextElement();
            textElement->loadFromFile(headerElement);
        } else if(headerElement.tagName() == "HeaderLinkElement"){
            HeaderLinkElement* linkElement = createAndAddHeaderLinkElement();
            linkElement->loadFromFile(headerElement);
        }

        node = node.nextSibling();
    }

    for(int i=0; i<ui->headerPartLayout->count(); i++){
        qobject_cast<ShiftableWidget*>(ui->headerPartLayout->itemAt(i)->widget())->setShiftWidgetVisibility();
    }

}

void ResumeHeaderPane::showContextMenu(const QPoint &location){
    QMenu contextMenu("Header Menu");
    QAction addHeaderText("Add new header text element");
    connect(&addHeaderText, &QAction::triggered, this, &ResumeHeaderPane::createNewHeaderTextElement);
    QAction addHeaderLink("Add new header link element");
    connect(&addHeaderLink, &QAction::triggered, this, &ResumeHeaderPane::createNewHeaderLinkElement);

    contextMenu.addAction(&addHeaderText);
    contextMenu.addAction(&addHeaderLink);
    contextMenu.exec(mapToGlobal(location));
}

void ResumeHeaderPane::createNewHeaderTextElement(){
    HeaderTextElement* newTextElement = createAndAddHeaderTextElement();
    newTextElement->setShiftWidgetVisibility();
    qobject_cast<ShiftableWidget*>(ui->headerPartLayout->itemAt(ui->headerPartLayout->count()-2)->widget())->setShiftWidgetVisibility();
}

void ResumeHeaderPane::createNewHeaderLinkElement(){
    HeaderLinkElement* newLinkElement = createAndAddHeaderLinkElement();
    newLinkElement->setShiftWidgetVisibility();
    qobject_cast<ShiftableWidget*>(ui->headerPartLayout->itemAt(ui->headerPartLayout->count()-2)->widget())->setShiftWidgetVisibility();
}

HeaderTextElement *ResumeHeaderPane::createAndAddHeaderTextElement(){
    HeaderTextElement* newTextElement = new HeaderTextElement(this, ui->headerPartLayout);
    QPushButton* shiftUpBtn = newTextElement->getShiftUpButton();
    connect(shiftUpBtn, &QPushButton::clicked, this, [this, newTextElement](){
        newTextElement->shiftWidgetUp();
    });
    QPushButton* shiftDownBtn = newTextElement->getShiftDownButton();
    connect(shiftDownBtn, &QPushButton::clicked, this, [this, newTextElement](){
        newTextElement->shiftWidgetDown();
    });
    ui->headerPartLayout->addWidget(newTextElement);
    return newTextElement;
}

HeaderLinkElement *ResumeHeaderPane::createAndAddHeaderLinkElement(){
    HeaderLinkElement* newLinkElement = new HeaderLinkElement(this, ui->headerPartLayout);
    QPushButton* shiftUpBtn = newLinkElement->getShiftUpButton();
    connect(shiftUpBtn, &QPushButton::clicked, this, [this, newLinkElement](){
        newLinkElement->shiftWidgetUp();
    });
    QPushButton* shiftDownBtn = newLinkElement->getShiftDownButton();
    connect(shiftDownBtn, &QPushButton::clicked, this, [this, newLinkElement](){
        newLinkElement->shiftWidgetDown();
    });
    ui->headerPartLayout->addWidget(newLinkElement);
    return newLinkElement;
}

}
