#include "nosta.h"
#include "ui_nosta.h"

Nosta::Nosta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nosta)
{
    ui->setupUi(this);
}

Nosta::~Nosta()
{
    delete ui;
}
