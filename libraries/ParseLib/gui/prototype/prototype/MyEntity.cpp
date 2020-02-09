#include "myentity.h"
#include <QDebug>
#include <QPainter>
#include <QtMath>






void MyEntity::FindLineAnchor(QPointF point)
{
    //calculate the center coordinates of the box.
    int xDisplacement = this->boundingRect().x() + this->boundingRect().width()/2;
    int yDisplacement = this->boundingRect().y() + this->boundingRect().height()/2;

    //create a point at the center of the box.
    QPointF entity_center = QPointF(point.x() + xDisplacement, point.y() + yDisplacement);

    for(int32_t i=0; i < _relationship.size(); ++i)
    {
        QPointF point1, point2;

        if(_IsRelationshipOrigin[i])
        {
            point1 = entity_center;
            point2 = _relationship[i]->line().p2();


            if( (point2.x() - point1.x()) > (point2.y() - point1.y()))
            {
                //right
                if(point2.x() > point1.x())
                {
                    point1 = QPointF(point1.x() + this->boundingRect().width()/2, point1.y());
                }
                //left
                else
                {
                    point1 = QPointF(point1.x() - this->boundingRect().width()/2, point1.y());
                }
            }
            else
            {
                //up
                if( point2.y() > point1.y() )
                {
                    point1 = QPointF(point1.x(), point1.y() + this->boundingRect().height()/2);
                }
                //down
                else
                {
                    point1 = QPointF(point1.x(), point1.y() - this->boundingRect().height()/2);
                }
            }

        }
        else
        {
            point1 = _relationship[i]->line().p1();
            point2 = entity_center;


            //adjust the x position
            if( (point2.x() - point1.x()) > (point2.y() - point1.y()) )
            {
                //right
                if( point2.x() < point1.x() )
                {
                    point2 = QPointF(point2.x() + this->boundingRect().width()/2, point2.y());
                }
                //left
                else
                {
                    point2 = QPointF(point2.x() - this->boundingRect().width()/2, point2.y());
                }
            }
            else
            {
                //up
                if( point2.y() < point1.y() )
                {
                    point2 = QPointF(point2.x(), point2.y() + this->boundingRect().height()/2);
                }
                //down
                else
                {
                    point2 = QPointF(point2.x(), point2.y() - this->boundingRect().height()/2);
                }
            }

        }

        this->_relationship[i]->setLine(QLineF(point1, point2));
    }

}



MyEntity::MyEntity(std::string entity_name_arg, QPointF rect_arg)
{
    this->_entity_name = entity_name_arg;
    this->_origin = rect_arg;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}


QRectF MyEntity::boundingRect() const
{
    QRectF rect(_origin, QPointF(_origin.x() + 125, _origin.y() + 125));
    return rect;
}

void MyEntity::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setPen(QPen(Qt::black, 1));
    painter->setFont(QFont("Arial", 20));
    painter->drawRect(boundingRect());
    painter->drawText(QPointF(_origin.x() + 7, _origin.y() + 20), _entity_name.c_str());
    painter->drawLine(QPointF( _origin.x() + 0, _origin.y() + 25), QPointF( _origin.x() + 125, _origin.y() + 25));

}


QVariant MyEntity::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene())
    {
        QPointF point = value.toPointF();

        this->FindLineAnchor(point);
    }

    return QGraphicsItem::itemChange(change,value);
}

void MyEntity::AddLine(QGraphicsLineItem * line, bool b_p1)
{
    _relationship.push_back(line);
    _IsRelationshipOrigin.push_back(b_p1);
}
