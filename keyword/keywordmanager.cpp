#include "keywordmanager.h"

#include <QFile>
#include <QDomDocument>
#include <QDebug>

namespace rcl {
namespace keyword {

KeywordManager::KeywordManager() {
    load();
}

KeywordManager::~KeywordManager(){
    save();
    for(int i=0; i<keywords.size(); i++){
        delete keywords.at(i);
    }
    keywords.clear();
}

Keyword* KeywordManager::addKeyword(const QString &name){
    return get().addKeywordImpl(name);
}

bool KeywordManager::hasKeyword(const QString &name){
    return get().hasKeywordImpl(name);
}

Keyword *KeywordManager::getKeyword(const QString &name){
    return get().getKeywordImpl(name);
}

QList<Keyword *> KeywordManager::getKeywords(){
    return get().getKeywordsImpl();
}

void KeywordManager::save(){
    get().saveImpl();
}

KeywordManager &KeywordManager::get(){
    static KeywordManager instance;
    return instance;
}

QList<Keyword *> KeywordManager::getKeywordsImpl() const{
    return keywords;
}

void KeywordManager::saveImpl() const{
    QDomDocument document;
    QDomProcessingInstruction xmlDecl = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    document.appendChild(xmlDecl);

    QDomElement keywordsRoot = document.createElement("Keywords");
    document.appendChild(keywordsRoot);

    //save the header
    for(int i=0; i<keywords.size(); i++){
        QDomElement keywordElement = document.createElement("Keyword");
        keywordElement.appendChild(document.createTextNode(keywords.at(i)->getKeywordName()));
        keywordsRoot.appendChild(keywordElement);
    }

    //write to the file
    QFile outFile(qgetenv("userdata.path") + "/keywords.xml");
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qInfo() << "failed to write keywords to file";
        return;
    }
    QTextStream outStream(&outFile);
    outStream << document.toString(4);
    outFile.close();
    qInfo() << "Saved keywords";
}

void KeywordManager::load(){
    QFile inFile(qgetenv("userdata.path") + "/keywords.xml");
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qInfo() << "failed to read saved keyword file";
        return;
    }
    QDomDocument document;
    if(!document.setContent(&inFile)){
        qInfo() << "failed to load saved keyword file";
    }
    inFile.close();

    qInfo() << "loaded keywords";

    //load the keywords
    QDomElement keywordElement = document.documentElement().firstChildElement();
    while(!keywordElement.isNull()){
        addKeywordImpl(keywordElement.text());
        keywordElement = keywordElement.nextSiblingElement();
    }

}

bool KeywordManager::hasKeywordImpl(const QString &name) const{
    for(int i=0; i< keywords.size(); i++){
        if(keywords.at(i)->getKeywordName() == name)
            return true;
    }
    return false;
}

Keyword *KeywordManager::getKeywordImpl(const QString &name) const{
    for(int i=0; i<keywords.size(); i++){
        if(keywords.at(i)->getKeywordName() == name)
            return keywords[i];
    }
    return nullptr;
}

Keyword *KeywordManager::addKeywordImpl(const QString &name){
    if(!hasKeywordImpl(name)){
        Keyword* newKeyword = new Keyword(name);
        keywords.append(newKeyword);
        return newKeyword;
    }
    return nullptr;
}



} // namespace keyword
} // namespace rcl
