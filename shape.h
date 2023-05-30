#ifndef SHAPE_H
#define SHAPE_H

#endif // SHAPE_H
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#include<cmath>
#include<stdio.h>
#include<QMainWindow>
#include<QPainter>
#include<sstream>
#include<fstream>
#include<vector>
#include <algorithm>
#define EPS 1e-6
using namespace std;

class Point;
class Rectangle;
class Sector;
class Circle;

class Geometry {

public:
    QPainter painter;
    QColor framecolor;//边框颜色
    QColor color;//颜色
    QPen pen;//画笔

public:
    virtual double Area() const { return 0; };
    virtual double Perimeter() const { return 0; };
    virtual bool IsContain(Point&pnt) const { return 0; };
 };

//点
class Point :public Geometry
{

public:
    QPainter painter;
    QColor framecolor;//边框颜色
    QColor color;//颜色
    QPen pen;//画笔

public:
    double x, y;
    double Area() const { return 0.0; }
    double Perimeter() const { return 0.0; }
    bool IsContain(Point& pnt) const { return x == pnt.x && y == pnt.y; }

    void Set(double x, double y) { this->x = x; this->y = y; }
    double GetX() const { return x; }
    double GetY() const { return y; }
};

//圆形
class Circle :public Geometry {

public:
    QPainter painter;
    QColor framecolor;//边框颜色
    QColor color;//颜色
    QPen pen;//画笔

public:
    double radius;
    double cx, cy;
    void Set(double cx, double cy, double radius) { this->cx = cx; this->cy = cy; this->radius = radius; };

public:
     double Area() const { return radius * radius * M_PI; };
     double Perimeter() const { return 2 * M_PI * radius; };
     bool IsContain(Point& pnt) const { return (sqrt(cx - pnt.GetX()) * (cx - pnt.GetX()) + (cy - pnt.GetY()) * (cy - pnt.GetY())) <= radius; };
};

//矩形
class Rectangle :public Geometry {

public:
    QPainter painter;
    QColor framecolor;//边框颜色
    QColor color;//颜色
    QPen pen;//画笔

public:
    double cx, cy,bx,by;
    void Set(double cx, double cy, double bx, double by) { this->cx = cx; this->cy = cy; this->bx = bx; this->by = by; };

public:
     double Area() const { return abs(cx - bx) * abs(cy - by); };
     double Perimeter() const { return 2 * abs(cx - bx) + 2* abs(cy - by); };
     bool IsContain(Point& pnt) const { return max(cx,bx) >= pnt.GetX() and max(cy, by) >= pnt.GetY() and min(cx, bx) <= pnt.GetX() and min(cy, by) <= pnt.GetY(); };
};

//扇形
class Sector :public Geometry {

public:

    double angle,radiusmin,radiusmax;
    double cx, cy;
    void Set(double angle, double radiusmin,double radiusmax,double cx, double cy) { this->angle = angle; this->radiusmin = radiusmin;this->radiusmax = radiusmax;this->cx = cx; this->cy = cy; };

public:
    double Area() const { return (M_PI*pow(radiusmax, 2)-M_PI*pow(radiusmin, 2))*angle/360;};
    double Perimeter() const { return (2*M_PI*radiusmax+2*M_PI*radiusmin)*angle/360+2*(radiusmax-radiusmin); };
    bool IsContain(Point& pnt) const { return (sqrt(cx - pnt.GetX()) * (cx - pnt.GetX()) + (cy - pnt.GetY()) * (cy - pnt.GetY())) <= radiusmax and (sqrt(cx - pnt.GetX()) * (cx - pnt.GetX()) + (cy - pnt.GetY()) * (cy - pnt.GetY())) >= radiusmin;}
};
