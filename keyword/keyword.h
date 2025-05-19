#pragma once

#include "keywordlistener.h"

#include <QList>

namespace rcl {
namespace keyword {

class Keyword
{
public:
    Keyword(QString name);
    QString getKeywordName() const;
    void setKeywordName(const QString name);
    void includeKeyword();
    void addListener(KeywordListener* listener);
    void removeListener(KeywordListener* listener);

private:
    QString keywordName;
    QList<KeywordListener*> listeners;
};

} // namespace keyword
} // namespace rcl
