#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QMouseEvent>
#include <QPainter>
#include <QProxyStyle>
#include <QStyleOptionTab>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
