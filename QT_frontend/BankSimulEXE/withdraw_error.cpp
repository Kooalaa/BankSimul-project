#include "withdraw_error.h"

#include "ui_withdraw_error.h"

withdraw_error::withdraw_error(QWidget *parent) : QDialog(parent), ui(new Ui::withdraw_error) {
    ui->setupUi(this);
}

withdraw_error::~withdraw_error() { delete ui; }

// Is shown if account balance is less than what the user is trying to withdraw
