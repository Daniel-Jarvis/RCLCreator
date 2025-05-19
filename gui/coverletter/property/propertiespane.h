#pragma once

#include "property.h"
#include "../../../job/jobspecifications.h"

#include <QWidget>
#include <QDomDocument>
#include <QDomElement>
#include <QMap>

namespace rcl {
namespace gui {
namespace cl {
namespace properties {

namespace Ui {
class PropertiesPane;
}

class PropertiesPane : public QWidget
{
    Q_OBJECT

public:
    explicit PropertiesPane(QWidget *parent = nullptr);
    ~PropertiesPane();
    QList<Property*> getProperties() const;
    QMap<QString, QString> getPropertiesMap() const;
    QDomElement toXml(QDomDocument& document) const;
    void loadFromFile(const QDomElement& element);
    void loadPropertiesFromJob(const job::JobSpecifications& job);

private slots:
    void showContextMenu(const QPoint &location);
    void addNewProperty();

private:
    Ui::PropertiesPane *ui;
    Property* createAndAddProperty(const QString& propName);
};

} // namespace properties
} // namespace cl
} // namespace gui
} // namespace rcl
