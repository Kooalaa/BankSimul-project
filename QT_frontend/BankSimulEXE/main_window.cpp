#include "main_window.h"

#include "ui_main_window.h"

Main_window::Main_window(QWidget *parent) : QDialog(parent), ui(new Ui::Main_window) {
    ui->setupUi(this);
    p_deposit_instruct = new deposit_instructions();
    p_withdraw = new withdraw();
    p_browse = new browse_transactions();
    p_balance = new balance();
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

    delete p_ids;
    p_ids = nullptr;
}

void Main_window::set_ids(ids_t ids) {
    p_ids = new ids_t;
    (*p_ids) = ids;
}

void Main_window::on_Browse_transactions_btn_clicked() {}

void Main_window::on_Deposit_btn_clicked() { p_deposit_instruct->reset(p_ids); }

void Main_window::on_Show_balance_btn_clicked() {
    // qDebug() << this->height() << "x" << this->width();
    p_balance->init_and_show(p_ids, this);
    this->hide();
}

void Main_window::on_Withdraw_btn_clicked() {}

void Main_window::on_Log_out_btn_clicked() { emit logout(); }
