#pragma once

#include <QObject>
#include <QPlainTextEdit>

namespace rcl {
namespace gui {

class ResizeEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit ResizeEventFilter(QObject *parent = nullptr, QPlainTextEdit* editor = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QPlainTextEdit* editor;
};

} // namespace gui
} // namespace rcl
