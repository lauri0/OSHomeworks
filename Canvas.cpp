#include "Canvas.h"

Canvas::Canvas() : QWidget()
{
    averageWaitingTime = "0";
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPoint waitingPoint(200, 20);
    QPoint algorithmPoint(500, 20);
    painter.setPen(Qt::black);
    painter.drawText(waitingPoint, QString::fromStdString("Average waiting time: " + averageWaitingTime));
    painter.drawRect(100, 50, 550, 50);
    painter.drawText(algorithmPoint, QString::fromStdString("Algorithm: " + planningAlgorithm));
    cout << "Text";
}

void Canvas::changeAverageWaitingTime(string time)
{
    averageWaitingTime = time;
    this -> update();
}

void Canvas::changeAlgorithm(string algorithm)
{
    planningAlgorithm = algorithm;
    this -> update();
}
