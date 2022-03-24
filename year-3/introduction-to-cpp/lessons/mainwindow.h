#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mymodel.h"
#include "myview.h"

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

    MyModel *myModel;
    MyView *myView;

private slots:
    void sayHiSlot();
    void changeSlot();
    void setRedColorSlot();
    void setGreenColorSlot();
    void setBlueColorSlot();
    void openFormatDialog();
    void openColorDialog();
};
#endif // MAINWINDOW_H
