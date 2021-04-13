#include "selaa.h"
#include "ui_selaa.h"

Selaa::Selaa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selaa)
{
    ui->setupUi(this);
}

Selaa::~Selaa()
{
    delete ui;
}
