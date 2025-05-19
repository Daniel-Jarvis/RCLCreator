#pragma once

#include "headerelement.h"
#include "headertextelement.h"
#include "headerlinkelement.h"

#include <QWidget>
#include <QDomDocument>
#include <QDomElement>

namespace Ui {
class ResumeHeaderPane;
}

namespace rcl::gui::resume{
class ResumeHeaderPane : public QWidget
{
    Q_OBJECT

public:
    explicit ResumeHeaderPane(QWidget *parent = nullptr);
    ~ResumeHeaderPane();
    QString getName() const;
    QList<HeaderElement*> getIncludedElements() const;
    QList<HeaderElement*> getElements() const;
    QDomElement toXml(QDomDocument& document) const;
    void loadFromFile(QDomElement& xml);

private slots:
    void showContextMenu(const QPoint &location);
    void createNewHeaderTextElement();
    void createNewHeaderLinkElement();

private:
    Ui::ResumeHeaderPane *ui;
    HeaderTextElement* createAndAddHeaderTextElement();
    HeaderLinkElement* createAndAddHeaderLinkElement();

};
}
