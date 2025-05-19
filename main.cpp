#include "launchwindow.h"
#include "boot/property.h"

#include <QApplication>


int main(int argc, char *argv[]){
    loadProperties();
    QApplication a(argc, argv);
    LaunchWindow w;
    w.show();
    return a.exec();
}
