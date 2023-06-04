#ifndef DRAW_H
#define DRAW_H
#include<QWidget>
#include <QObject>
#include<QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "shape.h"
//#include "state.h"
class draw
{
public:
//    QPainter painter;
//    int GetShapeType();
    draw();
//    void drawshape();
//    void drawPoint(QPainter *painter);
//    void drawCircle(QPainter* painter);
//    Geometry* Create();
//    Geometry* ReDraw();

//    Geometry* geometry;
//    Point m_curPoint;
//    Circle m_curcircle;
//    Rectangle m_currectangle;
//    Sector m_cursector;

};
//virtual double Area() const { return 0; };
//virtual double Perimeter() const { return 0; };
//virtual bool IsContain(Point&pnt) const { return 0; };

class GraphicsBaseItem:public QGraphicsItem{
public:
//    friend bool Geometry::IsContain(Point &pnt)const;
//    //查看是否包含该点
//    ~GraphicsBaseItem(){};
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) override;
//    virtual bool SetSelected();
protected:
    QPoint m_mousePt;//鼠标当前位置
    bool m_selected;//是否被选择

};
class PointItem:public QObject,public QGraphicsItem,Point{
    Q_OBJECT
public:
    PointItem(QGraphicsItem *parent)
        :QGraphicsItem(parent){}
    PointItem(QPointF point,QGraphicsItem *parent = nullptr){
//        , QGraphicsItem *parent = nullptr
        this->setFlags(QGraphicsItem::ItemIsMovable |
        //                   QGraphicsItem::ItemIsFocusable |
                           QGraphicsItem::ItemIsSelectable);
    };
    PointItem(PointItem&a){
        point.x=a.point.x;
        point.y=a.point.y;
    }
    void SetItem(QPointF a){
        point.x=a.x();
        point.y=a.y();
    };
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget){
      Q_UNUSED(widget);
      Q_UNUSED(option);
        painter->save();

        // 设置画笔和画刷
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(Qt::green);
        if(point.x!=NULL){
        painter->drawPoint(point.x,point.y);
        }
        painter->restore();
    };
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF boundingRect() const override{};
//    void setRect(const QRectF& rect){QRect*m_rect = rect; this->update(); }
    friend bool Point::IsContain(Point &pnt) const;
public:
    Point point;
};
class CricleItem:public GraphicsBaseItem,Circle{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget){
        painter->drawEllipse(circle.cx,circle.cy,circle.radius,circle.radius);
    }
private:
    Circle circle;
};

#endif // DRAW_H
