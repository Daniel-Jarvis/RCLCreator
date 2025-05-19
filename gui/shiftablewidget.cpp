#include "shiftablewidget.h"

namespace rcl {
namespace gui {

ShiftableWidget::ShiftableWidget(QWidget *parent, QVBoxLayout* owningLayout): DeletableWidget{parent}, owningLayout(owningLayout) {}

void ShiftableWidget::shiftWidgetUp(){
    int oldIdx = owningLayout->indexOf(this);
    if(oldIdx == 0 || oldIdx == -1)
        return;

    ShiftableWidget* otherWidget = qobject_cast<ShiftableWidget*>(owningLayout->itemAt(oldIdx-1)->widget());

    owningLayout->removeWidget(this);
    owningLayout->insertWidget(oldIdx-1, this);
    setShiftWidgetVisibility();
    otherWidget->setShiftWidgetVisibility();
}

void ShiftableWidget::shiftWidgetDown(){
    int oldIdx = owningLayout->indexOf(this);
    if(oldIdx == owningLayout->count()-1 || oldIdx == -1)
        return;

    ShiftableWidget* otherWidget = qobject_cast<ShiftableWidget*>(owningLayout->itemAt(oldIdx+1)->widget());

    owningLayout->removeWidget(this);
    owningLayout->insertWidget(oldIdx+1, this);
    setShiftWidgetVisibility();
    otherWidget->setShiftWidgetVisibility();
}

void ShiftableWidget::setShiftWidgetVisibility(){
    int index = owningLayout->indexOf(this);
    if(index == 0){
        getShiftUpButton()->setVisible(false);
    }
    if(index == owningLayout->count()-1){
        getShiftDownButton()->setVisible(false);
    }
    if(index > 0){
        getShiftUpButton()->setVisible(true);
    }
    if(index < owningLayout->count()-1 && owningLayout->count() > 1){
        getShiftDownButton()->setVisible(true);
    }
}

} // namespace gui
} // namespace rcl
