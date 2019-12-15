#ifndef MYENTITY_H
#define MYENTITY_H

#include <QGraphicsItem>

class MyEntity : public QGraphicsItem
{
public:
    MyEntity(std::string, QPointF);

    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;

    virtual void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget) override;

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    void AddLine(QGraphicsLineItem * Line, bool b_p1);

    void Center(QPointF);

    std::vector<QGraphicsLineItem *> relationship;
    std::vector<bool> p1;

    std::string entity_name;
    QPointF origin;

};

#endif // MYENTITY_H
