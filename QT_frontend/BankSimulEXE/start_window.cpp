#include "start_window.h"

#include "ui_start_window.h"

start_window::start_window(QWidget *parent) : QMainWindow(parent), ui(new Ui::start_window) {
    ui->setupUi(this);
    p_pincode = new DLLPincode;
    p_main_window = new Main_window;

    p_rest = new dll_rest_api;
    connect(p_rest, &dll_rest_api::logged_in, this, &start_window::logged_in);
}

start_window::~start_window() {
    delete ui;
    delete p_pincode;
    p_pincode = nullptr;
    delete p_main_window;
    p_main_window = nullptr;

    delete p_rest;
    p_rest = nullptr;
}

void start_window::on_pushButton_clicked() {
    p_pincode->Main();
    this->hide();
    p_main_window->set_ids(1);
    p_main_window->show();
}

void start_window::logged_in(ids_t ids) {
    p_main_window->set_ids(ids);
    p_main_window->show();
}

void start_window::pin_recived(QByteArray hash) {
    int card_num = 1561;
    p_rest->login(hash, card_num);
}
