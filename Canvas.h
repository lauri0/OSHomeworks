#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include <QWidget>
#include <string>
#include <iostream>

#include <AlgorithmHandler.h>

using std::string;
using std::cout;

class Canvas : public QWidget
{
public:
    Canvas(AlgorithmHandler *handler);

    void changeAverageWaitingTime();
    void changeAlgorithm(string algorithm);

private:
    int drawMultiplier;
    int textOffset;

    string canAverageWaitingTime;
    string planningAlgorithm;

    AlgorithmHandler *handler;

    AlgorithmHandler *getHandler();
    void paintEvent(QPaintEvent *);
};

#endif // CANVAS_H
