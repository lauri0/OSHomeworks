#include "Canvas.h"

Canvas::Canvas() : QWidget()
{

}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(100, 50, 550, 50);
}
