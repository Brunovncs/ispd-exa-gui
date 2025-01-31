#include "window/drawingtable/drawingtable.h"
#include "components/conf/machineconfiguration.h"
#include "components/conf/schemaconfiguration.h"
#include "components/connectable.h"
#include "components/link.h"
#include "components/machine.h"
#include "components/schema.h"
#include "components/switch.h"
#include "utils/iconSize.h"
#include "window/drawingtable/scene.h"
#include "window/users.h"
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

void printSchema(Schema *schema);

DrawingTable::DrawingTable(QFrame *parent) : DrawingTable(new Schema(), parent)
{
    QPixmap image(":/icons/perfil.png");
    QSize   imageSize(30, 30);
    QPixmap resizedImage =
        image.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    openUserWindow = new QPushButton(this);
    openUserWindow->setIcon(QIcon(resizedImage));
    openUserWindow->setIconSize(image.size());
    openUserWindow->setFixedSize(40, 40);

    //----------------------------------------------------------------------------------------

    QPixmap image_2(":/icons/engine.png");
    QSize   imageSize_2(30, 30);
    QPixmap resizedImage_2 = image_2.scaled(
        imageSize_2, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    openSimulationWindow = new QPushButton("Simulate", this);
    openSimulationWindow->setIcon(QIcon(resizedImage_2));
    openSimulationWindow->setIconSize(imageSize_2);

    openSimulationWindow->setFixedSize(100, 40);

    //----------------------------------------------------------------------------------------

    buttonsLayout->addWidget(openUserWindow, 0, Qt::AlignRight);
    buttonsLayout->addWidget(openSimulationWindow, 0, Qt::AlignRight);

    connect(openUserWindow,
            &QPushButton::clicked,
            this,
            &DrawingTable::openUserWindowClicked);
    connect(openSimulationWindow,
            &QPushButton::clicked,
            this,
            &DrawingTable::openSimulationWindowClicked);
}

DrawingTable::DrawingTable(Schema *schema, QWidget *parent) : QWidget{parent}
{
    this->schema = schema;
    this->view   = new View(this);
    this->scene  = new Scene(this);
    this->view->setGScene(scene);
    this->buttonsRow    = new QWidget(this);
    this->buttonsLayout = new QHBoxLayout(buttonsRow);
    this->buttonsLayout->setAlignment(Qt::AlignLeft);

    this->setupNoneButton();
    this->setupPcButton();
    this->setupSchemaButton();
    this->setupSetButton();
    this->setupLinkButton();
    this->setupSwitchButton();

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(buttonsRow);
    mainLayout->addWidget(view);
}

void DrawingTable::receiveUserWindowData(const QList<QString> &list1Data,
                                         const QList<double>  &list2Data)
{
    /* this->list1Data = list1Data; */
    /* this->list2Data = list2Data; */
}

///
/// @brief Creates the PC option button and connects it to the scene
///
void DrawingTable::setupPcButton()
{
    this->pcButton = new QRadioButton(this->buttonsRow);
    this->pcButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/pc.png"))));
    this->pcButton->setIconSize(buttonSize);
    this->buttonsLayout->addWidget(pcButton);
    QObject::connect(
        pcButton, &QRadioButton::clicked, this, &DrawingTable::pcButtonClicked);
}

void DrawingTable::setupSetButton()
{
    this->setButton = new QRadioButton(this->buttonsRow);
    this->setButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/connectableset.png"))));
    this->setButton->setIconSize(buttonSize);
    this->buttonsLayout->addWidget(setButton);
    QObject::connect(
        setButton, &QRadioButton::clicked, this, &DrawingTable::setButtonClicked);
}

///
/// @brief Creates the Cursor option button and connects it to the scene
///
void DrawingTable::setupNoneButton()
{
    noneButton = new QRadioButton(buttonsRow);
    noneButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/cursor.png"))));
    noneButton->setIconSize(buttonSize);
    buttonsLayout->addWidget(noneButton);
    QObject::connect(noneButton,
                     &QRadioButton::clicked,
                     this,
                     &DrawingTable::noneButtonClicked);
}

///
/// @brief Creates the Switch option button and connects it to the scene
///
void DrawingTable::setupSwitchButton()
{
    noneButton = new QRadioButton(buttonsRow);
    noneButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/switch.svg"))));
    noneButton->setIconSize(buttonSize);
    buttonsLayout->addWidget(noneButton);
    QObject::connect(noneButton,
                     &QRadioButton::clicked,
                     this,
                     &DrawingTable::switchButtonClicked);
}

///
/// @brief Creates the Schema option button and connects it to the scene
///
void DrawingTable::setupSchemaButton()
{

    schemaButton = new QRadioButton(buttonsRow);
    schemaButton->setIcon(
        QIcon(QPixmap::fromImage(QImage(":icons/cluster.png"))));
    schemaButton->setIconSize(buttonSize);
    buttonsLayout->addWidget(schemaButton);
    QObject::connect(schemaButton,
                     &QRadioButton::clicked,
                     this,
                     &DrawingTable::schemaButtonClicked);
}

///
/// @brief Creates the Link option button and connects it to the scene
///
void DrawingTable::setupLinkButton()
{
    const QIcon linkIcon(QPixmap::fromImage(QImage(":icons/connection.png")));

    linkButton = new QRadioButton(buttonsRow);
    linkButton->setIcon(linkIcon);
    linkButton->setIconSize(buttonSize);
    buttonsLayout->addWidget(linkButton);
    QObject::connect(linkButton,
                     &QRadioButton::clicked,
                     this,
                     &DrawingTable::linkButtonClicked);
}

///
/// @brief  Creates a Machine inside the DrawingTable's Schema
///
/// @return the machine's icon
///
PixmapIcon *DrawingTable::addMachine()
{
    const unsigned machineId = schema->allocateNewMachine();

    return schema->connectables.at(machineId)->getIcon();
}

///
/// @brief  Creates a Switch inside the DrawingTable's Schema
///
/// @return the switch's icon
///
PixmapIcon *DrawingTable::addSwitch()
{
    const unsigned switchId = schema->allocateNewSwitch();

    // FOR DEBUG
    printSchema(schema);

    return schema->connectables.at(switchId)->getIcon();
}

///
/// @brief  Creates a Schema inside the DrawingTable's Schema
///
/// @return the schema's icon
///
PixmapIcon *DrawingTable::addSchema()
{
    const unsigned schemaId = schema->allocateNewSchema();

    // FOR DEBUG
    printSchema(schema);

    return schema->connectables.at(schemaId)->getIcon();
}

PixmapIcon *DrawingTable::addSet()
{
    const unsigned schemaId = schema->allocateNewSet();

    // FOR DEBUG
    printSchema(schema);

    return schema->connectables.at(schemaId)->getIcon();
}

///
/// @brief  Creates a Link inside the DrawingTable's Schema
///
/// @return the link's line
///
Link *DrawingTable::addLink(LinkConnections connections)
{
    const unsigned linkId = schema->allocateNewLink(connections);

    // FOR DEBUG
    printSchema(schema);

    return schema->links.at(linkId).get();
}

///
/// @brief  set the scene operator to the PC insert mode
///
void DrawingTable::pcButtonClicked()
{
    this->scene->pickOp = PC;
}

void DrawingTable::setButtonClicked()
{
    this->scene->pickOp = SET;
}

///
/// @brief  set the scene operator to the switch insert mode
///
void DrawingTable::switchButtonClicked()
{
    this->scene->pickOp = SWITCH;
}

///
/// @brief  set the scene operator to the click mode
///
void DrawingTable::noneButtonClicked()
{
    this->scene->pickOp = NONE;
}

///
/// @brief  set the scene operator to the link insert mode
///
void DrawingTable::linkButtonClicked()
{
    this->scene->pickOp = LINK;
}

///
/// @brief  set the scene operator to the schema insert mode
///
void DrawingTable::schemaButtonClicked()
{
    this->scene->pickOp = SCHEMA;
}

///
/// @brief  prints the DrawingTable's Schema and its components
///
void printSchema(Schema *schema)
{
    for (auto machine = schema->connectables.begin();
         machine != schema->connectables.end();
         machine++) {

        qDebug() << "Connectable #" << machine->second->getId()
                 << ": " << machine->second->getConf()->getName().c_str();
    }

    for (auto &[id, nswitch] : schema->connectables) {

        qDebug() << "Connectable #" << id << ": "
                 << nswitch->getConf()->getName().c_str();
    }

    for (auto sch = schema->connectables.begin();
         sch != schema->connectables.end();
         sch++) {

        qDebug() << "Connectable #" << sch->second->getId() << ": "
                 << sch->second->getConf()->getName().c_str();
    }

    for (auto link = schema->links.begin(); link != schema->links.end();
         link++) {

        qDebug() << "Link #" << link->second->getId() << ": "
                 << link->second->conf->getName().c_str();
    }
}
void DrawingTable::openUserWindowClicked()
{
    /* this->userWindow = */
    /*     new UserWindow(nullptr, */
    /*                    this, */
    /*                    list1Data, */
    /*                    list2Data); // Pass the lists to UserWindow
     * constructor */

    userWindow->show();
}

void DrawingTable::openSimulationWindowClicked()
{
    this->simulationWindow = new Simulation();
    simulationWindow->show();
}

void DrawingTable::addIcons(std::vector<Connectable *> *items)
{
    for (auto it : *items) {
        this->scene->addIcon(static_cast<PixmapIcon *>(it->getIcon()),
                             static_cast<PixmapIcon *>(it->getIcon())->pos());
    }
}

Scene *DrawingTable::getScene()
{
    return this->scene;
}
