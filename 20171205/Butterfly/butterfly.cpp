#include "butterfly.h"
#include <math.h>
const static double PI= 3.1416;

Butterfly::Butterfly(QObject *parent) : QObject(parent)
{
    up = true;                              //给标志蝴蝶翅膀位置的变量赋初值
    pix_up.load("up.png");                  //调用QPixmap函数的load函数加载所用到的图片
    pix_down.load("down.png");              //调用QPixmap函数的load加载所用到的图片
    startTimer(1000);
}

void Butterfly::timerEvent(QTimerEvent *)
{
    //边界控制
    qreal edgex = scene()->sceneRect().right()+boundingRect().width()/2;       //限定蝴蝶飞舞的右边界
    qreal edgetop = scene()->sceneRect().top()+boundingRect().height()/2;       //限定蝴蝶飞舞的上边界
    qreal edgebottom = scene()->sceneRect().bottom()+boundingRect().height()/2; //限定蝴蝶飞舞的下边界
    if(pos().x()>=edgex)                                                        //如果超过了右边界
    {
        setPos(scene()->sceneRect().left(),pos().y());
    }
    if(pos().y()<=edgetop)                                                      //如果超过了上边界
    {
        setPos(pos().x(),scene()->sceneRect().bottom());                        //垂直移到下边界处
    }
    if(pos().y()>=edgebottom)
    {
        setPos(pos().y(),scene()->sceneRect().top());
    }
    angle += (qrand()%10)/20.0;
    qreal dx = fabs(sin(angle*PI)*10.0);
    qreal dy = (qrand()%20)-10.0;
    setPos(mapToParent(dx,dy));

}

QRectF Butterfly::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-pix_up.width()/2-adjust,-pix_up.height()/2-adjust,
                  pix_up.width()+adjust*2,pix_up.height()+adjust*2);
}

void Butterfly::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(up)
    {
        painter->drawPixmap(boundingRect().topLeft(),pix_up);
        up!=up;
    }
    else{
        painter->drawPixmap(boundingRect().topLeft(),pix_down);
    }
}
