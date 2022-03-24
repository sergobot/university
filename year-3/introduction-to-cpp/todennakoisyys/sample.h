#ifndef SAMPLE_H
#define SAMPLE_H

#include <QVector>

class Sample
{
public:
    Sample(QVector<double> values);

    const QVector<double> values;
};

#endif // SAMPLE_H
