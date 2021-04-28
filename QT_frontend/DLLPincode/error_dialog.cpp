#include "error_dialog.h"

#include "ui_error_dialog.h"

Error_dialog::Error_dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Error_dialog) {
    ui->setupUi(this);
    p_timer = new QTimer;
    connect(p_timer, SIGNAL(timeout()), this, SLOT(timer()));
}

Error_dialog::~Error_dialog() { delete ui; }

// Shows wrongpin error with attempts left
void Error_dialog::show_error(int attempts) {
    p_timer->start(1000);
    QString error = "Pin väärin, yrityksiä jäljellä " + QString().setNum(attempts);
    ui->label->setText(error);
    this->show();
}

// Shows cardlocked error
void Error_dialog::show_locked_card() {
    p_timer->start(1000);
    ui->label->setText("Pin syötetty väärin 3 kertaa, kortti lukittu");
    this->show();
}

void Error_dialog::timer() {
    ui->label_2->setNum(time);
    time--;
    if (time < 0) {
        stop_timer();
        this->close();
    }
}

void Error_dialog::stop_timer() {
    p_timer->stop();
    time = 2;
    ui->label_2->setNum(time);
}
