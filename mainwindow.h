#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsView>
#include <QWidget>
#include "rect.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QLineEdit>

class MainWindow :  public QGraphicsView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QGraphicsScene * scene;
    ~MainWindow();
    int vsize;
    std::vector<int> v;
    std::vector<Rect*> r;
    void delay(int x);
    void changerect(int y);
    void randomarray(int x);
private:
    QPushButton *qsortbutton;
    QPushButton *bsortbutton;
    QPushButton *csortbutton;
    QPushButton *newbutton;
    QPushButton *resetbutton;
    QLineEdit *number;
    void qsorthelper(int low, int high);
public slots:
    void qsort();
    void bsort();
    void csort();
    void change();
    void resetarray();
    void newarr();
};

#endif // MAINWINDOW_H
