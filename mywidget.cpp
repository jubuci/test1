#include "mywidget.h"
#include "ui_mywidget.h"
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}
void MyWidget::paintEvent(QPaintEvent *event){
     QPainter painter2(this);
    int BASESIZE = 8;
    int SIZE = 4;
    int gate = 1;
    int enemyNum = 23;

    //painter2.begin(ui->centralwidget); //QWidget::paintEngine: Should no longer be called


    //painter2.beginNativePainting();

    painter2.begin(this);

    QPoint x(560,55);


    painter2.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter2.fillRect(100 - 20, 100 - 20,
                                  80, 80, QColor(255,0,0,255));

    //设置字体属性
    QFont font;//字体属性类对象，可以设置字体的属性
    font.setPixelSize(18);//设置字体大小
    font.setUnderline(true);//设置下划线
    font.setOverline(true);//设置上划线
    font.setItalic(true);//设置斜体
    font.setBold(true);//设置加粗
    font.setCapitalization(QFont::SmallCaps);//设置字母大小写
    font.setLetterSpacing(QFont::AbsoluteSpacing,10);//设置字符间距
    painter2.setFont(font);//使用字体属性
    painter2.setPen(Qt::red);//设置画笔颜色
//    painter2.rotate(10);
//       painter2.drawText(6*SIZE/4,BASESIZE,"第"+QString::number(gate)+"关,现存敌人"+QString::number(enemyNum));


       QColor color(0,0,0,255);
       QPen pen;
       pen.setWidth(4);
       pen.setColor(color);
       painter2.setPen(pen);
//       DrawPoint(QPaintEvent *event);
//       draw1.drawPoint(&painter2);

//      painter2.end();


//       one.paint(&painter2,this);
      // this->update(); //此处没有意义

}

void MyWidget::DrawPoint(QPainter * painter,QWidget * widget){
//     painter->setPen(Qt::blue);
//        painter->setBrush(Qt::NoBrush);
//        painter->setOpacity(1.0);
//      QPainter painter(this);
//      painter->save();
//      painter->drawPoint(10,10);
//      painter->drawLine(QPoint(560-400,55),QPoint(620-400,55));
//      painter->restore();
//    DrawPointState *one;
//    one->paint(painter,widget);
}
