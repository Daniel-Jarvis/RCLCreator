#include "preamblepane.h"
#include "ui_preamblepane.h"

#include <QDate>

namespace rcl {
namespace gui {
namespace cl {
namespace preamble {

PreamblePane::PreamblePane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PreamblePane)
{
    ui->setupUi(this);
    //TODO; set the date field to the current date
    ui->dateEdit->setText(QDate::currentDate().toString("dd MMMM yyyy"));
}

PreamblePane::~PreamblePane()
{
    delete ui;
}

bool PreamblePane::isNameIncluded() const{
    return ui->includeNameBox->isChecked();
}

QString PreamblePane::getName() const{
    return ui->nameEdit->text();
}

bool PreamblePane::isPersonalLocationIncluded() const{
    return ui->includePersonalLocationBox->isChecked();
}

QString PreamblePane::getPersonalLocation() const{
    return ui->personalLocationEdit->text();
}

bool PreamblePane::isPhoneNumberIncluded() const{
    return ui->includePhoneNumberBox->isChecked();
}

QString PreamblePane::getPhoneNumber() const{
    return ui->phoneNumberEdit->text();
}

bool PreamblePane::isEmailIncluded() const{
    return ui->includeEmailBox->isChecked();
}

QString PreamblePane::getEmail() const{
    return ui->emailEdit->text();
}

bool PreamblePane::isDateIncluded() const{
    return ui->includeDateBox->isChecked();
}

QString PreamblePane::getDate() const{
    return ui->dateEdit->text();
}

bool PreamblePane::isHiringManagerIncluded() const{
    return ui->includeManagerBox->isChecked();
}

QString PreamblePane::getHiringManager() const{
    return ui->managerEdit->text();
}

bool PreamblePane::isCompanyNameIncluded() const{
    return ui->includeCompanyNameBox->isChecked();
}

QString PreamblePane::getCompanyName() const{
    return ui->companyNameEdit->text();
}

void PreamblePane::setCompanyName(const QString &name){
    ui->companyNameEdit->setText(name);
}

bool PreamblePane::isCompanyAddressIncluded() const{
    return ui->includeCompanyAddressBox->isChecked();
}

QString PreamblePane::getCompanyAddress() const{
    return ui->companyAddressEdit->text();
}

bool PreamblePane::isCompanyLocationIncluded() const{
    return ui->includeCompanyLocationBox->isChecked();
}

QString PreamblePane::getCompanyLocation() const{
    return ui->companyLocationEdit->text();
}

void PreamblePane::setCompanyLocation(const QString &location){
    ui->companyLocationEdit->setText(location);
}

QDomElement PreamblePane::toXml(QDomDocument &document) const{
    QDomElement propertiesRoot = document.createElement("Preamble");
    propertiesRoot.setAttribute("name", getName());
    propertiesRoot.setAttribute("location", getPersonalLocation());
    propertiesRoot.setAttribute("phone", getPhoneNumber());
    propertiesRoot.setAttribute("email", getEmail());
    return propertiesRoot;
}

void PreamblePane::loadFromFile(const QDomElement &element){
    ui->nameEdit->setText(element.attribute("name", ""));
    ui->personalLocationEdit->setText(element.attribute("location", ""));
    ui->phoneNumberEdit->setText(element.attribute("phone", ""));
    ui->emailEdit->setText(element.attribute("email", ""));
}

} // namespace preamble
} // namespace cl
} // namespace gui
} // namespace rcl
