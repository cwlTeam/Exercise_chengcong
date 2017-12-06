#include "pixitem.h"

PixItem::PixItem(QPixmap *pixmap)
{
    pix= *pixmap;
}

QRectF PixItem::boundingRect() const
{
    return QRectF(-2-pix.width()/2,-2-pix.height()/2,pix.width(),pix.height()/2);
}

void PixItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-pix.width()/2,-pix.height()/2,pix);
}
