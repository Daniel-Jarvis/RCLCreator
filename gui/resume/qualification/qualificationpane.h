#pragma once

#include "resumequalificationsection.h"

#include <QWidget>
#include <QDomDocument>

namespace rcl {
namespace gui {
namespace resume {
namespace qualification {

namespace Ui {
class QualificationPane;
}

class QualificationPane : public QWidget
{
    Q_OBJECT

public:
    explicit QualificationPane(QWidget *parent = nullptr);
    ~QualificationPane();
    QList<ResumeQualificationSection*> getIncludedQualifications() const;
    QList<ResumeQualificationSection*> getQualifications() const;
    QDomElement toXml(QDomDocument& document) const;
    void loadFromFile(QDomElement& xml);

private slots:
    void on_addSectionBtn_clicked();

private:
    Ui::QualificationPane *ui;
    qualification::ResumeQualificationSection* createAndAddSection();
};

} // namespace qualification
} // namespace resume
} // namespace gui
} // namespace rcl
