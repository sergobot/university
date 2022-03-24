#include "myview.h"

#include <QPainter>

MyView::MyView()
    : lineColor(Qt::red)
    , lineWidth(1)
    , model(nullptr)
{

}

void MyView::setModel(MyModel *m)
{
    model = m;
}

MyModel *MyView::getModel() const
{
    return model;
}

void MyView::setLineColor(QColor c)
{
    lineColor = c;
    update();
}

QColor MyView::getLineColor() const
{
    return lineColor;
}

void MyView::setLineWidth(double w)
{
    lineWidth = w;
}

double MyView::getLineWidth() const
{
    return lineWidth;
}

void MyView::setRectColor(QColor color)
{
    rectColor = color;
}

QColor MyView::getRectColor() const
{
    return rectColor;
}

void MyView::paintEvent(QPaintEvent */*event*/)
{
    if (!model)
        return;

    int i = getModel()->getNumber();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 4, height() / 4);

    painter.drawText(QPoint(i, i), "Hello");
    painter.drawRect(30, 30, 130, 130);
    painter.drawEllipse(30, 30, 130, 130);

    painter.setBrush(QBrush(rectColor));
    painter.setPen(QPen(rectColor));
    painter.drawRect(180, 180, 50, 50);
    painter.setPen(QPen(lineColor, lineWidth));
    painter.drawLine(250, 250, 370, 300);

    painter.setBrush(QBrush());
    painter.setPen(QPen(Qt::darkBlue));
    painter.drawRect(0, 0, width() / 2, height() / 2);

    painter.setFont(QFont("Ubuntu", 20));
    painter.drawText(QPoint(170, 50), "Text in 20px Ubuntu");

    painter.setFont(QFont("Noto Serif", 10));
    painter.drawText(QPoint(170, 75), "Text in 10px Noto Serif");

    painter.setPen(QPen(Qt::darkRed));
    painter.setFont(QFont("Open Sans", 20, QFont::ExtraBold | QFont::StyleItalic));
    painter.drawText(QPoint(170, 120), "Text in 20px Open Sans Extra Bold Italic");
}
