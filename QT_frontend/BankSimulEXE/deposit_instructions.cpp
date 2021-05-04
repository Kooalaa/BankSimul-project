
#include "deposit_instructions.h"

#include "ui_deposit_instructions.h"

deposit_instructions::deposit_instructions(QWidget *parent)
    : QDialog(parent), ui(new Ui::deposit_instructions) {
    ui->setupUi(this);
    p_rest = new dll_rest_api;
    p_deposit = new deposit;
    p_timer = new QTimer;
    connect(p_deposit->p_timer, SIGNAL(timeout()), p_deposit, SLOT(timer()), Qt::DirectConnection);
    connect(p_timer, SIGNAL(timeout()), this, SLOT(timer()), Qt::DirectConnection);
    connect(p_deposit, SIGNAL(ready(int)), this, SLOT(deposit_done(int)));
    // clang-format off
    connect(p_rest, SIGNAL(info_ready(account_info_t)), this, SLOT(set_account_info(account_info_t)));
    connect(p_rest, SIGNAL(info_ready(customer_info_t)), this, SLOT(set_customer_info(customer_info_t)));
    // clang-format on
}

deposit_instructions::~deposit_instructions() { delete ui; }

// Shows the deposit.ui and starts timer on it
void deposit_instructions::on_start_clicked() {
    p_deposit->show_ui(info.account_num, info.balance, name);
    stop_timer();
    this->hide();
}

// Shows this.ui with new information and ends the deposit operation
void deposit_instructions::deposit_done(int _return) {
    if (_return == 0) {
        status = 0;
        if (p_deposit->sum != 0.0f) {
            p_rest->add_transaction(p_id->account_id, p_deposit->sum);
            new_balance = p_deposit->sum + info.balance;
            ui->Balance->setText(QString().setNum(new_balance, 'f', 2));
            p_rest->set_new_balance(p_id->account_id, new_balance);
        }
        ui->label->setText("Talletus suoritettu");
        ui->start->hide();
        p_timer->start(1000);
        this->show();
    } else {
        on_Close_clicked();
    }
}

// Timer setup
void deposit_instructions::timer() {
    ui->Time->setNum(time);
    time--;
    if ((time == 0) && (status == 0)) {
        stop_timer();
        emit log_out();
    } else if ((time == 0) && (status == 1)) {
        stop_timer();
        emit return_to_main();
        this->close();
    }
}

// Stops timer and resets timer integer
void deposit_instructions::stop_timer() {
    p_timer->stop();
    time = 10;
    ui->Time->setNum(time);
}

// Resets the uis
void deposit_instructions::reset(ids_t *id) {
    status = 1;
    p_id = id;
    p_timer->start(1000);
    p_deposit->reset_sum();
    ui->label->setText(
        "Aloita talletus painamalla 'Aloita' ja syötä aukeavassa ikkunassa summa jonka haluat "
        "tallettaa, tai peruuta painamalla 'Sulje'");
    ui->start->show();
    p_rest->get_account_info(p_id->account_id);
    p_rest->get_customer_info(p_id->customer_id);
    this->show();
}

// Closes deposit window and resets timer
void deposit_instructions::on_Close_clicked() {
    stop_timer();
    emit return_to_main();
    this->close();
}

// Sets new account information on screen
void deposit_instructions::set_account_info(account_info_t info) {
    this->info = info;
    ui->Bank_account_num->setText(info.account_num);
    ui->Balance->setText(QString().setNum(info.balance, 'f', 2));
}

// Sets new customer information on screen
void deposit_instructions::set_customer_info(customer_info_t info) {
    name = info.first_name + " " + info.last_name;
    ui->User_name->setText(name);
}
