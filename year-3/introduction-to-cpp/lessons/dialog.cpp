#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->comboBox->addItem("Red");
    ui->comboBox->addItem("Green");
    ui->comboBox->addItem("Blue");
    ui->comboBox->setCurrentIndex(0);

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &Dialog::colorChangedSlot);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::accept()
{
    emit colorChangedSignal(ui->comboBox->currentText());
    emit widthChangedSignal(ui->doubleSpinBox->value());

    QDialog::accept();
}

void Dialog::colorChangedSlot(QString colorName)
{
    if (colorName == "Blue")
    {
        ui->doubleSpinBox->setDisabled(true);
        ui->doubleSpinBox->setValue(1.0);
    }
    else
        ui->doubleSpinBox->setDisabled(false);

}
