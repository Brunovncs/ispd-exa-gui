#ifndef ICON_H
#define ICON_H

#include "qgraphicsscene.h"
#include <QGraphicsItem>
#include <QLabel>
#include <QObject>
#include <QVector>
#include <map>
#include <string>
#include <QDialog>
#include "window/machineconfiguration.h"

class Link;

// Define a estrutura para armazenar as configurações do ícone
struct IconConfiguration {
    QString CompPower_lineEdit;
    QString cores_lineEdit;
    QString energyconsumer_lineEdit;
    QString labelEdit;
    QString lineEdit_4;
    QString loadFactor_lineEdit;
    QString primarystorage_lineEdit;
    QString secondaryStorage_lineEdit;

    int comboBoxIndex;
    bool checkBoxState;
    // Adicione mais campos aqui, se necessário
    IconConfiguration() : comboBoxIndex(0), checkBoxState(false) {
        // Define os valores iniciais dos campos conforme necessário
        labelEdit = ""; // Por exemplo, defina uma string vazia como valor inicial para textValue
        CompPower_lineEdit = "";
        cores_lineEdit = "";
        energyconsumer_lineEdit = "";
        lineEdit_4 = "";
        loadFactor_lineEdit = "";
        primarystorage_lineEdit = "";
        secondaryStorage_lineEdit = "";
    }
};

class Icon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Icon(const char *name, QGraphicsItem *parent = nullptr);
    ~Icon();
    Icon(QPixmap pixmap, QGraphicsItem *parent = nullptr);
    void             setOutputLabel(QLabel *label);
    std::map<unsigned, Link *> *links;
    std::string     *getName();
    bool             isSelected;
    unsigned         id;

    std::string iconPath;
    std::string iconPathSelected;

    void deselect();

    // Funções para salvar e carregar as configurações do ícone
    void saveConfiguration();
    void loadConfiguration();
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void         updatePosition();
    void         select();
    QString      positionString;
    QLabel      *outputLabel;
    std::string *name;
    IconConfiguration configuration; // Adicione o membro de dados para armazenar a configuração
signals:
};

#endif
