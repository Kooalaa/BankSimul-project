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
    QByteArray store_PIN();
    QTimer *p_timer;
    void timer();

public slots:
    void Timer_slot();

private slots:
    void on_OK_clicked();
    void Handle_Buttons(QAbstractButton *button);
    void on_Close_clicked();
    void on_Backspace_clicked();

private:
    QString string_PIN;
    QByteArray byte_PIN;
    int time = 10;
};

#endif  // DIALOG_H
