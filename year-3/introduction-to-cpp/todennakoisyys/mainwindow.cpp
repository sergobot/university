#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <chrono>
#include <iostream>

#include <QToolBar>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDesktopServices>
#include <QtCharts>

#include "discretedistribution.h"
#include "chensamplegenerator.h"
#include "chisquarecriterion.h"
#include "defaults.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_distribution(DEFAULT_GROUPED_DISCRETE_DISTRIBUTION)
    , m_tableSampleGenerator(DEFAULT_TABLE_SAMPLE_GENERATOR)
    , m_chenSampleGenerator(DEFAULT_CHEN_SAMPLE_GENERATOR)
    , m_sampleSize(1000)
    , m_alpha(0.05)
    , m_generatorIndex(0)
    , m_chenWindows(3)
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    fileMenu->addAction(exitAct);

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));

    QMenu *modelMenu = menuBar()->addMenu(tr("&Model"));
    QToolBar *modelToolBar = addToolBar(tr("Model"));

    QAction *toggleToolBarAct = modelToolBar->toggleViewAction();
    toggleToolBarAct->setText("ToolBar");
    viewMenu->addAction(toggleToolBarAct);

    const QIcon sampleIcon = QIcon(":/images/diagram.png");
    QAction *sampleAct = new QAction(sampleIcon, tr("&Sample"), this);
    sampleAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    sampleAct->setStatusTip(tr("Sample from distribution with given parameters and plot"));
    connect(sampleAct, &QAction::triggered, this, &MainWindow::generateAndPlotHistogram);
    modelMenu->addAction(sampleAct);
    modelToolBar->addAction(sampleAct);

    const QIcon pLevelsIcon = QIcon(":/images/statistics.png");
    QAction *pLevelsAct = new QAction(pLevelsIcon, tr("Compute &p-levels"), this);
    pLevelsAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
    pLevelsAct->setStatusTip(tr("Compute p-levels and plot them"));
    connect(pLevelsAct, &QAction::triggered, this, &MainWindow::calculateAndPlotPLevels);
    modelMenu->addAction(pLevelsAct);
    modelToolBar->addAction(pLevelsAct);

    const QIcon testPerformanceIcon = QIcon(":/images/dashboard.png");
    QAction *testPerformanceAct = new QAction(testPerformanceIcon, tr("&Test Performance"), this);
    testPerformanceAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_T));
    testPerformanceAct->setStatusTip(tr("Measure and compare different sampling methods"));
    connect(testPerformanceAct, &QAction::triggered, this, &MainWindow::performAndPlotPerformanceTest);
    modelMenu->addAction(testPerformanceAct);
    modelToolBar->addAction(testPerformanceAct);

    modelMenu->addSeparator();
    modelToolBar->addSeparator();

    const QIcon settingsIcon = QIcon(":/images/setting-lines.png");
    QAction *settingsAct = new QAction(settingsIcon, tr("S&ettings"), this);
    settingsAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
    settingsAct->setStatusTip(tr("Change modelling preferences"));
    connect(settingsAct, &QAction::triggered, this, &MainWindow::promptUserForParameters);
    modelMenu->addAction(settingsAct);
    modelToolBar->addAction(settingsAct);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    const QIcon authorsIcon = QIcon(":/images/writer.png");
    QAction *authorsAct = new QAction(authorsIcon, tr("&Authors"), this);
    connect(authorsAct, &QAction::triggered, this, &MainWindow::showAuthors);
    helpMenu->addAction(authorsAct);

    const QIcon documentationIcon = QIcon(":/images/book.png");
    QAction *documentationAct = new QAction(documentationIcon, tr("&Documentation"), this);
    documentationAct->setStatusTip(tr("Developers documentation"));
    connect(documentationAct, &QAction::triggered, this, &MainWindow::openHelpLinkInWebBrowser);
    helpMenu->addAction(documentationAct);
}

void MainWindow::promptUserForParameters()
{
    SettingsDialog dialog(this);

    dialog.ui->sampleSize->setValue(m_sampleSize);
    dialog.ui->significance->setValue(m_alpha);
    dialog.ui->simulationComboBox->setCurrentIndex(m_generatorIndex);
    dialog.ui->chenWindows->setValue(m_chenWindows);

    dialog.ui->tableWidget->setRowCount(m_distribution.size());
    for (size_t i = 0; i < m_distribution.size(); ++i)
    {
        GroupedPoint point = m_distribution[i];
        QTableWidgetItem* value = new QTableWidgetItem();
        value->setData(Qt::EditRole, point.value());
        dialog.ui->tableWidget->setItem(i, 0, value);

        QTableWidgetItem* count = new QTableWidgetItem();
        count->setData(Qt::EditRole, (int)point.count());
        dialog.ui->tableWidget->setItem(i, 1, count);
    }
    dialog.ui->tableWidget->sortItems(0);

    int code = dialog.exec();

    if (code == QDialog::Accepted)
    {
        if (dialog.ui->sampleSize->value() != m_sampleSize)
        {
            m_sampleSize = dialog.ui->sampleSize->value();
        }
        if (dialog.ui->significance->value() != m_alpha)
        {
            m_alpha = dialog.ui->significance->value();
        }
        if (dialog.ui->simulationComboBox->currentIndex() != m_generatorIndex)
        {
            m_generatorIndex = dialog.ui->simulationComboBox->currentIndex();
        }
        if (dialog.ui->chenWindows->value() != m_chenWindows)
        {
            m_chenWindows = dialog.ui->chenWindows->value();
            m_chenSampleGenerator = ChenSampleGenerator(m_distribution.ungroup(), m_chenWindows);
        }

        bool updateRequired = false;

        if (dialog.ui->tableWidget->rowCount() == m_distribution.size())
        {
            for (size_t i = 0; i < dialog.ui->tableWidget->rowCount(); ++i)
            {
                double value = dialog.ui->tableWidget->item(i, 0)->text().toDouble();
                double count = dialog.ui->tableWidget->item(i, 1)->text().toInt();

                if (value != m_distribution[i].value() || count != m_distribution[i].count())
                {
                    updateRequired = true;
                    break;
                }
            }
        }
        else
        {
            updateRequired = true;
        }

        if (updateRequired)
        {
            std::vector<GroupedPoint> newPoints;
            for (size_t i = 0; i < dialog.ui->tableWidget->rowCount(); ++i)
            {
                double value = dialog.ui->tableWidget->item(i, 0)->text().toDouble();
                double count = dialog.ui->tableWidget->item(i, 1)->text().toInt();
                newPoints.emplace_back(value, count);
            }
            recreateDistributionAndGenerators(newPoints);
        }
    }
}

void MainWindow::recreateDistributionAndGenerators(std::vector<GroupedPoint> newPoints)
{
    m_distribution = GroupedDiscreteDistribution(newPoints);
    m_tableSampleGenerator = TableSampleGenerator(m_distribution);
    m_chenSampleGenerator = ChenSampleGenerator(m_distribution.ungroup(), m_chenWindows);
}

void MainWindow::generateAndPlotHistogram()
{
    SampleGenerator &gen = generator();
    GroupedSample gSamp = gen.generate(m_sampleSize).group();

    DiscreteDistribution discreteDistribution = m_distribution.ungroup();
    ChiSquareCriterion chisq(discreteDistribution, gSamp);


    QStringList categories;
    for (size_t i = 0; i < discreteDistribution.size(); ++i)
        categories << QString::number(discreteDistribution[i].value());

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Value");
    QValueAxis *axisY = new QValueAxis();
    axisY->setMinorGridLineVisible(true);
    axisY->setTitleText("Frequencies");

    QBarSet *theoretical = new QBarSet("Theoretical");
    QBarSet *empirical = new QBarSet("Empirical");

    for (size_t i = 0; i < discreteDistribution.size(); ++i)
        theoretical->append(discreteDistribution[i].probability());
    for (size_t i = 0; i < gSamp.size(); ++i)
        empirical->append(gSamp[i].count() / (double)gSamp.count());


    QBarSeries *series = new QBarSeries();
    series->append(theoretical);
    series->append(empirical);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Comparing theoretical and empirical distributions, \nusing " + generatorDescription());
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::calculateAndPlotPLevels()
{
    std::vector<size_t> sampleSizes = {10, 100, 1000, 10000, 100000};
    std::vector<double> pValueShares;
    DiscreteDistribution discreteDistribution = m_distribution.ungroup();

    QStringList categories;
    QLineSeries *pValues = new QLineSeries();
    for (const size_t& size : sampleSizes)
    {
        categories << QString::number(size);

        size_t pValuesOverLimit = 0;
        for (size_t i = 0; i < P_VALUE_COUNTS; ++i)
        {
            GroupedSample sample = m_tableSampleGenerator.generate(size).group();
            ChiSquareCriterion chisq(discreteDistribution, sample);

            double pVal = chisq.pValue();
            if (pVal > m_alpha)
                ++pValuesOverLimit;
        }
        double share = pValuesOverLimit / (double)P_VALUE_COUNTS;
        pValueShares.push_back(share);
        pValues->append(QPointF(size, share));
    }

    QLogValueAxis *axisX = new QLogValueAxis();
    axisX->setLabelFormat("%g");
    axisX->setBase(10.0);
    axisX->setTitleText("Sample size");
    QValueAxis *axisY = new QValueAxis();
    axisY->setMinorGridLineVisible(true);
    axisY->setTitleText("True significance level");

    QChart *chart = new QChart();
    chart->addSeries(pValues);
    chart->setTitle("Relationship between sample size and true significance level, using " + generatorDescription() +
                    "\n and formal significance level " + QString::number(m_alpha));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    pValues->attachAxis(axisX);
    pValues->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->graphicsView->setChart(chart);
}

void MainWindow::performAndPlotPerformanceTest()
{
    std::vector<size_t> sampleSizes = {10, 100, 1000, 10000, 100000};

    QStringList categories;
    QBarSet *chenTimes = new QBarSet("Chen");
    QBarSet *tableTimes = new QBarSet("Table");

    using std::chrono::high_resolution_clock, std::chrono::duration;
    for (const size_t& size : sampleSizes)
    {
        categories << QString::number(size);

        auto chenStart = high_resolution_clock::now();
        m_chenSampleGenerator.generate(size);
        auto chenEnd = high_resolution_clock::now();

        auto tableStart = high_resolution_clock::now();
        m_tableSampleGenerator.generate(size);
        auto tableEnd = high_resolution_clock::now();

        duration<double, std::milli> chenTime = chenEnd - chenStart;
        duration<double, std::milli> tableTime = tableEnd - tableStart;

        chenTimes->append(chenTime.count());
        tableTimes->append(tableTime.count());
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Sample size");

    QLogValueAxis *axisY = new QLogValueAxis();
    axisY->setMinorGridLineVisible(true);
    axisY->setLabelFormat("%g");
    axisY->setBase(10.0);
    axisY->setTitleText("Time in ms");

    QBarSeries *series = new QBarSeries();
    series->append(tableTimes);
    series->append(chenTimes);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Chen vs Table method performance comparison by sample size.");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->graphicsView->setChart(chart);
}

void MainWindow::showAuthors()
{
    QMessageBox msgBox;
    msgBox.setText("Copyright (c) Sergey Popov, 2021-2022");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::openHelpLinkInWebBrowser()
{
    QMessageBox msgBox;
    msgBox.setText("Open developers documentation in your default web browser?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Ok)
    {
        QDesktopServices::openUrl(QUrl("https://sergobot.com/todennakoisyys"));
    }
}

SampleGenerator& MainWindow::generator()
{
    if (m_generatorIndex == 0)
    {
        return m_tableSampleGenerator;
    }
    return m_chenSampleGenerator;
}

QString MainWindow::generatorDescription() const
{
    if (m_generatorIndex == 0)
    {
        return "Table method";
    }
    else
        return "Chen method with " + QString::number(m_chenWindows) + " windows";
}

