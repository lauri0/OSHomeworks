#include "Canvas.h"

using namespace std;

Canvas::Canvas() : QWidget()
{
    canAverageWaitingTime = "0";
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPoint waitingPoint(200, 20);
    QPoint algorithmPoint(500, 20);
    painter.setPen(Qt::black);
    painter.drawText(waitingPoint, QString::fromStdString("Average waiting time: " + canAverageWaitingTime));
    painter.drawRect(100, 50, 550, 50);
    painter.drawText(algorithmPoint, QString::fromStdString("Algorithm: " + planningAlgorithm));
}

void Canvas::changeAverageWaitingTime(int time)
{
    canAverageWaitingTime = to_string(time);
    this -> update();
}

void Canvas::changeAlgorithm(string algorithm)
{
    planningAlgorithm = algorithm;
    this -> update();
}
