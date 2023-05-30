//#ifndef STATE_H
//#define STATE_H
//#include"QMouseEvent"
//#include<QPainter>
//#include<QWidget>

//class State
//{
//public:
//    State(){};
//    ~State(){};
//    virtual void mousePressEvent(QMouseEvent *event)=0;
//};
//class editingstate:public State{
//public:
//    virtual void mousePressEvent(QMouseEvent *event);
////    virtual void Shapecreate(QMouseEvent *event);
////    virtual void ShapeChange(QMouseEvent *event);
////    virtual void ShapeTranslation(QMouseEvent *event);
////    virtual void ShapeRotation(QMouseEvent *event);
////    virtual void ShapeZoom(QMouseEvent *event);
////    virtual void ShapeDelete(QMouseEvent *event);
//    virtual void paint(QPainter * painter,QWidget * widget);
//};
//class DrawPointState:public editingstate{
//public:
//    void mousePressEvent(QMouseEvent *event){};
//    void paint(QPainter * painter,QWidget * widget);
//};
//class DrawLineState:public editingstate{
//    void mousePressEvent(QMouseEvent *event);
//};
//class DrawPolState:public editingstate{
//    void mousePressEvent(QMouseEvent *event);
//};
//class DrawRectState:public editingstate{
//    void mousePressEvent(QMouseEvent *event);
//};
//class DrawCircleState:public editingstate{
//    void mousePressEvent(QMouseEvent *event);
//};
//class DrawSectorState:public editingstate{
//    void mousePressEvent(QMouseEvent *event);
//};

////编写各个几何图元的绘制状态
////之后可以添加其它图元
////State* currentState1 = NULL;
////editingstate* currentBrowseState = NULL;
////进行
//class Command
//{
//public:
//    virtual void execute() = 0;
//    virtual const char* Name() const = 0;
//};


//#endif // STATE_H
