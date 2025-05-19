#pragma once

#include <QString>

namespace rcl {
namespace job {

class JobSpecifications
{
public:
    JobSpecifications(QString jobPosting);
    QString getLocation() const;
    QString getTitle() const;
    QString getCompany() const;

private:
    QString location;
    QString title;
    QString company;
};

} // namespace job
} // namespace rcl
