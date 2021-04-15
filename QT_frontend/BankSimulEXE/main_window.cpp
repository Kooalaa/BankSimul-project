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

void Main_window::on_Selaa_tilitapahtumia_clicked() { pselaa->show(); }

void Main_window::on_Talleta_rahaa_clicked() {}

void Main_window::on_Nosta_rahaa_clicked() { p_withdraw->show(); }

void Main_window::on_Nayta_saldo_clicked() {}

void Main_window::on_Kirjaudu_ulos_clicked() {}
