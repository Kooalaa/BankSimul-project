#include "main_window.h"

#include "ui_main_window.h"

Main_window::Main_window(QWidget *parent) : QDialog(parent), ui(new Ui::Main_window) {
    ui->setupUi(this);
    p_rest = new dll_rest_api;
    p_mobile = new dll_mobile_login;
    p_timer = new QTimer;
    p_deposit_instruct = new deposit_instructions();
    p_withdraw = new withdraw();
    p_browse = new browse_transactions();
    p_balance = new balance();
    p_rest = new dll_rest_api();
    p_ids = new ids_t;
    p_withdraw_done = new withdraw_done();

    connect(p_timer, SIGNAL(timeout()), this, SLOT(timer()));
    connect(p_rest, SIGNAL(info_ready(account_info_t)), this,
            SLOT(set_account_info(account_info_t)));
    connect(p_rest, SIGNAL(info_ready(customer_info_t)), this,
            SLOT(set_customer_info(customer_info_t)));
    connect(p_deposit_instruct, SIGNAL(log_out()), this, SLOT(on_Log_out_btn_clicked()),
            Qt::DirectConnection);
    connect(p_deposit_instruct, SIGNAL(return_to_main()), this, SLOT(return_to_main_slot()),
            Qt::DirectConnection);
    connect(p_withdraw, SIGNAL(return_to_main()), this, SLOT(return_to_main_slot()),
            Qt::DirectConnection);
    connect(p_withdraw_done, SIGNAL(return_to_main()), this, SLOT(return_to_main_slot()),
            Qt::DirectConnection);
    connect(p_withdraw_done, SIGNAL(log_out()), this, SLOT(on_Log_out_btn_clicked()),
            Qt::DirectConnection);
}

Main_window::~Main_window() {
    delete ui;
    delete p_deposit_instruct;
    p_deposit_instruct = nullptr;
    delete p_withdraw;
    p_withdraw = nullptr;
    delete p_browse;
    p_browse = nullptr;
    delete p_balance;
    p_balance = nullptr;
    delete p_rest;
    p_rest = nullptr;

    delete p_ids;
    p_ids = nullptr;
}

void Main_window::set_ids(ids_t ids) {
    (*p_ids) = ids;
    p_mobile->set_ids(ids);
}

void Main_window::set_card_num(const int64_t &card_num) { this->card_num = card_num; }

void Main_window::show_ui() {
    p_timer->start(1000);
    p_rest->get_account_info(p_ids->account_id);
    p_rest->get_customer_info(p_ids->customer_id);
    this->show();
}

void Main_window::on_Browse_transactions_btn_clicked() {
    stop_timer();
    p_browse->transaction_menu(p_ids, this);
    this->hide();
}

void Main_window::on_Deposit_btn_clicked() {
    stop_timer();
    p_deposit_instruct->reset(p_ids);
    this->hide();
}

void Main_window::on_Show_balance_btn_clicked() {
    stop_timer();
    p_balance->init_and_show(p_ids, card_num, this);
    this->hide();
}

void Main_window::on_Withdraw_btn_clicked() {
    stop_timer();
    p_withdraw->show_ui(p_ids, p_withdraw_done);
    this->hide();
}

void Main_window::timer() {
    ui->time->setNum(time);
    time--;
    if (time == 0) {
        stop_timer();
        emit logout();
    }
}

void Main_window::set_account_info(account_info_t info) {
    ui->balance->setText(QString().setNum(info.balance, 'f', 2));
    ui->bank_account->setText(info.account_num);
}

void Main_window::set_customer_info(customer_info_t info) {
    name = info.first_name + " " + info.last_name;
    ui->user_name->setText(name);
}

void Main_window::return_to_main_slot() { show_ui(); }

void Main_window::stop_timer() {
    p_timer->stop();
    time = 30;
    ui->time->setNum(time);
}


void Main_window::on_Log_out_btn_clicked() {
stop_timer();
emit logout();
}

void Main_window::on_mobile_login_btn_clicked() {
    p_mobile->get_or_generate_mobile_token(p_ids->card_id);
}
