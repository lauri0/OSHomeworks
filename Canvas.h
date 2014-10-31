#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include <QWidget>
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Canvas : public QWidget
{
public:
    Canvas();

    void changeAverageWaitingTime(int time);
    void changeAlgorithm(string algorithm);

private:
    string canAverageWaitingTime;
    string planningAlgorithm;

    void paintEvent(QPaintEvent *);
};

#endif // CANVAS_H
