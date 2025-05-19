#pragma once

#include "deletablewidget.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace rcl {
namespace gui {

class ShiftableWidget : public DeletableWidget
{
    Q_OBJECT
public:
    ShiftableWidget(QWidget *parent = nullptr, QVBoxLayout* owningLayout = nullptr);
    virtual QPushButton* getShiftUpButton() const = 0;
    virtual QPushButton* getShiftDownButton() const = 0;
    void shiftWidgetUp();
    void shiftWidgetDown();
    void setShiftWidgetVisibility();

private:
    QVBoxLayout* owningLayout;

};

} // namespace gui
} // namespace rcl
