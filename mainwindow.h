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
    int max;
    int sorted = 0;
    std::vector<int> v = {12,15,2,4,8,1,9,10,6,3,11,5,13,7,14};
    std::vector<int> v2 = {12,15,2,4,8,1,9,10,6,3,11,5,13,7,14};
    std::vector<Rect*> r = {};
    void delay(int x);
    void changerect(int y);
private:
    QPushButton *qsortbutton;
    QPushButton *bsortbutton;
    QPushButton *ssortbutton;
    QPushButton *newbutton;
    QPushButton *resetbutton;
    QLineEdit *number;
public slots:
    void qsort();
    void bsort();
    void ssort();
    void change();
    void resetarray();
    void randomarray();
};

#endif // MAINWINDOW_H
