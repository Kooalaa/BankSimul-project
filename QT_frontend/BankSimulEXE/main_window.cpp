#include "main_window.h"

#include "ui_main_window.h"

Main_window::Main_window(QWidget *parent) : QDialog(parent), ui(new Ui::Main_window) {
    ui->setupUi(this);
    ptalleta = new deposit();
    p_withdraw = new withdraw();
    pselaa = new browse_transactions();
    psaldo = new balance();
}

Main_window::~Main_window() {
    delete ui;
    delete ptalleta;
    ptalleta = nullptr;
    delete p_withdraw;
    p_withdraw = nullptr;
    delete pselaa;
    pselaa = nullptr;
    delete psaldo;
    psaldo = nullptr;
}

void Main_window::on_Browse_transactions_btn_clicked() {}

void Main_window::on_Deposit_btn_clicked() {}

void Main_window::on_Show_balance_btn_clicked() {}

void Main_window::on_Withdraw_btn_clicked() {}

void Main_window::on_Log_out_btn_clicked() { this->close(); }
