#include "Canvas.h"

Canvas::Canvas() : QWidget()
{

}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(100, 100, 300, 100, Qt::black);
}
