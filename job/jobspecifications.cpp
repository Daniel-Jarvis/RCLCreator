#include "jobspecifications.h"
#include "../keyword/keywordmanager.h"
#include "../keyword/keyword.h"

#include <QDebug>

namespace rcl {
namespace job {

JobSpecifications::JobSpecifications(QString jobPosting) {
    int end = jobPosting.indexOf("\n");
    title = jobPosting.first(end);
    int start = end+1;
    end = jobPosting.indexOf("\n&nbsp;\n", start);
    company = jobPosting.mid(start, end-start);
    start = end+8;
    end = jobPosting.indexOf("\n&nbsp;\n", start);
    start = end+8;
    end = jobPosting.indexOf("\n", start);
    location = jobPosting.mid(start, end-start);

    auto keywords = rcl::keyword::KeywordManager::getKeywords();
    for(int i=0; i<keywords.size(); i++){
        rcl::keyword::Keyword* keyword = keywords.at(i);
        if(jobPosting.contains(keyword->getKeywordName()))
            keyword->includeKeyword();
    }
}

QString JobSpecifications::getLocation() const{
    return location;
}

QString JobSpecifications::getTitle() const{
    return title;
}

QString JobSpecifications::getCompany() const{
    return company;
}

} // namespace job
} // namespace rcl
