#include "start_window.h"

#include "ui_start_window.h"

start_window::start_window(QWidget *parent) : QMainWindow(parent), ui(new Ui::start_window) {
    ui->setupUi(this);
    ppincode = new DLLPincode();
    pmain_window = new Main_window();
    pmain_window->show();
}

start_window::~start_window() {
    delete ui;
    delete ppincode;
    ppincode = nullptr;
    delete pmain_window;
    pmain_window = nullptr;
}

void start_window::card_inserted() {  // Showing the DLLPincode ui when card is inserted
    ppincode->Main();
    pmain_window->show();
}
