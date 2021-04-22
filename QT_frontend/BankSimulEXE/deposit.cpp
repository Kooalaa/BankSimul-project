#include "deposit.h"

#include "ui_deposit.h"

deposit::deposit(QWidget *parent) : QDialog(parent), ui(new Ui::deposit) {
    p_timer = new QTimer;
    ui->setupUi(this);
    // clang-format off
    connect(ui->num_pad, SIGNAL(buttonClicked(QAbstractButton*)), this,
            SLOT(handle_buttons(QAbstractButton*)));
    // clang-format on
    sum = 0.0f;
}

deposit::~deposit() { delete ui; }

void deposit::reset_sum() { ui->lineEdit->setText(""); }

void deposit::timer() {
    ui->Time->setNum(time);
    time--;
    if (time < 0) {
        stop_timer();
        this->close();
    }
}

void deposit::handle_buttons(QAbstractButton *button) {
    stop_timer();
    p_timer->start();
    QString temp = ui->lineEdit->text();
    QStringList list = temp.split(".");
    if (list.size() > 1) {
        if (list[1].length() == 2) {
            return;
        }
    }
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
}

void deposit::on_pushButton_12_clicked() {
    ui->lineEdit->backspace();
    stop_timer();
    p_timer->start();
}

void deposit::stop_timer() {
    p_timer->stop();
    time = 10;
    ui->Time->setNum(time);
}

void deposit::on_Ok_clicked() {
    stop_timer();
    sum = ui->lineEdit->text().toDouble();
    emit ready();
    this->close();
}
