#include "withdraw.h"

#include "ui_withdraw.h"

withdraw::withdraw(QWidget *parent) : QDialog(parent), ui(new Ui::withdraw) {
    ui->setupUi(this);
    p_error = new withdraw_error;
    p_withdraw_done = new withdraw_done;
    timer = new QTimer;
    p_rest = new dll_rest_api;
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    // clang-format off
    connect(ui->num_pad, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(handle_buttons(QAbstractButton*)), Qt::DirectConnection);
    connect(p_rest, SIGNAL(info_ready(account_info_t)), this, SLOT(set_account_info(account_info_t)));
    connect(p_rest, SIGNAL(info_ready(customer_info_t)), this, SLOT(set_customer_info(customer_info_t)));
    // clan-format on
}

withdraw::~withdraw() { delete ui; }

void withdraw::show_ui(ids_t *id) {
    p_id = id;
    p_rest->get_account_info(id->account_id);
    p_rest->get_customer_info(id->customer_id);
    timer->start(1000);
    this->show();
}

void withdraw::timer_timeout() {
    ui->time->setNum(time_int);
    time_int--;
    if (time_int < 0) {
        stop_timer();
        this->close();
    }
}

void withdraw::stop_timer() {
    timer->stop();
    time_int = 10;
    ui->time->setNum(time_int);
}

void withdraw::handle_buttons(QAbstractButton *button) {
    stop_timer();
    timer->start();
    sum = button->text().toDouble();
    if (info.balance < sum) {
        stop_timer();
        p_error->exec();
        timer->start();
    } else {
        update_balance(sum);
    }
}

void withdraw::set_account_info(account_info_t info) {
    this->info = info;
    ui->bank_num->setText(info.account_num);
    ui->balance->setText(QString().setNum(info.balance, 'f',2));
}

void withdraw::set_customer_info(customer_info_t info)
{
    name = info.first_name + " " + info.last_name;
    ui->user_name->setText(name);
}

void withdraw::update_balance(double sum) {
    p_rest->add_transaction(p_id->account_id, -sum);
    p_rest->set_new_balance(p_id->account_id, info.balance - sum);
    show_withdraw_done();
}

void withdraw::show_withdraw_done() {
    p_withdraw_done->show_ui(ui->bank_num->text(), info.balance - sum, name);
    stop_timer();
    this->close();
}

void withdraw::on_Sulje_clicked() {
    stop_timer();
    this->close();
}
