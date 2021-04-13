#include "start_window.h"

#include "ui_mainwindow.h"

Start_window::Start_window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Start_window) {
    ui->setupUi(this);
    ppincode = new DLLPincode();
    pmain_window = new Main_window();
}

Start_window::~Start_window() {
    delete ui;
    delete ppincode;
    ppincode = nullptr;
    delete pmain_window;
    pmain_window = nullptr;
}

void Start_window::on_pushButton_clicked() {
    ppincode->Main();
    this->hide();
    qDebug() << QString(ppincode->PIN.toHex());
    pmain_window->show();
}
