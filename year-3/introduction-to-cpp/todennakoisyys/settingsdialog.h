#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    Ui::SettingsDialog *ui;
private slots:
    void on_clearButton_clicked();
    void on_addButton_clicked();
};

#endif // SETTINGSDIALOG_H
