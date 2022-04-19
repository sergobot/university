#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "groupeddiscretedistribution.h"
#include "tablesamplegenerator.h"
#include "chensamplegenerator.h"

#include "settingsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GroupedDiscreteDistribution m_targetDistribution;

    GroupedDiscreteDistribution m_distribution;
    TableSampleGenerator m_tableSampleGenerator;
    ChenSampleGenerator m_chenSampleGenerator;

    size_t m_sampleSize;
    double m_alpha;
    int m_generatorIndex;
    size_t m_chenWindows;

    void createActions();
    void recreateDistributionAndGenerators(std::vector<GroupedPoint> newPoints);
    SampleGenerator& generator();
    QString generatorDescription() const;

private slots:
    void promptUserForParameters();

    void generateAndPlotHistogram();
    void calculateAndPlotPLevels();
    void performAndPlotPerformanceTest();
    void plotPValues();

    void showAuthors();
    void openHelpLinkInWebBrowser();
};

#endif // MAINWINDOW_H
