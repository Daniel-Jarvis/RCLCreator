#pragma once

#include "headerelement.h"

#include <QWidget>
#include <QPushButton>

namespace Ui {
class HeaderTextElement;
}

namespace rcl::gui::resume{

class HeaderTextElement : public HeaderElement
{
    Q_OBJECT

public:
    explicit HeaderTextElement(QWidget *parent = nullptr, QVBoxLayout* owningLayout = nullptr);
    ~HeaderTextElement();
    bool isIncluded() const override;
    QString getFormattedText() const override;
    QString getText() const;
    QPushButton* getShiftUpButton() const override;
    QPushButton* getShiftDownButton() const override;
    QDomElement toXml(QDomDocument& document) const override;
    void loadFromFile(QDomElement& element);

private:
    Ui::HeaderTextElement *ui;
};

}
