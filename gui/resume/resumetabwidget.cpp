#include "resumetabwidget.h"
#include "ui_resumetabwidget.h"

#include <QLineEdit>
#include <QPrinter>
#include <QPainter>
#include <QMarginsF>
#include <QList>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>

namespace rcl::gui::resume{

namespace q = qualification;

ResumeTabWidget::ResumeTabWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResumeTabWidget){
    ui->setupUi(this);
    areaSplitter = new QSplitter(this);
    areaSplitter->addWidget(ui->leftWidget);
    areaSplitter->addWidget(ui->resumeScrollArea);
    areaSplitter->addWidget(ui->rightWidget);
    areaSplitter->setChildrenCollapsible(false);
    this->layout()->addWidget(areaSplitter);
    connect(ui->writeResumeBtn, &QPushButton::clicked, this, &ResumeTabWidget::buildResume);
    load();
}

ResumeTabWidget::~ResumeTabWidget(){
    delete ui;
}

void ResumeTabWidget::save() const{
    QDomDocument document;
    QDomProcessingInstruction xmlDecl = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    document.appendChild(xmlDecl);

    QDomElement resumeRoot = document.createElement("ResumeContents");
    document.appendChild(resumeRoot);

    //save the header
    QDomElement headerRoot = ui->resumeHeaderPane->toXml(document);
    resumeRoot.appendChild(headerRoot);

    //save the contents
    QDomElement sectionsRoot = ui->qualificationsScrollAreaWidgetContents->toXml(document);
    resumeRoot.appendChild(sectionsRoot);

    //write to the file
    QFile outFile(qgetenv("userdata.path") + "/resume.xml");
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qInfo() << "failed to write resume tab to file";
        return;
    }
    QTextStream outStream(&outFile);
    outStream << document.toString(4);
    outFile.close();
    qInfo() << "Saved resume tab";
}

void ResumeTabWidget::resumeContentChange(){
    //TODO: this can do more advanced checking, and adds the posibility of not automatically building the resume
    buildResume();
}

void ResumeTabWidget::buildResume(){
    //this will be a much more complicated method later once sizing, bullet points, horizontal lines and what not are implemented
    QString resumeContents = "";
    QTextStream stream(&resumeContents);

    //header of the resume
    stream << "<h1>" << ui->resumeHeaderPane->getName() << "</h1>";
    QList<HeaderElement*> headerElements = ui->resumeHeaderPane->getIncludedElements();
    int i = 0;
    while(i < headerElements.size()){
        stream << headerElements.at(i)->getFormattedText();
        i++;
        if(i != headerElements.size())
            stream << " | ";
    }

    // body of the resume
    auto sections = ui->qualificationsScrollAreaWidgetContents->getIncludedQualifications();
    for(int i=0; i<sections.size(); i++){
        q::ResumeQualificationSection* section = qobject_cast<q::ResumeQualificationSection*>(sections.at(i));
        if(section->isIncluded()){
            stream << "<hr>";
            stream << "<h2>" << section->getSectionTitle() << "</h2>" ;
            QList<q::ResumeQualificationSubsection*> subsections = section->getIncludedSubsections();

            for(int j=0; j<subsections.size(); j++){
                q::ResumeQualificationSubsection* subsection = subsections.at(j);

                stream << "<p>" << subsection->getDescription().replace("\n", "<br>") << "</p>";
                QList<q::ResumeSubsectionDetail*> details = subsection->getEnabledDetails();
                if(details.isEmpty())
                    continue;

                stream << "<ul>";
                for(int k=0; k<details.size(); k++){
                    q::ResumeSubsectionDetail* detail = details.at(k);
                    stream << "<li>" << detail->getDetailText() << "</li>";
                }
                stream << "</ul>";
            }
        }
    }

    ui->textEdit->setHtml(resumeContents);
}

void ResumeTabWidget::on_printButton_clicked(){
    QString fileName = QFileDialog::getExistingDirectory(this, "Location", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(fileName.isEmpty())
        return;

    QPrinter printer(QPrinter::PrinterMode::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName + "/Resume.pdf");
    printer.setPageSize(QPageSize(QPageSize::A4));


    qreal margin = 18 / 2.54;
    QMarginsF margins(margin, margin, margin, margin);
    QPageLayout layout(QPageSize(QPageSize::A4), QPageLayout::Portrait, margins);
    printer.setPageLayout(layout);

    QTextDocument doc;
    doc.setHtml(ui->textEdit->toHtml());

    QPainter painter(&printer);
    qreal scaleFactor = printer.resolution() / 96.0;
    painter.scale(scaleFactor, scaleFactor);

    QRectF paintRect = printer.pageLayout().paintRectPixels(printer.resolution());
    painter.translate(paintRect.left() / scaleFactor, paintRect.top() / scaleFactor);

    QSizeF docSize = paintRect.size() / scaleFactor;

    doc.setPageSize(docSize);
    doc.drawContents(&painter, QRectF(QPointF(0, 0), docSize));
}

void ResumeTabWidget::load(){
    QFile inFile(qgetenv("userdata.path") + "/resume.xml");
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qInfo() << "failed to read saved resume file";
        return;
    }
    QDomDocument document;
    if(!document.setContent(&inFile)){
        qInfo() << "failed to load saved resume file";
    }
    inFile.close();

    qInfo() << "loaded resume tab";

    // actually load the file
    QDomElement header = document.documentElement().childNodes().at(0).toElement();
    ui->resumeHeaderPane->loadFromFile(header);

    QDomElement sections = header.nextSiblingElement();
    ui->qualificationsScrollAreaWidgetContents->loadFromFile(sections);

}




}
