#include "mainwindow.h"
#include <QGraphicsScene>
#include <QTime>
#include "rect.h"
#include <QApplication>
#include <QPushButton>
#include <QtMath>
#include <vector>
#include <QFont>
#include <QElapsedTimer>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,520);
    setScene(scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWindowTitle("multisort");

    qsortbutton = new QPushButton("Quicksort", this);
    qsortbutton->setGeometry(QRect(QPoint(220, 450),QSize(160, 50)));
    connect(qsortbutton, SIGNAL (released()), this, SLOT (qsort()));

    bsortbutton = new QPushButton("Bubblesort", this);
    bsortbutton->setGeometry(QRect(QPoint(30, 450),QSize(160, 50)));
    connect(bsortbutton, SIGNAL (released()), this, SLOT (bsort()));

    csortbutton = new QPushButton("Combsort", this);
    csortbutton->setGeometry(QRect(QPoint(410, 450),QSize(160, 50)));
    connect(csortbutton, SIGNAL (released()), this, SLOT (csort()));

    resetbutton = new QPushButton("Reset", this);
    resetbutton ->setGeometry(QRect(QPoint(30, 450),QSize(250, 50)));
    resetbutton->setVisible(false);
    connect(resetbutton, SIGNAL (released()), this, SLOT (resetarray()));

    newbutton = new QPushButton("New Array", this);
    newbutton ->setGeometry(QRect(QPoint(320, 450),QSize(250, 50)));
    newbutton->setVisible(false);
    connect(newbutton, SIGNAL (released()), this, SLOT (newarr()));

    //number = new QLineEdit;
    //scene->addWidget(number);
    //number->setGeometry(480,450,90,50);
    //number->setFont(QFont("KaiTi",30));
    //number->setVisible(false);

    randomarray(100);

}



MainWindow::~MainWindow(){

}

void MainWindow::qsorthelper(int low, int high){
    if (low < high){
        int pivot = v[high];
        int wall = low - 1;
        for (int i = low; i <= high - 1; ++i){
            if (v[i] <= pivot){
                wall = wall + 1;
                int tempvalue = v[wall];
                v[wall] = v[i];
                v[i] = tempvalue;
                change();
            }
        }
        wall = wall + 1;
        int tempvalue = v[wall];
        v[wall] = v[high];
        v[high] = tempvalue;
        change();
        qsorthelper(low, wall - 1);
        qsorthelper(wall + 1, high);
    }
}

void MainWindow::qsort(){
    qsortbutton->setVisible(false);
    bsortbutton->setVisible(false);
    csortbutton->setVisible(false);
    qsorthelper(0, vsize - 1);
    resetbutton->setVisible(true);
    newbutton->setVisible(true);
    //number->setVisible(true);

    /* OLD IMPLEMENTATION(SOMEHOW IT WORKED):
    std::vector<int> check = {};
    for (int i = 0; i < vsize; i++){
        check.push_back(0);
    }
    int distance = 0;
    int start = 0;
    int base = 0;
    int tempvalue = 0;
    int found = 0;
    int wall = 0;
    int sorted = 0;
    while(sorted == 0){
        sorted = 1;
        for (int i = 0; i < vsize; i++){
            if (check[i] == 1 && found == 0){

            } else if (check[i] == 1 && found == 1){
                base = v[i - 1];
                break;
            } else if (check[i] == 0 && found == 1){
                distance = distance + 1;
            } else if (check[i] == 0 && found == 0){
                sorted = 0;
                distance = distance + 1;
                start = i;
                found = 1;
            }
            base = v[v.size() - 1];
        }
        wall = start;
        if (distance == 0){
        } else if (distance == 1){
            check[start] = 1;

        }else {
            for(int x = start; x < start + distance; x++){
                if (v[x] < base){
                    tempvalue = v[x];
                    if (wall != x){
                        v.erase(v.begin() + x);
                        v.insert(v.begin()+wall,tempvalue);
                        change();
                    }
                    wall = wall + 1;
                }

            }
            v.erase(v.begin() + start + distance - 1);
            v.insert(v.begin()+wall,base);
            check[wall] = 1;
        }

        change();
        distance = 0;
        start = 0;
        found = 0;
        wall = 0;
    }*/
}

void MainWindow::bsort(){
    qsortbutton->setVisible(false);
    bsortbutton->setVisible(false);
    csortbutton->setVisible(false);
    for (int i = 0 ; i < ( vsize - 1 ); ++i)
     {
       for (int j = 0 ; j < vsize - i - 1; ++j)
       {
         if (v[j] > v[j+1])
         {
           int tempvalue = v[j];
           v[j] = v[j+1];
           v[j+1] = tempvalue;
           change();
         }
       }
     }
    resetbutton->setVisible(true);
    newbutton->setVisible(true);
    //number->setVisible(true);
}

void MainWindow::csort(){
    qsortbutton->setVisible(false);
    bsortbutton->setVisible(false);
    csortbutton->setVisible(false);

    int gap = vsize;
    bool sorted = false;

    while(!sorted){
        gap = gap * 3 / 4;
        if (gap == 0){
            gap = 1;
        }
        if (gap == 1){
            sorted = true;
        }
        for (int i = 0; i + gap < vsize; ++i){
            if (v[i] > v[i+gap]){
                int temp = v[i+gap];
                v[i+gap] = v[i];
                v[i] = temp;
                sorted = false;
                change();
            }
        }
    }

    resetbutton->setVisible(true);
    newbutton->setVisible(true);
    //number->setVisible(true);
}

void MainWindow::change(){
    delay(1);
    for (int i = 0; i < v.size(); i++){
        r[i]->setRect(i*600/v.size(), 420 - v[i]*400/vsize, 600/v.size(), v[i]*400/vsize);
    }

}

void MainWindow::resetarray(){
    change();
    qsortbutton->setVisible(true);
    bsortbutton->setVisible(true);
    csortbutton->setVisible(true);
    resetbutton->setVisible(false);
    newbutton->setVisible(false);
    //number->setVisible(false);
}

void MainWindow::delay(int x){
    QTime dieTime = QTime::currentTime().addMSecs( x );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void MainWindow::randomarray(int num){
    v.clear();
    changerect(num);
    for (int i=1; i<=num; ++i) v.push_back(i);
    std::random_shuffle ( v.begin(), v.end());
    vsize = num;
    change();
    qsortbutton->setVisible(true);
    bsortbutton->setVisible(true);
    csortbutton->setVisible(true);
    resetbutton->setVisible(false);
    newbutton->setVisible(false);
    //number->setVisible(false);
}

void MainWindow::changerect(int y){
    r.clear();
    scene->clear();
    //number = new QLineEdit;
    //scene->addWidget(number);
    //number->setGeometry(480,450,90,50);
    //number->setFont(QFont("KaiTi",30));
    //number->setVisible(false);
    for (int i = 0; i < y; ++i){
        Rect *rect = new Rect();
        scene->addItem(rect);
        r.push_back(rect);
    }

}

void MainWindow::newarr(){
    randomarray(1000);
}
