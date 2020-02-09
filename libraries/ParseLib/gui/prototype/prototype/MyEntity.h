#ifndef MYENTITY_H
#define MYENTITY_H

#include <QGraphicsItem>

class MyEntity : public QGraphicsItem
{
public:
    MyEntity(std::string, QPointF);

    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void AddLine(QGraphicsLineItem * Line, bool isOrigin);
    void FindLineAnchor(QPointF);

    std::vector<QGraphicsLineItem *> _relationship;
    std::vector<bool> _IsRelationshipOrigin;

    std::string _entity_name;
    QPointF _origin;

};

#endif // MYENTITY_H
