#include "mainwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QGroupBox>
#include <math.h>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    angle = 0;
    scaleValue = 5;
    shearValue = 5;
    translateValue = 50;
    QGraphicsScene *scene = new QGraphicsScene;
    //限定新建QGraphicsScene对象的显示区域
    scene->setSceneRect(-200,-200,400,400);
    QPixmap *pixmap = new QPixmap("image.png");
    pixitem = new PixItem(pixmap);
    scene->addItem(pixitem);
    pixitem->setPos(0,0);
    view = new QGraphicsView;                                       //新建一个视图
    view->setScene(scene);                                          //将视图和场景联系起来
    view->setMinimumSize(200,400);                                  //设置视图的最小尺寸为200，400
    ctrlFrame = new QFrame;
    createControlFrame();                                           //新建一个主窗体控制区
    //主窗口布局
    QHBoxLayout *mainLayout = new QHBoxLayout;                      //设置主布局
    mainLayout->setMargin(10);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(view);
    mainLayout->addWidget(ctrlFrame);
    setLayout(mainLayout);
    setWindowTitle(tr("Graphics Item transformation"));             //设置主窗体的标题


}

MainWidget::~MainWidget()
{

}

void MainWidget::createControlFrame()
{
    //旋转控制
    QSlider *rotateSlider = new QSlider;
    rotateSlider->setOrientation(Qt::Horizontal);
    QHBoxLayout *rotateLayout = new QHBoxLayout;
    rotateLayout->addWidget(rotateSlider);
    QGroupBox *rotateGroup = new QGroupBox(tr("Rotate"));
    rotateGroup->setLayout(rotateLayout);

    //缩放控制
    QSlider *scaleSlider = new QSlider;
    scaleSlider->setOrientation(Qt::Horizontal);
    scaleSlider->setRange(1,2*scaleValue);
    scaleSlider->setValue(scaleValue);
    QHBoxLayout *scaleLayout = new QHBoxLayout;
    scaleLayout->addWidget(scaleSlider);
    QGroupBox *scaleGroup = new QGroupBox(tr("Scale"));
    scaleGroup->setLayout(scaleLayout);

    //切变控制
    QSlider *shearSlider = new QSlider;
    shearSlider->setOrientation(Qt::Horizontal);
    shearSlider->setValue(shearValue);
    shearSlider->setRange(0,2*shearValue);
    QHBoxLayout *shearLayout = new QHBoxLayout;
    shearLayout->addWidget(shearSlider);
    QGroupBox *shearGroup = new QGroupBox(tr("shear"));
    shearGroup->setLayout(shearLayout);

    //位移控制
    QSlider *translateSlider = new QSlider;
    translateSlider->setRange(0,2*translateValue);
    translateSlider->setValue(translateValue);
    translateSlider->setOrientation(Qt::Horizontal);
    QHBoxLayout *translateLayout = new QHBoxLayout;
    translateLayout->addWidget(translateSlider);
    QGroupBox *translateGroup = new QGroupBox(tr("tranlate"));
    translateGroup->setLayout(translateLayout);

    connect(rotateSlider,SIGNAL(valueChanged(int)),this,SLOT(slotRotate(int)));
    connect(scaleSlider,SIGNAL(valueChanged(int)),this,SLOT(slotScale(int)));
    connect(shearSlider,SIGNAL(valueChanged(int)),this,SLOT(slotShear(int)));
    connect(translateSlider,SIGNAL(valueChanged(int)),this,SLOT(slotTranslate(int)));

    //控制面板布局
    QVBoxLayout *frameLayout = new QVBoxLayout;
    frameLayout->setMargin(10);
    frameLayout->setSpacing(10);
    frameLayout->addWidget(rotateGroup);
    frameLayout->addWidget(scaleGroup);
    frameLayout->addWidget(shearGroup);
    frameLayout->addWidget(translateGroup);
    ctrlFrame->setLayout(frameLayout);
}

void MainWidget::slotRotate(int value)
{
    view->rotate(value-angle);
    angle = value;
}

void MainWidget::slotScale(int value)
{
    qreal s;
    if(value>scaleValue)
        s=pow(1.1,(value-scaleValue));
    else
        s=pow(1/1.1,(scaleValue-value));
    view->scale(s,s);
    scaleValue = value;
}

void MainWidget::slotShear(int value)
{
    view->shear((value-shearValue)/10.0,0);
    shearValue = value;

}

void MainWidget::slotTranslate(int value)
{
    view->translate((value-translateValue),(value-translateValue));
    translateValue = value;
}
