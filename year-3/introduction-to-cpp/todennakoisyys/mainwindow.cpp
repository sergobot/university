#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settingsdialog.h"

#include <QToolBar>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chartView(new QChartView)
    , centralWidget(new QWidget)
{
    ui->setupUi(this);
    createActions();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(chartView);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chartView;
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
    sampleAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    sampleAct->setStatusTip(tr("Sample from distribution with given parameters and plot"));
    connect(sampleAct, &QAction::triggered, this, &MainWindow::generateAndPlotHistogram);
    modelMenu->addAction(sampleAct);
    modelToolBar->addAction(sampleAct);

    const QIcon pLevelsIcon = QIcon(":/images/statistics.png");
    QAction *pLevelsAct = new QAction(pLevelsIcon, tr("&Compute p-levels"), this);
    pLevelsAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    pLevelsAct->setStatusTip(tr("Compute p-levels and plot them"));
    connect(pLevelsAct, &QAction::triggered, this, &MainWindow::calculateAndPlotPLevels);
    modelMenu->addAction(pLevelsAct);
    modelToolBar->addAction(pLevelsAct);

    const QIcon testPerformanceIcon = QIcon(":/images/dashboard.png");
    QAction *testPerformanceAct = new QAction(testPerformanceIcon, tr("&Test Performance"), this);
    testPerformanceAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
    testPerformanceAct->setStatusTip(tr("Measure and compare different sampling methods"));
    connect(testPerformanceAct, &QAction::triggered, this, &MainWindow::performAndPlotPerformanceTest);
    modelMenu->addAction(testPerformanceAct);
    modelToolBar->addAction(testPerformanceAct);

    modelMenu->addSeparator();
    modelToolBar->addSeparator();

    const QIcon settingsIcon = QIcon(":/images/setting-lines.png");
    QAction *settingsAct = new QAction(settingsIcon, tr("&Settings"), this);
    settingsAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
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
    dialog.exec();
}

void MainWindow::generateAndPlotHistogram()
{

}

void MainWindow::calculateAndPlotPLevels()
{

}

void MainWindow::performAndPlotPerformanceTest()
{

}

void MainWindow::showAuthors()
{
    QMessageBox msgBox;
    msgBox.setText("Copyright (c) Sergey Popov, 2021");
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
        QDesktopServices::openUrl(QUrl("https://sergobot.me/todennakoisyys"));
    }
}

