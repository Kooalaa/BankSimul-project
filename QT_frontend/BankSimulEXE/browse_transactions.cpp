#include "browse_transactions.h"

#include "ui_browse_transactions.h"

browse_transactions::browse_transactions(QWidget *parent)
    : QDialog(parent), ui(new Ui::browse_transactions) {
    ui->setupUi(this);
}

browse_transactions::~browse_transactions() { delete ui; }
