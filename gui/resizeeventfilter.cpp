#include "resizeeventfilter.h"
#include "gui_utils.h"

#include <QEvent>
#include <QDebug>

namespace rcl {
namespace gui {

ResizeEventFilter::ResizeEventFilter(QObject *parent, QPlainTextEdit* editor)
    : QObject{parent}, editor(editor)
{}

bool ResizeEventFilter::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::Resize){
        resizePlainTextArea(editor);
        //TODO: should probably optimize so it only runs when there is a change text display
    }
    return QObject::eventFilter(obj, event);
}

} // namespace gui
} // namespace rcl
