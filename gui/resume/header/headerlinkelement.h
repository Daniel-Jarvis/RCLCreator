#pragma once

#include "headerelement.h"

#include <QWidget>

namespace Ui {
class HeaderLinkElement;
}

namespace rcl::gui::resume{

class HeaderLinkElement : public HeaderElement
{
    Q_OBJECT

public:
    explicit HeaderLinkElement(QWidget *parent = nullptr, QVBoxLayout* owningLayout = nullptr);
    ~HeaderLinkElement();
    bool isIncluded() const override;
    QString getFormattedText() const override;
    QString getLabelText() const;
    QString getDisplayText() const;
    QString getLinkText() const;
    QPushButton* getShiftUpButton() const override;
    QPushButton* getShiftDownButton() const override;
    QDomElement toXml(QDomDocument& document) const override;
    void loadFromFile(QDomElement& element);

private:
    Ui::HeaderLinkElement *ui;
};

}
