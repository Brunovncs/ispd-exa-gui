#include "item/icon.h"
#include "item/link.h"
#include "utils/iconSize.h"
#include <QDebug>
#include <QGraphicsScene>

Icon::Icon(const char *name, QGraphicsItem *parent)
    : QGraphicsPixmapItem{parent}
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->name  = new std::string(name);
    this->links = new QVector<Link *>();
    this->isSelected = false;
}

/*
 * Configure the event of clicking the item to print the position of it and select it.
 */
void Icon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "(" << this->pos().x() << " , " << this->pos().y() << ")"
             << "\n";

    QGraphicsPixmapItem::mousePressEvent(event);

    select();

    this->updatePosition();
}

void Icon::updatePosition()
{
    QString pos_string =
        QString("Position: %1, %2").arg(this->pos().x()).arg(this->pos().y());

    if (outputLabel) {
        outputLabel->setText(pos_string);
    }
}

void Icon::setOutputLabel(QLabel *label)
{
    this->outputLabel = label;
}

/*
 * Configure the event of releasing the mouse to check if the item is
 * inside its scene, if it's not, move it inside.
 */
void Icon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    auto pos    = this->pos();
    auto height = this->scene()->sceneRect().height();
    auto width  = this->scene()->sceneRect().width();

    if (pos.x() <= 0) {
        this->moveBy(-pos.x(), 0);
    }

    if (pos.y() <= 0) {
        this->moveBy(0, -pos.y());
    }

    if (pos.x() > width) {
        this->moveBy(-(pos.x() - width), 0);
    }

    if (pos.y() > height) {
        this->moveBy(0, -(pos.y() - height));
    }

    updatePosition();
    for (auto link = links->begin(); link != links->end(); link++) {
        (*link)->updatePositions();
    }
}

std::string *Icon::getName()
{
    return this->name;
}

void Icon::select() {
    if (!isSelected) {
        isSelected = true;

        auto pixmap =
            QPixmap::fromImage(QImage(this->iconPathSelected.c_str())).scaled(iconSelectSize);
        this->setPixmap(pixmap);
    } else {
        isSelected = false;
        auto pixmap =
            QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);
        this->setPixmap(pixmap);
    }
}