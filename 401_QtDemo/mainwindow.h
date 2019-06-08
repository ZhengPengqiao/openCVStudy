#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QFrame>
#include "mibase.h"

class MainWindow : public QMainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *leftVBoxLayout;
    QListWidget *listWidget;
    QFrame *line;
    QVBoxLayout *rightVBoxLayout;
    QStackedWidget *stackedWidget;
    MIBase *modelItemList;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initBaseUI();
    void addModelItem(MIBase *item);

public slots:
    void listWidget_clicked(QModelIndex index);
};

#endif // MAINWINDOW_H
