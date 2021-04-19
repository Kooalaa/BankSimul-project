#include "dialog.h"

#include <QDebug>

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    timer();  // Calling timersetup as soon as possible
    ui->setupUi(this);
    // clang-format off
    connect(ui->Key_pad, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(Handle_Buttons(QAbstractButton*)));
    // clang-format on
    this->show();
    ui->lineEdit->setMaxLength(4);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
}

Dialog::~Dialog() {
    delete ui;
    ui = nullptr;
    delete p_timer;
    p_timer = nullptr;
}

void Dialog::timer() {  // Timer setup and start(ms)
    p_timer = new QTimer();
    p_timer->start(1000);
    connect(p_timer, SIGNAL(timeout()), this, SLOT(Timer_slot()), Qt::DirectConnection);
}

void Dialog::Timer_slot() {  // Updating the time to ui.label every second
    ui->label->setNum(time);
    time--;
    if (time < 0) {
        this->close();
    }
}

void Dialog::on_OK_clicked() {  // Saving and emitting signal containing written pincode
    p_timer->stop();
    PIN = ui->lineEdit->text();
    QByteArray temp(PIN.toLocal8Bit());
    hash = QCryptographicHash::hash(temp, QCryptographicHash::Sha3_256);
    emit send_pin(hash);
}

void Dialog::Handle_Buttons(QAbstractButton *button) {  // Handling the numpad operations
    button->text();
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
    p_timer->start();
    time = 10;
    ui->label->setNum(time);
}

void Dialog::on_Close_clicked() { this->close(); }

void Dialog::on_Backspace_clicked() { ui->lineEdit->backspace(); }
