#include "mainwindow.h"
#include <QRectF>
#include "flashitem.h"
#include "startitem.h"
#include <QGraphicsItemAnimation>
#include <QTimeLine>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    scene = new QGraphicsScene;
    scene->setSceneRect(-200,-200,400,400);
    initScene();                                    //初始化场景
    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);
    view->setMinimumSize(400,400);
    view->show();
    setCentralWidget(view);
    resize(550,450);
    setWindowTitle(tr("Graphics Items"));
}

MainWindow::~MainWindow()
{

}

void MainWindow::initScene(QWidget *parent)            //初始化场景
{
    int i;
    for(i=0;i<3;i++)
        slotAddEllipseItem();
    for(i=0;i<3;i++)
        slotAddRectItem();
    for(i=0;i<3;i++)
        slotAddTextItem();
    for(i=0;i<3;i++)
        slotAddAlphaItem();
    for(i=0;i<3;i++)
        slotAddFlashItem();
    for(i=0;i<3;i++)
        slotAddAnimationItem();
}

void MainWindow::createActions()                        //创建主窗体所有动作
{
    newAct = new QAction(tr("新建"),this);
    clearAct = new QAction(tr("清除"),this);
    exitAct = new QAction(tr("关闭"),this);
    addEllipseItemAct = new QAction(tr("加入椭圆"),this);
    addPolygonItemAct = new QAction(tr("加入多边形"),this);
    addTextItemAct = new QAction(tr("加入文字"),this);
    addRectItemAct = new QAction(tr("加入长方形"),this);
    addAlphaItemAct = new QAction(tr("加入透明图片"),this);
    addFlashItemAct = new QAction(tr("加入闪烁画面"),this);
    addAnimItemAct = new QAction(tr("加入星星"),this);
    connect(newAct,SIGNAL(triggered(bool)),this,SLOT(slotNew()));
    connect(clearAct,SIGNAL(triggered(bool)),this,SLOT(slotClear()));
    connect(exitAct,SIGNAL(triggered(bool)),this,SLOT(slotExit()));
    connect(addEllipseItemAct,SIGNAL(triggered(bool)),this,SLOT(slotAddEllipseItem()));
    connect(addPolygonItemAct,SIGNAL(triggered(bool)),this,SLOT(slotPolygonIem()));
    connect(addTextItemAct,SIGNAL(triggered(bool)),this,SLOT(slotAddTextItem()));
    connect(addRectItemAct,SIGNAL(triggered(bool)),this,SLOT(slotAddRectItem()));
    connect(addAlphaItemAct,SIGNAL(triggered(bool)),this,SLOT(slotAddAlphaItem()));
    connect(addFlashItemAct,SIGNAL(triggered(bool)),this,SLOT(slotAddFlashItem()));
    connect(addAnimItemAct,SIGNAL(triggered(bool)),this,SLOT(slotAddAnimationItem()));

}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(clearAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    QMenu *itemMenu = menuBar()->addMenu(tr("元素"));
    itemMenu->addAction(addEllipseItemAct);
    itemMenu->addAction(addPolygonItemAct);
    itemMenu->addAction(addTextItemAct);
    itemMenu->addAction(addRectItemAct);
    itemMenu->addAction(addAlphaItemAct);
    itemMenu->addAction(addFlashItemAct);
    itemMenu->addAction(addAnimItemAct);
}

void MainWindow::slotNew()                      //新建一个显示窗体
{
    slotClear();
    initScene();
    MainWindow *newWin = new MainWindow;
    newWin->show();
}

void MainWindow::slotClear()
{
    QList<QGraphicsItem*>listItem = scene->items();
    while(!listItem.empty())
    {
        scene->removeItem(listItem.at(0));
        listItem.removeAt(0);
    }
}

void MainWindow::slotAddEllipseItem()                       //在场景中添加一个椭圆
{
     QGraphicsEllipseItem *item = new QGraphicsEllipseItem(QRectF(0,0,80,60));
     item->setPen(Qt::NoPen);
     item->setBrush(QColor(qrand()/256,qrand()/256,qrand()/256));
     item->setFlag(QGraphicsItem::ItemIsMovable);
     scene->addItem(item);
     item->setPos((qrand()%int(scene->sceneRect().width()))-200,
                  (qrand()%int(scene->sceneRect().height()))-200);

}

void MainWindow::slotPolygonIem()
{
    QVector<QPoint> v;
    v<<QPoint(30,-15)<<QPoint(0,-30)<<QPoint(-30,-15)<<QPoint(-30,15)
       <<QPoint(0,30)<<QPoint(30,15);
    QGraphicsPolygonItem *item = new QGraphicsPolygonItem(QPolygonF(v));
    item->setBrush(QColor(100,100,100));
    item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(item);
    item->setPos((qrand()%int(scene->sceneRect().width()))-200,
                 (qrand()%int(scene->sceneRect().height()))-200);
}

void MainWindow::slotAddTextItem()
{
  QFont font("Times",16);
  QGraphicsTextItem *item = new QGraphicsTextItem("Hello Qt");
  item->setFont(font);
  item->setFlag(QGraphicsItem::ItemIsMovable);
  item->setDefaultTextColor(QColor(0,0,255));
  scene->addItem(item);
  item->setPos((qrand()%int(scene->sceneRect().width()))-200,
               (qrand()%int(scene->sceneRect().height()))-200);
}

void MainWindow::slotAddRectItem()
{
    QGraphicsRectItem *item = new QGraphicsRectItem(QRectF(0,0,60,60));
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(0,0,0));
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setBrush(QColor(255,255,255));
    scene->addItem(item);
    item->setPos((qrand()%int(scene->sceneRect().width()))-200,
                 (qrand()%int(scene->sceneRect().height()))-200);

}

void MainWindow::slotAddAlphaItem()
{
    QGraphicsPixmapItem *item=scene->addPixmap(QPixmap("image.png"));
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setPos((qrand()%int(scene->sceneRect().width()))-200,
                 (qrand()%int(scene->sceneRect().height()))-200);
}

void MainWindow::slotExit()
{
    close();
}

void MainWindow::slotAddFlashItem()
{
    FlashItem *item = new FlashItem;
    scene->addItem(item);
    item->setPos((qrand()%int(scene->sceneRect().width()))-200,
                 (qrand()%int(scene->sceneRect().height()))-200);
}

void MainWindow::slotAddAnimationItem()
{
    StartItem *item = new StartItem;
    QGraphicsItemAnimation *anim = new QGraphicsItemAnimation;
    anim->setItem(item);
    QTimeLine *timeLine = new QTimeLine(4000);
    timeLine->setCurveShape(QTimeLine::SineCurve);
    timeLine->setLoopCount(0);
    anim->setTimeLine(timeLine);
    int y = (qrand()%400)-200;
    for(int i=0;i<400;i++)
    {
        anim->setPosAt(i/400.0,QPointF(i-200,y));
    }
    timeLine->start();
    scene->addItem(item);
}
