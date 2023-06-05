#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include<QGraphicsItemGroup>
#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include "mywidget.h"
namespace Ui {
class MainWindow;
}
enum EditStates{
  Select,
  Change,
  Delete,
  CreatePoint,
  CreateBrokenLine,
  CreateRectangle,
  CreateSector,
  CreateCircle,
  CreatePolygon,
  CreateText,
  CreatePictue,

};
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetBackGround();
    void SetQPen();
private slots:
    void on_actionopen_triggered();
    void initGraphicsSystem();
    void drawshape();
    void deleteshape();
    //设置菜单
public slots:
    void mouseReleased_slot(QMouseEvent *e);
    void mousePressed_slot(QMouseEvent *e);
//        void on_mouseMovePoint(QPoint point);
//        void on_mouseClicked(QPoint point);
private:
       QGraphicsScene *m_scene = nullptr;  //场景
       EditStates m_editstate;
       QPointF start_point; // 绘制图形时的起点
       QPointF end_point;
       QGraphicsItemGroup *group;
       QVector<QPointF> points; // 绘制多边形时使用
//    friend void MyWidget::DrawMyPoint(QPointF point);
private:
    Ui::MainWindow *ui;
//    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
