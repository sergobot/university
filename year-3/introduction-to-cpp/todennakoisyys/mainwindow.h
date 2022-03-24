#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void createActions();

    QChartView *chartView;
    QWidget *centralWidget;

private slots:
    void promptUserForParameters();

    void generateAndPlotHistogram();
    void calculateAndPlotPLevels();
    void performAndPlotPerformanceTest();

    void showAuthors();
    void openHelpLinkInWebBrowser();
};
#endif // MAINWINDOW_H
