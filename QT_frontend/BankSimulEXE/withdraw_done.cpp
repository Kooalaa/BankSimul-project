#include "withdraw_done.h"

#include "ui_withdraw_done.h"

withdraw_done::withdraw_done(QWidget *parent) : QDialog(parent), ui(new Ui::withdraw_done) {
    ui->setupUi(this);
    ui->time->setNum(time);
    p_timer = new QTimer;
    connect(p_timer, SIGNAL(timeout()), this, SLOT(timer()));
}

withdraw_done::~withdraw_done() { delete ui; }

void withdraw_done::show_ui(QString account_num, double new_balance, QString name) {
    p_timer->start(1000);
    ui->accoun_num->setText(account_num);
    ui->balance->setText(QString().setNum(new_balance, 'f', 2));
    ui->user_name->setText(name);
    this->show();
}

void withdraw_done::on_pushButton_clicked() {
    p_timer->stop();
    time = 10;
    this->close();
}

void withdraw_done::timer() {
    ui->time->setNum(time);
    time--;
    if (time < 0) {
        p_timer->stop();
        time = 10;
        this->close();
    }
}
