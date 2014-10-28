#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include <QWidget>

using namespace std;

class Canvas : public QWidget
{
public:
    Canvas();

private:
    void paintEvent(QPaintEvent *);
};

#endif // CANVAS_H
