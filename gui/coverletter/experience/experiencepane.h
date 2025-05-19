#pragma once

#include "experience.h"

#include <QWidget>
#include <QDomDocument>
#include <QDomElement>

namespace rcl {
namespace gui {
namespace cl {
namespace experience {

namespace Ui {
class ExperiencePane;
}

class ExperiencePane : public QWidget
{
    Q_OBJECT

public:
    explicit ExperiencePane(QWidget *parent = nullptr);
    ~ExperiencePane();
    QList<Experience*> getExperinces() const;
    QList<Experience*> getIncludedExperinces() const;
    QDomElement toXml(QDomDocument& document) const;
    void loadFromFile(const QDomElement& element);

private slots:
    void on_addExperienceBtn_clicked();

private:
    Ui::ExperiencePane *ui;
    Experience* createAndAddExperience();

};

} // namespace experience
} // namespace cl
} // namespace gui
} // namespace rcl
