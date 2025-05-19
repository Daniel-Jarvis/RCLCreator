#pragma once

#include <QWidget>

namespace rcl {
namespace gui {

class DeletableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeletableWidget(QWidget *parent = nullptr);
    virtual ~DeletableWidget();

protected slots:
    virtual void showCustomContextMenu(const QPoint &location);
};

} // namespace gui
} // namespace rcl
