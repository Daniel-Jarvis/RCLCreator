#include "property.h"
#include <QFile>
#include <QTextStream>

void loadPropertyFromLine(const QString& line){
    QString result;
    QTextStream stream(&result); //I know this is slow, but this is not performance critical
    for(size_t i=0; i<line.size(); i++){
        QChar character = line.at(i);
        if (character == '#'){
            break;
        } else if (character == ' ' || character == '\t'){
            continue;
        }
        stream << character;
    }
    QList<QString> values = result.split('=');
    qputenv(values.at(0).toStdString().c_str(), values.at(1).toStdString().c_str());
}

void loadProperties(){
    // TODO: this needs error checking, not in mvp
    QFile inFile("boot/properties/default.properties");
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream inStream(&inFile);
    while(!inStream.atEnd()){
        QString line = inStream.readLine();
        loadPropertyFromLine(line);
    }
    inFile.close();
}

void validateProperties(){
    //TODO: I still don't know what I want to do with this
}
