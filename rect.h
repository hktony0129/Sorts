#ifndef RECT_H
#define RECT_H
#include <QGraphicsRectItem>

class Rect: public QGraphicsRectItem{
public:
    int width;
    int height;

    Rect();
};

#endif // RECT_H
