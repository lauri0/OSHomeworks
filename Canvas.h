#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include <QWidget>
#include <string>
#include <iostream>

using namespace std;

class Canvas : public QWidget
{
public:
    Canvas();

    void changeAverageWaitingTime(string time);
    void changeAlgorithm(string algorithm);

private:
    string averageWaitingTime;
    string planningAlgorithm;

    void paintEvent(QPaintEvent *);
};

#endif // CANVAS_H
