#pragma once

#include "keyword.h"

#include <QList>

namespace rcl {
namespace keyword {

class KeywordManager
{
public:
    ~KeywordManager();
    static Keyword* addKeyword(const QString& name);
    static bool hasKeyword(const QString& name);
    static Keyword* getKeyword(const QString& name);
    static QList<Keyword*> getKeywords();
    static void save();

private:
    QList<Keyword*> keywords;
    KeywordManager();
    static KeywordManager& get();
    Keyword* addKeywordImpl(const QString& name);
    bool hasKeywordImpl(const QString& name) const;
    Keyword* getKeywordImpl(const QString& name) const;
    QList<Keyword*> getKeywordsImpl() const;
    void saveImpl() const;
    void load();
};

} // namespace keyword
} // namespace rcl
