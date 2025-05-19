#include "coverlettertab.h"
#include "ui_coverlettertab.h"
#include "experience/experience.h"

#include <QDomDocument>
#include <QFile>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>

namespace rcl {
namespace gui {
namespace cl {

CoverLetterTab::CoverLetterTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CoverLetterTab)
{
    ui->setupUi(this);
    areaSplitter = new QSplitter(this);
    areaSplitter->addWidget(ui->leftWidget);
    areaSplitter->addWidget(ui->coverLetterScrollArea);
    areaSplitter->addWidget(ui->rightWidget);
    areaSplitter->setChildrenCollapsible(false);
    this->layout()->addWidget(areaSplitter);

    rightSplitter = new QSplitter(Qt::Orientation::Vertical, this);
    rightSplitter->addWidget(ui->preambleScrollArea);
    rightSplitter->addWidget(ui->propertiesScrollArea);
    ui->rightInternalWidget->layout()->addWidget(rightSplitter);
    load();
}

CoverLetterTab::~CoverLetterTab()
{
    delete ui;
}

void CoverLetterTab::save() const{
    QDomDocument document;
    QDomProcessingInstruction xmlDecl = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    document.appendChild(xmlDecl);

    QDomElement clRoot = document.createElement("CoverLetterContents");
    document.appendChild(clRoot);

    clRoot.appendChild(ui->preambleScrollAreaContents->toXml(document));
    clRoot.appendChild(ui->propertiesScrollAreaContents->toXml(document));
    clRoot.appendChild(ui->experienceScrollAreaContents->toXml(document));

    //write to the file
    QFile outFile(qgetenv("userdata.path") + "/coverletter.xml");
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qInfo() << "failed to write cover letter tab to file";
        return;
    }
    QTextStream outStream(&outFile);
    outStream << document.toString(4);
    outFile.close();
}

void CoverLetterTab::load(){

    QFile inFile(qgetenv("userdata.path") + "/coverletter.xml");
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qInfo() << "failed to read saved cover letter file";
        return;
    }
    QDomDocument document;
    if(!document.setContent(&inFile)){
        qInfo() << "failed to load saved cover letter file";
    }
    inFile.close();

    qInfo() << "loaded cover letter tab";

    // actually load the file
    QDomElement preamble = document.documentElement().childNodes().at(0).toElement();
    ui->preambleScrollAreaContents->loadFromFile(preamble);

    QDomElement properties = preamble.nextSiblingElement();
    ui->propertiesScrollAreaContents->loadFromFile(properties);

    QDomElement experiences = properties.nextSiblingElement();
    ui->experienceScrollAreaContents->loadFromFile(experiences);
}

void CoverLetterTab::importJob(const job::JobSpecifications &job){
    ui->preambleScrollAreaContents->setCompanyLocation(job.getLocation());
    ui->preambleScrollAreaContents->setCompanyName(job.getCompany());
    ui->propertiesScrollAreaContents->loadPropertiesFromJob(job);
}

void CoverLetterTab::on_writeBtn_clicked(){
    buildCoverLetter();
}

void CoverLetterTab::buildCoverLetter(){
    QString coverLetterContents = "";
    QTextStream stream(&coverLetterContents);

    //preamble
    if(ui->preambleScrollAreaContents->isNameIncluded())
        stream << "<p>" << ui->preambleScrollAreaContents->getName() << "</p>";
    if(ui->preambleScrollAreaContents->isPersonalLocationIncluded())
        stream << "<p>" << ui->preambleScrollAreaContents->getPersonalLocation() << "</p>";
    if(ui->preambleScrollAreaContents->isPhoneNumberIncluded())
        stream << "<p>" << ui->preambleScrollAreaContents->getPhoneNumber() << "</p>";
    if(ui->preambleScrollAreaContents->isEmailIncluded())
        stream << "<p>" << ui->preambleScrollAreaContents->getEmail() << "</p>";
    if(ui->preambleScrollAreaContents->isDateIncluded())
        stream << "<p>" << ui->preambleScrollAreaContents->getDate() << "</p>";
    if(ui->preambleScrollAreaContents->isHiringManagerIncluded())
        stream << "<p>" << ui->preambleScrollAreaContents->getHiringManager() << "</p>";
    if(ui->preambleScrollAreaContents->isCompanyNameIncluded())
        stream << "<p>" << ui->preambleScrollAreaContents->getCompanyName() << "</p>";
    if(ui->preambleScrollAreaContents->isCompanyAddressIncluded())
        stream << "<p>" << ui->preambleScrollAreaContents->getCompanyAddress() << "</p>";
    if(ui->preambleScrollAreaContents->isCompanyLocationIncluded())
        stream << "<p>" << ui->preambleScrollAreaContents->getCompanyLocation() << "</p>";

    //sections of the cover letter
    QMap<QString, QString> properties = ui->propertiesScrollAreaContents->getPropertiesMap();

    QList<experience::Experience*> experiences = ui->experienceScrollAreaContents->getIncludedExperinces();
    for(int i=0; i<experiences.size(); i++){
        stream << "<p>" << "\t" << replaceProperties(experiences.at(i)->getContents().replace("\n", "</p><p>"), properties) << "</p>";
    }

    ui->textEdit->setHtml(coverLetterContents);
}

QString CoverLetterTab::replaceProperties(const QString &source, const QMap<QString, QString> &properties){
    QString output = source;
    QList<QString> keys = properties.keys();
    for(int i=0; i<keys.length(); i++){
        QString key = keys.at(i);
        QString value = properties.value(key, "");
        output.replace("${"+key+"}", value);
    }

    return output;
}

void CoverLetterTab::on_printBtn_clicked(){
    QString fileName = QFileDialog::getExistingDirectory(this, "Location", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(fileName.isEmpty())
        return;

    qInfo() <<"printing cover letter to" << fileName;
    QPrinter printer(QPrinter::PrinterMode::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName + "/Cover Letter.pdf");
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



} // namespace cl
} // namespace gui
} // namespace rcl
