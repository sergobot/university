#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    virtual void accept() override;

private:
    Ui::Dialog *ui;

private slots:
    void colorChangedSlot(QString colorName);

signals:
    void colorChangedSignal(QColor color);
    void widthChangedSignal(double width);
};

#endif // DIALOG_H
