#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QButtonGroup>
#include <QDialog>
#include <QTimer>

namespace Ui {
class deposit;
}

class deposit : public QDialog {
    Q_OBJECT

public:
    explicit deposit(QWidget *parent = nullptr);
    ~deposit();
    void reset_sum();
    QTimer *p_timer;
    double sum;
    void show_ui(QString, double, QString);
signals:
    void ready();
private slots:
    void handle_buttons(QAbstractButton *button);
    void on_pushButton_12_clicked();
    void on_Ok_clicked();
    void timer();

private:
    Ui::deposit *ui;
    void stop_timer();
    int time = 10;
};

#endif  // DEPOSIT_H
