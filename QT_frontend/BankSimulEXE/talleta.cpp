#include "talleta.h"
#include "ui_talleta.h"

Talleta::Talleta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Talleta)
{
    ui->setupUi(this);
}

Talleta::~Talleta()
{
    delete ui;
}
