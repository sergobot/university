#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>

class MyModel : public QObject
{
    Q_OBJECT

public:
    explicit MyModel(QObject *parent = nullptr);

    int getNumber();
    void setNumber(int n);

private:
    int number;
};

#endif // MYMODEL_H
