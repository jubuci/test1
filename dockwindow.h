#ifndef DOCKWINDOW_H
#define DOCKWINDOW_H

#include <QWidget>
#include <QMainWindow>
#pragma execution_character_set("utf-8")
class DockWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit DockWindow(QWidget *parent = nullptr);

signals:

};

#endif // DOCKWINDOW_H
