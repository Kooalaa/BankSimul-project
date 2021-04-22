#include "error_dialog.h"

#include "ui_error_dialog.h"

Error_dialog::Error_dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Error_dialog) {
    ui->setupUi(this);
}

Error_dialog::~Error_dialog() { delete ui; }

// Shows wrongpin error with attempts left
void Error_dialog::show_error(int attempts) {
    this->show();
    QString error = "Pin väärin, yrityksiä jäljellä " + QString().setNum(attempts);
    ui->label->setText(error);
}

// Shows cardlocked error
void Error_dialog::show_locked_card() {
    ui->label->setText("Pin väärin 3 kertaa, kortti lukittu");
    this->show();
}
