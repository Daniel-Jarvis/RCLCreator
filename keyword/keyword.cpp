#include "keyword.h"

namespace rcl {
namespace keyword {

Keyword::Keyword(QString name) : keywordName(name) {}

QString Keyword::getKeywordName() const{
    return keywordName;
}

void Keyword::setKeywordName(const QString name){
    keywordName = name;
}

void Keyword::includeKeyword(){
    for(int i=0; i<listeners.size(); i++){
        listeners.at(i)->triggerInclusion();
    }
}

void Keyword::addListener(KeywordListener* listener){
    if(!listeners.contains(listener))
        listeners.append(listener);
}

void Keyword::removeListener(KeywordListener* listener){
    if(listeners.contains(listener))
        listeners.remove(listeners.indexOf(listener));
}

} // namespace keyword
} // namespace rcl
