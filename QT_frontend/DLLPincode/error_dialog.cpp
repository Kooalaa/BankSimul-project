#include "error_dialog.h"

#include "ui_error_dialog.h"

Error_dialog::Error_dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Error_dialog) {
    ui->setupUi(this);
}

Error_dialog::~Error_dialog() { delete ui; }

void Error_dialog::show_error() {
    this->show();
    ui->label->setText()
}
