#include "keywordowner.h"

namespace rcl::keyword {

KeywordOwner::KeywordOwner(){
    keywordsListener = new KeywordListener;
}

KeywordOwner::~KeywordOwner(){
    delete keywordsListener;
}

void rcl::keyword::KeywordOwner::associateKeyword(Keyword *keyword){
    associatedKeywords.append(keyword);
    keyword->addListener(keywordsListener);
}

void KeywordOwner::disassociateKeyword(Keyword *keyword){
    associatedKeywords.remove(associatedKeywords.indexOf(keyword));
    keyword->removeListener(keywordsListener);
}

bool KeywordOwner::isAssociatedKeyword(Keyword *keyword) const{
    return associatedKeywords.contains(keyword);
}

const QList<Keyword *> &KeywordOwner::getAssociatedKeywords() const{
    return associatedKeywords;
}

}
