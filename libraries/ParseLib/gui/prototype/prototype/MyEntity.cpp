#include "myentity.h"
#include <QDebug>
#include <QPainter>






void MyEntity::Center(QPointF point)
{
    int xDisplacement = boundingRect().x() + boundingRect().width()/2;
    int yDisplacement = boundingRect().y() + boundingRect().height()/2;

    QPointF new_point = QPointF(point.x() + xDisplacement, point.y() + yDisplacement);

    for(int32_t i=0; i < relationship.size(); ++i)
    {
        QPointF point1 = p1[i] ? new_point : relationship[i]->line().p1();
        QPointF point2 = p1[i] ? relationship[i]->line().p2() : new_point;

        this->relationship[i]->setLine(QLineF(point1, point2));
    }

}



MyEntity::MyEntity(std::string entity_name_arg, QPointF rect_arg)
{
    this->entity_name = entity_name_arg;
    this->origin = rect_arg;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}


QRectF MyEntity::boundingRect() const
{
    QRectF rect(origin, QPointF(origin.x() + 125, origin.y() + 125));
    return rect;
}

void MyEntity::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setPen(QPen(Qt::black, 1));
    painter->setFont(QFont("Arial", 20));
    painter->drawRect(boundingRect());
    painter->drawText(QPointF(origin.x() + 7, origin.y() + 20), entity_name.c_str());
    painter->drawLine(QPointF( origin.x() + 0, origin.y() + 25), QPointF( origin.x() + 125, origin.y() + 25));

}


QVariant MyEntity::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene())
    {
        QPointF point = value.toPointF();

        Center(point);
    }

    return QGraphicsItem::itemChange(change,value);
}

void MyEntity::AddLine(QGraphicsLineItem * line, bool b_p1)
{
    relationship.push_back(line);
    p1.push_back(b_p1);
}
