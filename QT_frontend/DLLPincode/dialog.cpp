#include "dialog.h"

#include <QDebug>

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    timer();
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

QByteArray Dialog::store_PIN() { return byte_PIN; }

void Dialog::timer() {
    p_timer = new QTimer();
    p_timer->start(1000);
    connect(p_timer, SIGNAL(timeout()), this, SLOT(Timer_slot()), Qt::DirectConnection);
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
    string_PIN = ui->lineEdit->text();
    QByteArray joku_PIN(string_PIN.toLocal8Bit());
    byte_PIN = QCryptographicHash::hash(joku_PIN, QCryptographicHash::Sha3_256);
    this->close();
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
