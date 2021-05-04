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
    void show_with_timer();
signals:
    void send_pin(QByteArray);
    void cancel();

private slots:
    void on_OK_clicked();
    void Handle_Buttons(QAbstractButton *button);
    void on_Close_clicked();
    void on_Backspace_clicked();
    void Timer_slot();

private:
    Ui::Dialog *ui;
    QString PIN;
    QByteArray hash;
    int time = 10;
    QTimer *p_timer;
    void timer();
    void stop_timer();
};

#endif  // DIALOG_H
