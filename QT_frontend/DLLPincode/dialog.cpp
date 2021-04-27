#include "dialog.h"

#include <QDebug>

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
    p_timer = new QTimer();
    // clang-format off
    connect(ui->Key_pad, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(Handle_Buttons(QAbstractButton*)));
    // clang-format on
    connect(p_timer, SIGNAL(timeout()), this, SLOT(Timer_slot()), Qt::DirectConnection);
    ui->lineEdit->setMaxLength(4);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
}

Dialog::~Dialog() {
    delete ui;
    ui = nullptr;
    delete p_timer;
    p_timer = nullptr;
}

void Dialog::show_with_timer() {
    time = 10;
    ui->label->setNum(time);
    ui->lineEdit->setText("");
    p_timer->start(1000);
    this->show();
}

void Dialog::Timer_slot() {
    ui->label->setNum(time);
    time--;
    if (time < 0) {
        this->close();
    }
}

void Dialog::on_OK_clicked() {
    p_timer->stop();
    PIN = ui->lineEdit->text();
    QByteArray temp(PIN.toLocal8Bit());
    hash = QCryptographicHash::hash(temp, QCryptographicHash::Sha3_256);
    emit send_pin(hash);
}

void Dialog::Handle_Buttons(QAbstractButton *button) {
    button->text();
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
    p_timer->start();
    time = 10;
    ui->label->setNum(time);
}

void Dialog::on_Close_clicked() { this->close(); }

void Dialog::on_Backspace_clicked() { ui->lineEdit->backspace(); }
