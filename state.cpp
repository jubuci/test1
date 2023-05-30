//#include "state.h"
//void DrawPointState::paint(QPainter * painter,QWidget * widget){
//    painter->setPen(Qt::blue);
//    painter->setBrush(Qt::NoBrush);
//    painter->setOpacity(1.0);
//     painter->save();
//     painter->drawPoint(10,10);
//     painter->drawLine(QPoint(560-400,55),QPoint(620-400,55));
//     painter->restore();
//};
//editingstate* currentState = NULL;
//class DrawPointCommand:public Command {
//public:
//    void execute() {
//        if (currentState)delete currentState;
//        currentState = new DrawPointState;
//    }
//    const char* Name() const
//    {
//        return "Draw Point";
//    }
//};
//class DrawLineCommand:public Command{
//    void execute() {
//        if (currentState)delete currentState;
//        currentState = new DrawLineState;
//    }
//    const char* Name() const
//    {
//        return "Draw Polyline";
//    }
//};
//class DrawPolCommand:public Command {
//public:
//    void execute() {
//        if (currentState)delete currentState;
//        currentState = new DrawPolState;
//    }
//    const char* Name() const
//    {
//        return "Draw Polygon";
//    }
//};
//class DrawRectCommand :public Command
//{
//public:
//    void execute() {
//        if (currentState)delete currentState;
//        currentState = new DrawRectState;
//    }
//    const char* Name() const
//    {
//        return "Draw Rectangle";
//    }
//};
//class DrawCircleCommand :public Command
//{
//public:
//    void execute() {
//        if (currentState)delete currentState;
//        currentState = new DrawCircleState;
//    }
//    const char* Name() const
//    {
//        return "Draw Circle";
//    }
//};
//class DrawSectorCommand :public Command
//{
//public:
//    void execute() {
//        if (currentState)delete currentState;
//        currentState = new DrawSectorState;
//    }
//    const char* Name() const
//    {
//        return "Draw Sector";
//    }
//};

//编写各个图元命令模式

//State::State()
//{

//}





//class Invoker
//{
//public:
//    QVector<Command*> m_cmds;
//};
//Invoker voker;
//void OnMenuClick(int data) {
//    voker.m_cmds[data - 1]->execute();
//}
