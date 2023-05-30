#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    QWidget *myWidget = new QWidget(&w);    // 将myWidget设置为mainWindow的中心窗口部件
//    w.setCentralWidget(myWidget);    // 显示主窗口
    w.show();
    return a.exec();
}
