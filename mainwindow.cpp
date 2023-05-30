#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextEdit>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("图形编辑和分析系统");
    //停靠窗口2
    QDockWidget *dw2 = new QDockWidget("图层",this);//构建停靠窗口，指定父类
    dw2->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);
    //设置停靠窗口特性，可浮动,可关闭
//    dw2->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dw2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //设置停靠窗口特性，具有全部停靠窗口的特性
    QTextEdit *dte2 = new QTextEdit("此处为图层栏");
    dw2->setWidget(dte2);
    addDockWidget(Qt::RightDockWidgetArea,dw2);

    //以上是图层属性代码

    QToolBar* tb=addToolBar("Tool Bar");
    QAction* action=new QAction("",NULL);
    action->setToolTip("Open");
    tb->addAction(action);
    //菜单栏的设置（之后会设置堆栈录入子菜单图标）


//    connect(ui->actionopen, SIGNAL(clicked()), this, SLOT(DrawPoint(QPainter * painter,QWidget * widget)));
//    ui->setupUi(this);
//    connect(mywidget,SIGNAL(send_cwin()),this,SLOT(on_actionopen_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionopen_triggered()
{

//    this->show();
//    QColor color(0,0,0,255);
//    QPen pen; //画笔
//    pen.setWidth(4);
//    pen.setColor(color);
//    painter.setPen(pen);
//    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
//    painter.setPen(pen);
//    mywidget.DrawPoint(&painter);

//    QPainter painter(this);
//    QPen pen; //画笔
//    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
//    painter.setPen(pen);
//    painter.drawPoint(10,10);
//    draw draw1;
//    draw1.drawPoint(&painter);

}
