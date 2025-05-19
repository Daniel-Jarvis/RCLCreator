#include "propertiespane.h"
#include "ui_propertiespane.h"
#include "property.h"

#include <QMenu>
#include <QInputDialog>

namespace rcl {
namespace gui {
namespace cl {
namespace properties {

PropertiesPane::PropertiesPane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PropertiesPane)
{
    ui->setupUi(this);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &PropertiesPane::showContextMenu);
}

PropertiesPane::~PropertiesPane()
{
    delete ui;
}

QList<Property *> PropertiesPane::getProperties() const{
    QList<Property*> properties(ui->propertiesLayout->count());
    for(int i=0; i<ui->propertiesLayout->count(); i++){
        properties[i] = qobject_cast<Property*>(ui->propertiesLayout->itemAt(i)->widget());
    }
    return properties;
}

QMap<QString, QString> PropertiesPane::getPropertiesMap() const{
    QMap<QString, QString> propertiesMap;
    for(int i=0; i<ui->propertiesLayout->count(); i++){
        Property* property = qobject_cast<Property*>(ui->propertiesLayout->itemAt(i)->widget());
        propertiesMap[property->getPropertyName()] = property->getPropertyValue();
    }
    return propertiesMap;
}

void PropertiesPane::showContextMenu(const QPoint &location){
    QMenu contextMenu("Header Menu");
    QAction addHeaderText("Add new property");
    connect(&addHeaderText, &QAction::triggered, this, &PropertiesPane::addNewProperty);

    contextMenu.addAction(&addHeaderText);
    contextMenu.exec(mapToGlobal(location));
}

void PropertiesPane::addNewProperty(){
    bool inputRecieved;
    QString propertyName = QInputDialog::getText(this, "Property Specifier", "Property Name:", QLineEdit::Normal, "", &inputRecieved);

    if(!inputRecieved || propertyName.isEmpty())
        return;

    Property* newProperty = createAndAddProperty(propertyName);
    newProperty->setShiftWidgetVisibility();
    int prevIndex = ui->propertiesLayout->count()-2;
    if(prevIndex >= 0)
        qobject_cast<ShiftableWidget*>(ui->propertiesLayout->itemAt(prevIndex)->widget())->setShiftWidgetVisibility();

    qInfo() << "Add new property";
}

QDomElement PropertiesPane::toXml(QDomDocument &document) const{
    QDomElement propertiesRoot = document.createElement("Properties");
    auto properties = getProperties();
    for(int i=0; i<properties.size(); i++){
        propertiesRoot.appendChild(properties.at(i)->toXml(document));
    }
    return propertiesRoot;
}

void PropertiesPane::loadFromFile(const QDomElement &element){
    QDomElement propertyElement = element.firstChildElement();
    while(!propertyElement.isNull()){
        createAndAddProperty(propertyElement.text());
        propertyElement = propertyElement.nextSiblingElement();
    }

    for(int i=0; i<ui->propertiesLayout->count(); i++){
        qobject_cast<ShiftableWidget*>(ui->propertiesLayout->itemAt(i)->widget())->setShiftWidgetVisibility();
    }
}

void PropertiesPane::loadPropertiesFromJob(const job::JobSpecifications &job){
    auto properties = getProperties();
    for(int i=0; i<properties.size(); i++){
        Property* property = properties.at(i);
        if(property->getPropertyName() == "title")
            property->setPropertyValue(job.getTitle());
        if(property->getPropertyName() == "company")
            property->setPropertyValue(job.getCompany());
    }
}

Property *PropertiesPane::createAndAddProperty(const QString& propName){
    Property* newProperty = new Property(this, ui->propertiesLayout);
    newProperty->setPropertyName(propName);
    ui->propertiesLayout->addWidget(newProperty);
    QPushButton* shiftUpBtn = newProperty->getShiftUpButton();
    connect(shiftUpBtn, &QPushButton::clicked, this, [this, newProperty](){
        newProperty->shiftWidgetUp();
    });
    QPushButton* shiftDownBtn = newProperty->getShiftDownButton();
    connect(shiftDownBtn, &QPushButton::clicked, this, [this, newProperty](){
        newProperty->shiftWidgetDown();
    });
    return newProperty;
}

} // namespace properties
} // namespace cl
} // namespace gui
} // namespace rcl
