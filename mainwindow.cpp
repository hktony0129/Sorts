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

    ssortbutton = new QPushButton("Shellsort", this);
    ssortbutton->setGeometry(QRect(QPoint(410, 450),QSize(160, 50)));
    connect(ssortbutton, SIGNAL (released()), this, SLOT (ssort()));

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

void MainWindow::qsort(){
    qsortbutton->setVisible(false);
    bsortbutton->setVisible(false);
    ssortbutton->setVisible(false);
    std::vector<int> check = {};
    for (int i = 0; i < v.size(); i++){
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
        for (int i = 0; i < check.size(); i++){
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
                        delay(1);
                        change();
                    }
                    wall = wall + 1;
                }

            }
            v.erase(v.begin() + start + distance - 1);
            v.insert(v.begin()+wall,base);
            delay(1);
            check[wall] = 1;
        }

        change();
        distance = 0;
        start = 0;
        found = 0;
        wall = 0;
    }
    resetbutton->setVisible(true);
    newbutton->setVisible(true);
    //number->setVisible(true);
}

void MainWindow::bsort(){
    qsortbutton->setVisible(false);
    bsortbutton->setVisible(false);
    ssortbutton->setVisible(false);
    int tempvalue = 0;
    int sorted = 0;
    while(sorted == 0){
        sorted = 1;
        for (int i = 0; i < v.size() - 1; i++){
            if (v[i] > v[i + 1]){
                tempvalue = v[i];
                v[i] = v[i+1];
                v[i+1] = tempvalue;
                delay(1);
                change();
                sorted = 0;
            }
        }
    }
    resetbutton->setVisible(true);
    newbutton->setVisible(true);
    //number->setVisible(true);
}

void MainWindow::ssort(){
    qsortbutton->setVisible(false);
    bsortbutton->setVisible(false);
    ssortbutton->setVisible(false);
    std::vector<int> gapsize = {};
    int size = 1;
    while ((qPow(3,size) - 1) / 2 < v.size() / 2){
        gapsize.insert(gapsize.begin(), (qPow(3,size) - 1) / 2);
        size = size + 1;
    }
    for (int i = 0; i < gapsize.size(); i++){
        if (gapsize[i] != 1){
            std::vector<std::vector<int>> list(gapsize[i], std::vector<int>());
            int count = 0;
            for (int i2 = 0; i2 < v.size(); i2++){
                if (count < list.size() - 1){
                    list[count].push_back(v[i2]);
                    count = count + 1;
                } else {
                    list[count].push_back(v[i2]);
                    count = 0;
                }
            }
            for (int i3 = 0; i3 < list.size(); i3 ++){
                int tempvalue = 0;
                for (int i4 = 1; i4 < list[i3].size() ; i4 ++){
                    int location = i4;
                    while(list[i3][i4] < list[i3][location - 1] and location > 0){
                        location = location - 1;
                    }
                    for (int i7 = i4; i7 > location; i7 --){
                        tempvalue = list[i3][i7];
                        list[i3][i7] = list[i3][i7 - 1];
                        list[i3][i7 - 1] = tempvalue;
                        v[i7 * gapsize[i] + i3] = v[(i7-1) * gapsize[i] + i3] ;
                        v[(i7-1) * gapsize[i] + i3] = tempvalue;
                        change();
                        delay(1);

                    }
                }
            }
        } else {
            int tempvalue = 0;
            for (int i5 = 1; i5 < v.size(); i5 ++){
                int location = i5;
                while(v[i5] < v[location - 1] and location > 0){
                    location = location - 1;
                }
                for (int i6 = i5; i6 > location; i6 --){
                    tempvalue = v[i6];
                    v[i6] = v[i6 - 1];
                    v[i6 - 1] = tempvalue;
                    change();
                    delay(1);
                }

            }
        }
    }
    resetbutton->setVisible(true);
    newbutton->setVisible(true);
    //number->setVisible(true);
}

void MainWindow::change(){

    for (int i = 0; i < v.size(); i++){
        r[i]->setRect(i*600/v.size(), 420 - v[i]*400/vsize, 600/v.size(), v[i]*400/vsize);
    }

}

void MainWindow::resetarray(){
    change();
    qsortbutton->setVisible(true);
    bsortbutton->setVisible(true);
    ssortbutton->setVisible(true);
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
    ssortbutton->setVisible(true);
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
