#ifndef MYVIEW_H
#define MYVIEW_H

#include <QWidget>

#include "mymodel.h"

class MyView : public QWidget
{
    Q_OBJECT
public:
    MyView();

    void setModel(MyModel *model);
    MyModel *getModel() const;

    QColor getLineColor() const;
    double getLineWidth() const;
    QColor getRectColor() const;

public slots:
    void setLineColor(QColor color);
    void setLineWidth(double width);
    void setRectColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event) override;

    QColor lineColor;
    double lineWidth;
    QColor rectColor;

    MyModel *model;
};

#endif // MYVIEW_H
