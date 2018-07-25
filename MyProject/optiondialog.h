#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = 0);
    ~OptionDialog();

private slots:
    void on_confirm_clicked();

    void on_cancel_clicked();

    void closeEvent(QCloseEvent*);

    void on_musicvolumeslider_valueChanged(int value);

    void on_isplaymusic_stateChanged(int arg1);

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
