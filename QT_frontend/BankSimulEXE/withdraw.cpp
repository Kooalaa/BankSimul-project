#include "withdraw.h"

#include "ui_withdraw.h"

withdraw::withdraw(QWidget *parent) : QDialog(parent), ui(new Ui::withdraw) {
    ui->setupUi(this);

    // Pointer initialization
    p_error = new withdraw_error;
    timer = new QTimer;
    p_rest = new dll_rest_api;

    // Signals and slots connections
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    // clang-format off
    connect(ui->num_pad, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(handle_buttons(QAbstractButton*)), Qt::DirectConnection);
    // clang-format on
    connect(p_rest, SIGNAL(info_ready(account_info_t)), this,
            SLOT(set_account_info(account_info_t)));
    connect(p_rest, SIGNAL(info_ready(customer_info_t)), this,
            SLOT(set_customer_info(customer_info_t)));
}

withdraw::~withdraw() {
    delete p_error;
    p_error = nullptr;
    delete p_rest;
    p_rest = nullptr;
    delete timer;
    delete ui;
}

// Shows this ui, starts withdraw operation and gets account and customer ids as parameters
void withdraw::show_ui(ids_t *id, withdraw_done *p_withdraw_done) {
    p_id = id;
    this->p_withdraw_done = p_withdraw_done;
    p_rest->get_account_info(id->account_id);    // Calls dll_rest_api function to emit a
                                                 // signal(info_ready(account_info_t))
    p_rest->get_customer_info(id->customer_id);  // Calls dll_rest_api function to emit a
                                                 // signal(info_ready(cutomer_info_t))
    timer->start(1000);
    this->show();
}

// Timer_timeout slot, executed every second when timer signal timeouts
void withdraw::timer_timeout() {
    ui->time->setNum(time_int);
    time_int--;
    if (time_int == 0) {
        stop_timer();
        emit return_to_main();
        this->close();
    }
}

// Resets the timer
void withdraw::stop_timer() {
    timer->stop();
    time_int = 10;
    ui->time->setNum(time_int);
}

// Num_pad buttongroups button handling, gets called everytime a button from num_pad buttongroup is
// pressed
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

// Receives signal(info_ready(account_info_t) from dll_rest_api and shows account information on
// this.ui
void withdraw::set_account_info(account_info_t info) {
    this->info = info;
    ui->bank_num->setText(info.account_num);
    ui->balance->setText(QString().setNum(info.balance, 'f', 2));
}

// Receives signal(info_ready(customer_info_t) from dll_rest_api and shows customer information on
// this.ui
void withdraw::set_customer_info(customer_info_t info) {
    name = info.first_name + " " + info.last_name;
    ui->user_name->setText(name);
}

// Calls functions from dll_rest_api to add new transaction and to set new balance
void withdraw::update_balance(double sum) {
    p_rest->add_transaction(p_id->account_id, -sum);
    p_rest->set_new_balance(p_id->account_id, info.balance - sum);
    show_withdraw_done();
}

// Shows withdraw_done ui with new information
void withdraw::show_withdraw_done() {
    p_withdraw_done->show_ui(ui->bank_num->text(), info.balance - sum, name);
    stop_timer();
    this->close();
}

// Closes withdraw window and resets timer
void withdraw::on_Sulje_clicked() {
    stop_timer();
    emit return_to_main();
    this->close();
}
