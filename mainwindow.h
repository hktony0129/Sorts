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
    void newarr();
};

#endif // MAINWINDOW_H
