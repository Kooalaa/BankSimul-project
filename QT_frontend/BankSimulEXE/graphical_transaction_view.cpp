#include "graphical_transaction_view.h"
#include "ui_graphical_transaction_view.h"

graphical_transaction_view::graphical_transaction_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphical_transaction_view)
{
    ui->setupUi(this);
}

graphical_transaction_view::~graphical_transaction_view()
{
    delete ui;
}
