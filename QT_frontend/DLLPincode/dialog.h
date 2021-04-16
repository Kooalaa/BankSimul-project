#ifndef DIALOG_H
#define DIALOG_H

#include <QButtonGroup>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDialog>
#include <QLineEdit>
#include <QTimer>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    Ui::Dialog *ui;
signals:
    void send_pin(QByteArray);

private slots:
    void on_OK_clicked();
    void Handle_Buttons(QAbstractButton *button);
    void on_Close_clicked();
    void on_Backspace_clicked();
    void Timer_slot();

private:
    QString PIN;
    QByteArray hash;
    int time = 10;
    QTimer *p_timer;
    void timer();
};

#endif  // DIALOG_H
