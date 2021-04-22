#include "start_window.h"

#include "ui_start_window.h"

start_window::start_window(QWidget *parent) : QMainWindow(parent), ui(new Ui::start_window) {
    ui->setupUi(this);
    p_pincode = new DLLPincode;
    p_main_window = new Main_window;
    p_pincode->Main();
    p_main_window->set_ids(1);
    p_main_window->show();

    p_rest = new dll_rest_api;
    connect(p_rest, &dll_rest_api::logged_in, this, &start_window::logged_in);
    connect(p_pincode, SIGNAL(send_pin(QByteArray)), this, SLOT(pin_received(QByteArray)));
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

void start_window::logged_in(ids_t ids) {
    p_main_window->set_ids(ids);
    p_main_window->show();
}

void start_window::pin_received(QByteArray hash) {
    int card_num = 1561;
    p_rest->login(hash, card_num);
}

void start_window::card_inserted() {  // Showing the DLLPincode ui when card is inserted
    this->close();
    p_pincode->Main();
    p_main_window->show();
}
