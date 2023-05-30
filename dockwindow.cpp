#include "dockwindow.h"

#include<QTextEdit>
#include <QDockWidget>

DockWindow::DockWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle("main");

    //停靠窗口1
    QDockWidget *dw = new QDockWidget("dock window 1",this);

    //设置停靠窗口特性，可移动，可关闭
    dw->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);

    //设置可停靠区域为主窗口左边和右边
    dw->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QTextEdit *dte = new QTextEdit("DockWindow First");
    dw->setWidget(dte);
    addDockWidget(Qt::LeftDockWidgetArea,dw);

    //停靠窗口2
    QDockWidget *dw2 = new QDockWidget("dock window 2",this);//构建停靠窗口，指定父类

    dw2->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);//设置停靠窗口特性，可浮动,可关闭

    QTextEdit *dte2 = new QTextEdit("DockWindow Second");
    dw2->setWidget(dte2);
    addDockWidget(Qt::RightDockWidgetArea,dw2);

    //停靠窗口3
    QDockWidget *dw3 = new QDockWidget("dock window 3",this);//构建停靠窗口，指定父类

    dw3->setFeatures(QDockWidget::AllDockWidgetFeatures);//设置停靠窗口特性，具有全部停靠窗口的特性

    QTextEdit *dte3 = new QTextEdit("DockWindow Third");
    dw3->setWidget(dte3);
    addDockWidget(Qt::RightDockWidgetArea,dw3);

}
