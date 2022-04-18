#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QMessageBox>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_clearButton_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(1);

    QTableWidgetItem* value = new QTableWidgetItem();
    value->setData(Qt::EditRole, 1.0);
    ui->tableWidget->setItem(0, 0, value);

    QTableWidgetItem* count = new QTableWidgetItem();
    count->setData(Qt::EditRole, 1.0);
    ui->tableWidget->setItem(0, 1, count);
}

void SettingsDialog::on_addButton_clicked()
{
    double val = ui->value->value();
    int cnt = ui->count->value();

    if (cnt < 1)
    {
        QMessageBox msgBox;
        msgBox.setText("Point must have non-zero count!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    for (size_t i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        double v = ui->tableWidget->item(i, 0)->text().toDouble();
        if (v == val)
        {
            QMessageBox msgBox;
            msgBox.setText("Point must be unique!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            return;
        }
    }

    int pos = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(pos + 1);
    ui->tableWidget->setSortingEnabled(false);

    QTableWidgetItem* value = new QTableWidgetItem();
    value->setData(Qt::EditRole, val);
    ui->tableWidget->setItem(pos, 0, value);

    pos = ui->tableWidget->row(value);
    QTableWidgetItem* count = new QTableWidgetItem();
    count->setData(Qt::EditRole, cnt);
    ui->tableWidget->setItem(pos, 1, count);
    ui->tableWidget->sortItems(0);
}

