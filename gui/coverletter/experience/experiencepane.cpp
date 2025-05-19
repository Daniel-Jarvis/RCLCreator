#include "experiencepane.h"
#include "ui_experiencepane.h"

namespace rcl {
namespace gui {
namespace cl {
namespace experience {

ExperiencePane::ExperiencePane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExperiencePane)
{
    ui->setupUi(this);
}

ExperiencePane::~ExperiencePane()
{
    delete ui;
}

QList<Experience *> ExperiencePane::getExperinces() const{
    QList<Experience*> list(ui->experiencesLayout->count());
    for(int i=0; i<ui->experiencesLayout->count(); i++){
        list[i] = qobject_cast<Experience*>(ui->experiencesLayout->itemAt(i)->widget());
    }
    return list;
}

QList<Experience *> ExperiencePane::getIncludedExperinces() const{
    QList<Experience*> list;
    for(int i=0; i<ui->experiencesLayout->count(); i++){
        Experience* experience = qobject_cast<Experience*>(ui->experiencesLayout->itemAt(i)->widget());
        if(experience->isIncluded())
            list.append(experience);
    }
    return list;
}

QDomElement ExperiencePane::toXml(QDomDocument &document) const{
    QDomElement experiencesRoot = document.createElement("Experiences");
    auto experiences = getExperinces();
    for(int i=0; i<experiences.size(); i++){
        experiencesRoot.appendChild(experiences.at(i)->toXml(document));
    }
    return experiencesRoot;
}

void ExperiencePane::loadFromFile(const QDomElement &element){
    QDomElement experienceElement = element.firstChildElement();
    while(!experienceElement.isNull()){
        Experience* newExperience = createAndAddExperience();
        newExperience->loadFromFile(experienceElement);
        experienceElement = experienceElement.nextSiblingElement();
    }

    for(int i=0; i<ui->experiencesLayout->count(); i++){
        qobject_cast<ShiftableWidget*>(ui->experiencesLayout->itemAt(i)->widget())->setShiftWidgetVisibility();
    }
}

void ExperiencePane::on_addExperienceBtn_clicked(){
    Experience* newExperience = createAndAddExperience();
    newExperience->setShiftWidgetVisibility();

    int prevIndex = ui->experiencesLayout->count()-2;
    if(prevIndex >= 0)
        qobject_cast<ShiftableWidget*>(ui->experiencesLayout->itemAt(prevIndex)->widget())->setShiftWidgetVisibility();
}

Experience *ExperiencePane::createAndAddExperience(){
    Experience* newExperience = new Experience(this, ui->experiencesLayout);
    QPushButton* shiftUpBtn = newExperience->getShiftUpButton();
    connect(shiftUpBtn, &QPushButton::clicked, this, [this, newExperience](){
        newExperience->shiftWidgetUp();
    });
    QPushButton* shiftDownBtn = newExperience->getShiftDownButton();
    connect(shiftDownBtn, &QPushButton::clicked, this, [this, newExperience](){
        newExperience->shiftWidgetDown();
    });
    ui->experiencesLayout->addWidget(newExperience);
    return newExperience;
}


} // namespace experience
} // namespace cl
} // namespace gui
} // namespace rcl
