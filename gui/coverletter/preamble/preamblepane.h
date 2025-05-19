#pragma once

#include <QWidget>
#include <QDomDocument>
#include <QDomELement>

namespace rcl {
namespace gui {
namespace cl {
namespace preamble {

namespace Ui {
class PreamblePane;
}

class PreamblePane : public QWidget
{
    Q_OBJECT

public:
    explicit PreamblePane(QWidget *parent = nullptr);
    ~PreamblePane();
    bool isNameIncluded() const;
    QString getName() const;
    bool isPersonalLocationIncluded() const;
    QString getPersonalLocation() const;
    bool isPhoneNumberIncluded() const;
    QString getPhoneNumber() const;
    bool isEmailIncluded() const;
    QString getEmail() const;
    bool isDateIncluded() const;
    QString getDate() const;
    bool isHiringManagerIncluded() const;
    QString getHiringManager() const;
    bool isCompanyNameIncluded() const;
    QString getCompanyName() const;
    void setCompanyName(const QString& name);
    bool isCompanyAddressIncluded() const;
    QString getCompanyAddress() const;
    bool isCompanyLocationIncluded() const;
    QString getCompanyLocation() const;
    void setCompanyLocation(const QString& location);
    QDomElement toXml(QDomDocument& document) const;
    void loadFromFile(const QDomElement& element);

private:
    Ui::PreamblePane *ui;
};

} // namespace preamble
} // namespace cl
} // namespace gui
} // namespace rcl
