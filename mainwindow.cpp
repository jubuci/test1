#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextEdit>
#include <QDockWidget>
#include <QMouseEvent>
#include <QColorDialog>
template<class T>
void setBrushColor(T *item)
{//函数模板
    QColor color = item->brush().color();
    color = QColorDialog::getColor(color,NULL,"选择填充颜色");
    if (color.isValid())
        item->setBrush(QBrush(color));
}
//设置填充颜色
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("图形编辑和分析系统");
    //设置主窗口标题
    QDockWidget *dw2 = new QDockWidget("图层",this);//构建停靠窗口，指定父类
    dw2->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);
    //设置停靠窗口特性，可浮动,可关闭
//    dw2->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dw2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //设置停靠窗口特性，可以左侧和右侧浮动
    QTextEdit *dte2 = new QTextEdit("此处为图层栏");
    //设置图层栏文本
    dw2->setWidget(dte2);
    addDockWidget(Qt::RightDockWidgetArea,dw2);
    //初始情况下，图层栏在右侧
    //以上是右侧悬浮窗口（用以显示图层图层）代码

    QToolBar* tb=addToolBar("Tool Bar");
    QAction* open=new QAction("",NULL);
    open->setToolTip("Open");
    tb->addAction(open);
    QAction *select=new QAction("",NULL);
    select->setToolTip("select");
    tb->addAction(select);
    //!没搞完
    //菜单栏的设置（之后会设置堆栈录入子菜单图标）
    connect(select,&QAction::triggered,[=](){
        m_editstate =Select;
    });
    connect(select, &QAction::triggered,
            ui->graphicsView,
            [=]()
            {
                ui->graphicsView->SetState(Edit);
            }
            );
    //选择状态

    //设置graphicsView属性，详细可以搜索“GraphicsView”关键词
    //graphicsview是中间的白框，QGraphicsItem是抽象的图形类，圆、矩形等等形状都是它的子类

    ui->graphicsView->setCursor(Qt::CrossCursor);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

//    connect(ui->graphicsView, &MyGraphicsView::mouseMove, this, &MainWindow::mouseMove_slot);
    connect(ui->graphicsView, &MyGraphicsView::mousePressed, this, &MainWindow::mousePressed_slot);
    connect(ui->graphicsView, &MyGraphicsView::mouseReleased, this, &MainWindow::mouseReleased_slot);
//    connect(ui->graphicsView, &MyGraphicsView::mouseDoubleClick, this, &MainWindow::mouseDoubleClick_slot);
    initGraphicsSystem();
    //功能相当于展示一个图层
    //之后把这个封装一下，将QPen、color等导入进去，由此设置图形的颜色，粗细
    //调用函数进行系统初始化
    //基本的一点函数
    //bool isActive() const：true为被选中
    //设置图元指针为pShape
    //QPointF pos = pShape->pos();得到图元坐标
    QMenu *pMenu = new QMenu(ui->graphicsView);
    QAction *mes = new QAction(tr("编辑所选项大小"), this);
    QAction *color=new QAction(tr("编辑所选项颜色"),this);
    QAction *delete1= new QAction(tr("删除所选项"), this);
    QAction *quit = new QAction(tr("取消"), this);

    /* 添加菜单项 */
    pMenu->addAction(mes);
    pMenu->addAction(color);
    pMenu->addAction(delete1);
    pMenu->addAction(quit);

    /* 连接槽函数 */
    connect(mes, SIGNAL(triggered()), this, SLOT(message()));
    connect(color,SIGNAL(triggered()),this,SLOT(message()));
    connect(delete1,SIGNAL(triggered()), this, SLOT(deleteshape()));
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));  //直接触发窗口的close函数
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->graphicsView,&QLabel::customContextMenuRequested,[=](const QPoint &pos)
        {
            pMenu->exec(QCursor::pos());
        });
    //菜单设置
//    connect(ui->actionopen, SIGNAL(clicked()), this, SLOT(DrawMyPoint(QPointF point)));
//    ui->setupUi(this);
//    connect(mywidget,SIGNAL(send_cwin()),this,SLOT(on_actionopen_triggered()));
//    connect(ui->actiondraw, SIGNAL(clicked()), this, SLOT(DrawMyPoint(QPointF point)));
    connect(ui->actionselect, &QAction::triggered,
                [=]()
                {
                    m_editstate =Select;
                }
                );
        connect(ui->actionselect, &QAction::triggered,
                ui->graphicsView,
                [=]()
                {
                    ui->graphicsView->SetState(Edit);
                }
                );
    //选择

    connect(ui->actionpoint, &QAction::triggered,[=]()
               {m_editstate = CreatePoint;
                start_point = end_point = QPointF();
               });
       connect(ui->actionpoint, &QAction::triggered,
               ui->graphicsView,[=](){
                   ui->graphicsView->SetState(Draw);
               });
       //点
       connect(ui->actionrectangle, &QAction::triggered,[=]()
               {m_editstate = CreateRectangle;
                   start_point = end_point = QPointF();});

        connect(ui->actionrectangle, &QAction::triggered,ui->graphicsView,[=](){
                       ui->graphicsView->SetState(Draw);});
        //矩形
        connect(ui->actionpolygon, &QAction::triggered,
                    [=]()
                    {
                        m_editstate = CreatePolygon;
                        start_point = end_point = QPointF();
                        points.clear();
                    }
                    );
            connect(ui->actionpolygon, &QAction::triggered,
                    ui->graphicsView,
                    [=]()
                    {
                         ui->graphicsView->SetState(Draw);
                    }
                    );
        //多边形
        connect(ui->actioncircle, &QAction::triggered,
                    [=]()
                    {m_editstate = CreateCircle;
                    start_point = end_point = QPointF();
                    }
                    );
            connect(ui->actioncircle, &QAction::triggered,
                    ui->graphicsView,
                    [=]()
                    {
                        ui->graphicsView->SetState(Draw);
                    }
                    );
        //圆
            connect(ui->actionbrokenline, &QAction::triggered,
                      [=]()
                      {
                          m_editstate = CreateBrokenLine;
                          start_point = end_point = QPointF();
                          points.clear();
                      }
                      );
              connect(ui->actionbrokenline, &QAction::triggered,
                      ui->graphicsView,
                      [=]()
                      {
                          ui->graphicsView->SetState(Draw);
                      }
                      );
        //折线


        //扇形

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGraphicsSystem()
{
    QRectF rect(-200,-100,400,200);
    //m_scene逻辑坐标系定义
    m_scene = new QGraphicsScene(rect);
    ui->graphicsView->setScene(m_scene);
    //画一个矩形框，大小等于scene
    QGraphicsRectItem *item = new QGraphicsRectItem(rect);
    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);//可选择
    //设置画笔宽
    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    item->setData(1,13);

    m_scene->addItem(item);

    //画一个位于scene中心的椭圆
    QGraphicsEllipseItem *item2 = new QGraphicsEllipseItem(-100,-50,200,100);
    item2->setPos(0,0);
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable
                    | QGraphicsItem::ItemIsMovable);    //设置可拖动
    m_scene->addItem(item2);

    //画一个位于scene边缘的椭圆
    QGraphicsEllipseItem *item3 = new QGraphicsEllipseItem(-50,-50,100,100);
    item3->setPos(rect.right(),rect.bottom());
    //设置所处中点
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable
                    | QGraphicsItem::ItemIsMovable);    //设置可拖动
    m_scene->addItem(item3);

    m_scene->clearSelection();
    //将所有图形属性设置为未选中
}
//展示一个图层
void MainWindow::mousePressed_slot(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        // 绘图时
        if (m_editstate == CreateSector
                ||m_editstate == CreateRectangle
                || m_editstate == CreateCircle
                || m_editstate == CreatePolygon
                || m_editstate == CreateText
                || m_editstate == CreateBrokenLine
                ||m_editstate == CreatePoint)
        {
//            isSaved = false;
            start_point = ui->graphicsView->mapToScene(e->pos());
            if (m_editstate == CreatePolygon) {
                points.append(start_point);
            }
            if (m_editstate == CreateBrokenLine) {
                if (points.isEmpty()) { // 点下第一个点时
                    group = new QGraphicsItemGroup; // 创建一个组合
                    m_scene->addItem(group);
                }
                points.append(start_point);
            }
        }
        // 编辑时
        else if (m_editstate == Select
//                 || m_editstate == Fill
                 || m_editstate == Change
                 || m_editstate == Delete)
        {
//            isSaved = false;
            // 先选中
            QPointF pointScene = ui->graphicsView->mapToScene(e->pos()); //转换到Scene坐标
            QGraphicsItem *item = NULL;
            item = m_scene->itemAt(pointScene, ui->graphicsView->transform()); //获取光标下的绘图项
            if (item) {
                if (item->group()) {
                    item = item->group();
                }
                // 状态栏显示长度/面积
                item->setCursor(Qt::SizeAllCursor); // 改变鼠标样式
            }
//            if (cur_status == Fill) { // 填充
//                switch (item->type())  //绘图项的类型
//                {
//                      case QGraphicsRectItem::Type: //矩形框
//                      {
//                        QGraphicsRectItem *theItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
//                        setBrushColor(theItem);
//                        break;
//                      }
//                      case QGraphicsEllipseItem::Type: // 椭圆
//                      {
//                        QGraphicsEllipseItem *theItem;
//                        theItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
//                        setBrushColor(theItem);
//                        break;
//                      }
//                      case QGraphicsPolygonItem::Type: //多边形
//                      {
//                        QGraphicsPolygonItem *theItem = qgraphicsitem_cast<QGraphicsPolygonItem*>(item);
//                        setBrushColor(theItem);
//                        break;
//                      }
//                      case QGraphicsLineItem::Type: //直线，设置线条颜色
//                      {
//                        QGraphicsLineItem *theItem = qgraphicsitem_cast<QGraphicsLineItem*>(item);
//                        QPen pen = theItem->pen();
//                        QColor color = theItem->pen().color();
//                        color = QColorDialog::getColor(color,this,"选择线条颜色");
//                        if (color.isValid())
//                        {
//                            pen.setColor(color);
//                            theItem->setPen(pen);
//                        }
//                        break;
//                      }
//                     case QGraphicsItemGroup::Type:
//                     {
//                        QGraphicsItemGroup *thegroup = qgraphicsitem_cast<QGraphicsItemGroup*>(item);
//                        QColor color = QColorDialog::getColor(color,this,"选择线条颜色");
//                        QList<QGraphicsItem *>	items_list = scene->items();
//                        for (int i = 0; i < items_list.size(); i++) {
//                            if (items_list[i]->type() == QGraphicsLineItem::Type
//                                    && items_list[i]->data(group_id_key).toInt() == thegroup->data(group_id_key).toInt())
//                            {
//                                QGraphicsLineItem *theItem = qgraphicsitem_cast<QGraphicsLineItem*>(items_list[i]);
//                                QPen pen = theItem->pen();
//                                if (color.isValid())
//                                {
//                                    pen.setColor(color);
//                                    theItem->setPen(pen);
//                                }
//                            }
//                        }
//                        break;
//                     }
//                }
//                scene->clearSelection();
//            }
//            else if (cur_status == Translate) {  // 平移
//                // 平移模态对话框
//                tDialog = new TranslateDialog(this);
//                // 接受信号，包含输入的平移量
//                connect(tDialog, &TranslateDialog::translate_value,
//                        [=](float x, float y)
//                        {

//                            item->setPos(QPointF(item->x() + x, item->y() + y));

//                            //item->rect().setX(item->x() + x);





//                        }
//                        );
//                tDialog->exec();
//            }
            else if (m_editstate== Delete) {  // 删除
                // 删除所选中的绘图项
                int cnt = m_scene->selectedItems().count();
                if (cnt > 0)
                for (int i = 0; i < cnt; i++) {
                    QGraphicsItem *item = m_scene->selectedItems().at(0);
                    m_scene->removeItem(item);
                }
            }
            m_scene->clearSelection();
        } else {  // 其他选项

        }
    }
    else if (e->button() == Qt::RightButton) { // 鼠标右击 画多边形
        if (m_editstate==CreatePolygon) {
            start_point = ui->graphicsView->mapToScene(e->pos());
            points.append(start_point);
//            for (auto e : points) qDebug() << e.x() << e.y() << endl;

            // 画多边形
            QGraphicsPolygonItem *item = new QGraphicsPolygonItem(QPolygonF(points));
            item->setFlags(QGraphicsItem::ItemIsMovable
                           | QGraphicsItem::ItemIsSelectable
                           | QGraphicsItem::ItemIsFocusable);
//            double area = ComputePolygonArea(points);
//            item->setData(areaORlen_key, area);
//            item->setData(shape_key, "多边形");
            m_scene->addItem(item);
            // 清空points容器，便于下一个多边形绘制
            points.clear();
        }
        else if (m_editstate == CreateBrokenLine) {
            start_point = ui->graphicsView->mapToScene(e->pos());
            points.append(start_point);
            // 画折线
            for (int i = 0; i < points.size() - 1; i++) {
                QGraphicsLineItem *line_item = new QGraphicsLineItem(QLineF(points[i], points[i + 1]));//x,y 为左上角的图元局部坐标，图元中心点为0,0
                line_item->setFlags(QGraphicsItem::ItemIsMovable
                               | QGraphicsItem::ItemIsSelectable
                               | QGraphicsItem::ItemIsFocusable);

                QPen pen;
                pen.setWidth(2);
                line_item->setPen(pen);
                line_item->setSelected(false);
                line_item->clearFocus();
//                // 计算长度
//                double len = sqrt(pow((points[i].x() - points[i + 1].x()), 2) + pow((points[i].y() - points[i + 1].y()), 2));
//                line_item->setData(areaORlen_key, len);
//                group->setData(areaORlen_key, QVariant(group->data(areaORlen_key).toDouble() + len));
                // 加入到组合中
                group->addToGroup(qgraphicsitem_cast<QGraphicsItem*>(line_item));
            }
            points.clear();
            // 设置可选可移动
            group->setFlags(QGraphicsItem::ItemIsMovable
                           | QGraphicsItem::ItemIsSelectable
                           | QGraphicsItem::ItemIsFocusable);
            group->setSelected(false);
//            group_id++;
        }
    }
}

void MainWindow::mouseReleased_slot(QMouseEvent *e) {  // 鼠标释放时绘制图形
    if (e->button() == Qt::LeftButton) {
        // 获取鼠标释放时的坐标
        end_point = ui->graphicsView->mapToScene(e->pos());
        switch(m_editstate) {
//        case CreateLine:  // 绘制直线
//        {
//            QGraphicsLineItem *line_item = new QGraphicsLineItem(QLineF(start_point, end_point));//x,y 为左上角的图元局部坐标，图元中心点为0,0
//            line_item->setFlags(QGraphicsItem::ItemIsMovable
//                           | QGraphicsItem::ItemIsSelectable
//                           | QGraphicsItem::ItemIsFocusable);

//            QPen pen;
//            pen.setWidth(2);
//            line_item->setPen(pen);
//            // 计算长度
//            double len = sqrt(pow((start_point.x() - end_point.x()), 2) + pow((start_point.y() - end_point.y()), 2));
//            line_item->setData(areaORlen_key, QVariant(len));
//            line_item->setData(shape_key, "直线");
//            scene->addItem(line_item);
//            break;
//        }
        case CreateRectangle:  // 绘制矩形
        {
            // 保持start_point在左上方
            if (start_point.x() > end_point.x()) {
                QPointF tmp = start_point;
                start_point = end_point;
                end_point = tmp;
            }
            QGraphicsRectItem *rect_item = new QGraphicsRectItem(QRectF(start_point, end_point));//x,y 为左上角的图元局部坐标，图元中心点为0,0
            rect_item->setFlags(QGraphicsItem::ItemIsMovable
                           | QGraphicsItem::ItemIsSelectable
                           | QGraphicsItem::ItemIsFocusable);
            double area = (end_point.x() - start_point.x()) * (end_point.y() - start_point.y());
//            rect_item->setData(areaORlen_key, QVariant(area));
//            rect_item->setData(shape_key, "矩形");
            m_scene->addItem(rect_item);
            break;
        }
        case CreateCircle:  // 绘制椭圆
        {
            // 保持start_point在左上方
            if (start_point.x() > end_point.x()) {
                QPointF tmp = start_point;
                start_point = end_point;
                end_point = tmp;
            }
            QGraphicsEllipseItem *item=new QGraphicsEllipseItem(QRectF(start_point, end_point));
            item->setFlags(QGraphicsItem::ItemIsMovable
                           | QGraphicsItem::ItemIsSelectable
                           | QGraphicsItem::ItemIsFocusable);
//            double area = PI * (end_point.x() - start_point.x()) * 0.5 * (end_point.y() - start_point.y()) * 0.5;
//            item->setData(areaORlen_key, area);
//            item->setData(shape_key, "椭圆");
            m_scene->addItem(item);
            break;
        }
//        case DrawCurve:{
//            // 设置可选可移动
//            group->setFlags(QGraphicsItem::ItemIsMovable
//                           | QGraphicsItem::ItemIsSelectable
//                           | QGraphicsItem::ItemIsFocusable);
//            group_id++;
//            break;
//        }
        default:
            break;
        }
    }
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
//open菜单按钮响应函数
void MainWindow::SetBackGround(){
//    QPointF pointScene = ui->graphicsView->mapToScene(e->pos()); //转换到Scene坐标
//    QGraphicsItem *item = NULL;
//    item = m_scene->itemAt(pointScene, ui->graphicsView->transform()); //获取光标下的绘图项
    QGraphicsItem *item = m_scene->selectedItems().at(0);
    switch (item->type())  //绘图项的类型
                    {
                          case QGraphicsRectItem::Type: //矩形框
                          {
                            QGraphicsRectItem *theItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
                            setBrushColor(theItem);
                            break;
                          }
                          case QGraphicsEllipseItem::Type: // 椭圆
                          {
                            QGraphicsEllipseItem *theItem;
                            theItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
                            setBrushColor(theItem);
                            break;
                          }
                          case QGraphicsPolygonItem::Type: //多边形
                          {
                            QGraphicsPolygonItem *theItem = qgraphicsitem_cast<QGraphicsPolygonItem*>(item);
                            setBrushColor(theItem);
                            break;
                          }
                          case QGraphicsLineItem::Type: //直线，设置线条颜色
                          {
                            QGraphicsLineItem *theItem = qgraphicsitem_cast<QGraphicsLineItem*>(item);
                            QPen pen = theItem->pen();
                            QColor color = theItem->pen().color();
                            color = QColorDialog::getColor(color,this,"选择线条颜色");
                            if (color.isValid())
                            {
                                pen.setColor(color);
                                theItem->setPen(pen);
                            }
                            break;
                          }
                         case QGraphicsItemGroup::Type:
                         {
                            QGraphicsItemGroup *thegroup = qgraphicsitem_cast<QGraphicsItemGroup*>(item);
                            QColor color = QColorDialog::getColor(color,this,"选择线条颜色");
                            QList<QGraphicsItem *>	items_list = m_scene->items();
                            for (int i = 0; i < items_list.size(); i++) {
                                if (items_list[i]->type() == QGraphicsLineItem::Type
                                        /*&& items_list[i]->data(group_id_key).toInt() == thegroup->data(group_id_key).toInt()*/)
                                {
                                    QGraphicsLineItem *theItem = qgraphicsitem_cast<QGraphicsLineItem*>(items_list[i]);
                                    QPen pen = theItem->pen();
                                    if (color.isValid())
                                    {
                                        pen.setColor(color);
                                        theItem->setPen(pen);
                                    }
                                }
                            }
                            break;
                         }
};
};
void MainWindow::deleteshape(){
        // 删除所选中的绘图项
        int cnt = m_scene->selectedItems().count();
        if (cnt > 0)
        for (int i = 0; i < cnt; i++) {
            QGraphicsItem *item = m_scene->selectedItems().at(0);
            m_scene->removeItem(item);
        }
    m_scene->clearSelection();
};
void MainWindow::SetQPen(){};
void MainWindow::drawshape(){
    m_scene->clear();
    //清空图层
    //!未完成：将之前修改的图层进行存储。

};
//设置状态类：创造状态->创建点、线、圆……多边形状态。
//单击绘制点，拖动绘制矩形与圆，单击绘制直线，右键停止，单击绘制多边形，右键停止，除点外，图形绘制完成后，创造模式结束
//绘制图形
//设置状态类：修改状态，在这种状态模式下，选择新图形时会将上一个选择图形取消。
//单击选择图形，右键打开图形（“编辑”、“重绘”、“删除”）
//只有圆、矩形具有编辑选项，点击编辑，弹出对话框，可以修改半径等信息。
//点击重绘，删除之前的图形，重新进行绘制
//点击删除，删除图形

//设置状态类
//创建一个新的图层，
//将item堆栈存储，删除选中Item操作：
//    QList<QGraphicsItem *> itemList = Scene->selectedItems();
//    for (auto i = 0; i < itemList.size(); i++) {
//        Scene->removeItem(itemList[i]);
//        delete itemList[i];
//    }
