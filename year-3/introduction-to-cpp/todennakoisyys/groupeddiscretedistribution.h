#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <QObject>
#include <QVector>

#include "groupedpoint.h"

class DiscreteDistribution : public QObject
{
    Q_OBJECT
public:
    explicit DiscreteDistribution(QVector<GroupedPoint> groupedPoints, QObject *parent = nullptr);

    const GroupedPoint& operator[](size_t i) const;
    const QVector<double>& getCumProbs() const;
    const QVector<double>& getTable() const;
    size_t size() const;

    void computeCumProbsIfNotYet();
    void computeTableIfNotYet();

private:
    const QVector<GroupedPoint> points;
    QVector<double> cumprobs;
    QVector<double> table;
};

#endif // DISTRIBUTION_H
