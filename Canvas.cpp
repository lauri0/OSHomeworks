#include "Canvas.h"

using namespace std;

Canvas::Canvas(AlgorithmHandler *handler) : QWidget()
{
    drawMultiplier = 24;
    textOffset = 6;
    canAverageWaitingTime = "0";
    this -> handler = handler;
}

AlgorithmHandler* Canvas::getHandler()
{
    return handler;
}

void Canvas::paintEvent(QPaintEvent *)
{
    // Painter is created
    QPainter painter(this);
    QPoint waitingPoint(200, 20);
    QPoint algorithmPoint(500, 20);
    painter.setPen(Qt::black);
    // Average waiting time is displayed
    painter.drawText(waitingPoint, QString::fromStdString("Average waiting time: " +
                                                          to_string(handler -> getAverageWaitingTime()) +
                                                          " ms"));
    // The name of the currently used planning algorithm is displayed
    painter.drawText(algorithmPoint, QString::fromStdString("Algorithm: " + planningAlgorithm));

    int distance = 0;
    int endOfPrev = 20;
    vector< vector<string> > correctProcessVector;
    correctProcessVector = handler -> getCorrectProcessVector();

    for (vector<string> process : correctProcessVector)
    {
        string processId = process[0];
        int duration = atoi(process[1].c_str());

        if (processId == " ")
        {
            painter.fillRect(endOfPrev, 50, duration * drawMultiplier, 50, Qt::blue);
        }
        else
        {
            painter.fillRect(endOfPrev, 50, duration * drawMultiplier, 50, Qt::green);
        }

        painter.drawRect(endOfPrev, 50, duration * drawMultiplier, 50);
        int middle = endOfPrev + duration * drawMultiplier / 2;
        QPoint middlePoint(middle - textOffset, 75);

        QPoint endPoint(endOfPrev - textOffset / 2, 115);
        if (distance >= 10)
        {
            endPoint = QPoint(endOfPrev - textOffset, 115);
        }

        painter.drawText(middlePoint, QString::fromStdString(processId));
        painter.drawText(endPoint, QString::number(distance));
        distance += duration;
        endOfPrev += duration * drawMultiplier;
    }

    QPoint endPoint(endOfPrev - textOffset / 2, 115);
    if (distance >= 10)
    {
        endPoint = QPoint(endOfPrev - textOffset, 115);
    }
    painter.drawText(endPoint, QString::number(distance));

}

void Canvas::changeAverageWaitingTime()
{
    canAverageWaitingTime = to_string(handler -> getAverageWaitingTime());
    this -> repaint();
}

void Canvas::changeAlgorithm(string algorithm)
{
    planningAlgorithm = algorithm;
    this -> update();
}
