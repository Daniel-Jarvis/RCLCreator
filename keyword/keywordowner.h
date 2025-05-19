#pragma once

#include "keyword.h"
#include "keywordlistener.h"

#include <QList>

namespace rcl::keyword{

class KeywordOwner{
public:
    KeywordOwner();
    ~KeywordOwner();
    void associateKeyword(Keyword* keyword);
    void disassociateKeyword(Keyword* keyword);
    bool isAssociatedKeyword(Keyword* keyword) const;
    const QList<Keyword*>& getAssociatedKeywords() const;

protected:
    QList<Keyword*> associatedKeywords;
    KeywordListener* keywordsListener;

};

}
