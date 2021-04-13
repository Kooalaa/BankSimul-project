#include "main_window.h"

#include "ui_main_window.h"

Main_window::Main_window(QWidget *parent) : QDialog(parent), ui(new Ui::Main_window) {
    ui->setupUi(this);
    ptalleta = new Talleta();
    pnosta = new Nosta();
    pselaa = new Selaa();
    psaldo = new Saldo();
}

Main_window::~Main_window() {
    delete ui;
    delete ptalleta;
    ptalleta = nullptr;
    delete pnosta;
    pnosta = nullptr;
    delete pselaa;
    pselaa = nullptr;
    delete psaldo;
    psaldo = nullptr;
}

void Main_window::on_Selaa_tilitapahtumia_clicked() { pselaa->show(); }

void Main_window::on_Talleta_rahaa_clicked() {}

void Main_window::on_Nosta_rahaa_clicked() {}

void Main_window::on_Nayta_saldo_clicked() {}

void Main_window::on_Kirjaudu_ulos_clicked() {}
