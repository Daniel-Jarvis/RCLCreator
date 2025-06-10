#include "property.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

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

PropertyLoadResults loadProperties() noexcept {
    PropertyLoadResults result;

    QFile inFile("boot/properties/default.properties");
    if(!inFile.exists()){
        result.succeeded = false;
        result.reason = "Failed to open file: boot/properties/default.properties since it doesn't exist.";
        return result;
    }

    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        result.succeeded = false;
        result.reason = "Failed to open file: boot/properties/default.properties, even though it exists. Ensure it has read access.";
        return result;
    }

    QTextStream inStream(&inFile);
    while(!inStream.atEnd()){
        QString line = inStream.readLine();
        loadPropertyFromLine(line);
    }
    inFile.close();

    result.succeeded = true;
    result.reason = "";
    return result;
}

PropertyLoadResults validateProperties() noexcept {
    PropertyLoadResults result;
    bool succeeded = true;
    QString reason;
    QTextStream reasonStream(&reason);

    QString userdataPath = qgetenv("userdata.Path");
    if(userdataPath == ""){
        succeeded = false;
        reasonStream << "property userdata.path is not set.\n";
    } else if(!userdataPath.contains(QRegularExpression("^([a-zA-Z]:(\\\\|/)|/)([a-zA-Z+-_.]+(\\\\|/))*$"))){
        succeeded = false;
        reasonStream << "property userdata.path does not define a valid path to a directory without spaces.\n";
    }

    result.succeeded = succeeded;
    result.reason = reason.toStdString();
    return result;
}
