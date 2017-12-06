#ifndef PIXITEM_H
#define PIXITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class PixItem : public QGraphicsItem
{
public:
    PixItem();
    PixItem(QPixmap *pixmap);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap pix;                                        //作为图元显示图片的图片
};

#endif // PIXITEM_H
