#include "launchwindow.h"
#include "boot/property.h"

#include <QApplication>
#include <QMessageBox>


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    PropertyLoadResults loadResult = loadProperties();
    if(!loadResult.succeeded){
        QMessageBox::critical(nullptr, "Error Loading Properties", loadResult.reason.c_str());
        return 1;
    }

    PropertyLoadResults validationResult = validateProperties();
    if(!validationResult.succeeded){
        QMessageBox::critical(nullptr, "Error While Validating Properties", validationResult.reason.c_str());
        return 1;
    }

    LaunchWindow w;
    w.show();
    return a.exec();
}
