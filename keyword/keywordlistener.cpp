#include "keywordlistener.h"

namespace rcl {
namespace keyword {

KeywordListener::KeywordListener(QObject *parent)
    : QObject{parent}
{}

void KeywordListener::triggerInclusion(){
    emit included();
}

} // namespace keyword
} // namespace rcl
