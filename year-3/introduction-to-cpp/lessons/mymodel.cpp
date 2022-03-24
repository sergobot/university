#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    : QObject(parent)
{
}

int MyModel::getNumber()
{
    return number;
}

void MyModel::setNumber(int n)
{
    number = n;
}
