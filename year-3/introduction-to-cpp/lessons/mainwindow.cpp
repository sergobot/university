#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialog.h"

#include <QMessageBox>
#include <QToolBar>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myModel = new MyModel();
    myModel->setNumber(100);
    myView = new MyView();
    myView->setModel(myModel);

    setCentralWidget(myView);

    QMenu *sayHiMenu = menuBar()->addMenu("H&i");
    sayHiMenu->addAction("Hi", this, &MainWindow::sayHiSlot);

    QMenu *drawMenu = menuBar()->addMenu("&Draw");
    QToolBar *toolBar = addToolBar("Draw");
    QAction *changeAct = drawMenu->addAction("Change", this, &MainWindow::changeSlot);
    toolBar->addAction(changeAct);

    QMenu *colorMenu = menuBar()->addMenu("&Color");
    colorMenu->addAction("Red", this, &MainWindow::setRedColorSlot);
    colorMenu->addAction("Green", this, &MainWindow::setGreenColorSlot);
    colorMenu->addAction("Blue", this, &MainWindow::setBlueColorSlot);

    QMenu *formatMenu = menuBar()->addMenu("&Format");
    formatMenu->addAction("Format line", this, &MainWindow::openFormatDialog);
    formatMenu->addAction("Rect color", this, &MainWindow::openColorDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myView;
    delete myModel;
}

void MainWindow::sayHiSlot()
{
    QMessageBox msgBox;
    msgBox.setText("Hi");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::changeSlot()
{
    myModel->setNumber(300);
    update();
}

void MainWindow::setRedColorSlot()
{
    myView->setLineColor(Qt::red);
}

void MainWindow::setGreenColorSlot()
{
    myView->setLineColor(Qt::green);
}

void MainWindow::setBlueColorSlot()
{
    myView->setLineColor(Qt::blue);
}

void MainWindow::openFormatDialog()
{
    Dialog dialog(this);
    connect(&dialog, &Dialog::colorChangedSignal, myView, &MyView::setLineColor);
    connect(&dialog, &Dialog::widthChangedSignal, myView, &MyView::setLineWidth);
    dialog.exec();
}

void MainWindow::openColorDialog()
{
    QColorDialog dialog(this);
    connect(&dialog, &QColorDialog::colorSelected, myView, &MyView::setRectColor);
    dialog.exec();
}
