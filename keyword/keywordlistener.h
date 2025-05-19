#pragma once

#include <QObject>

namespace rcl {
namespace keyword {

class KeywordListener : public QObject
{
    Q_OBJECT
public:
    explicit KeywordListener(QObject *parent = nullptr);
    void triggerInclusion();

signals:
    void included();
};

} // namespace keyword
} // namespace rcl
