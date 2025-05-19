#include "deletablewidget.h"

#include <QMenu>
#include <QTimer>

namespace rcl {
namespace gui {

DeletableWidget::DeletableWidget(QWidget *parent)
    : QWidget{parent}{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &DeletableWidget::showCustomContextMenu);
}

DeletableWidget::~DeletableWidget(){

}

void DeletableWidget::showCustomContextMenu(const QPoint &location){
    QMenu* contextMenu = new QMenu("Detail Menu", this);
    QAction* deleteAction = new QAction("delete", contextMenu);
    connect(deleteAction, &QAction::triggered, this, &QObject::deleteLater);
    contextMenu->addAction(deleteAction);
    contextMenu->popup(mapToGlobal(location));
}

} // namespace gui
} // namespace rcl
