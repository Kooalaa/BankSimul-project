#include "deposit_instructions.h"

#include "ui_deposit_instructions.h"

deposit_instructions::deposit_instructions(QWidget *parent)
    : QDialog(parent), ui(new Ui::deposit_instructions) {
    ui->setupUi(this);
    p_rest = new dll_rest_api;
    p_deposit = new deposit;
    p_timer = new QTimer;
    connect(p_deposit->p_timer, SIGNAL(timeout()), p_deposit, SLOT(timer()), Qt::DirectConnection);
    connect(p_timer, SIGNAL(timeout()), this, SLOT(timer()), Qt::DirectConnection);
    connect(p_deposit, SIGNAL(ready()), this, SLOT(deposit_done()));
    connect(p_rest, SIGNAL(info_ready(account_info_t)), this, SLOT(update_balance(account_info_t)));
}

deposit_instructions::~deposit_instructions() { delete ui; }

void deposit_instructions::on_start_clicked() {  // Shows the deposit.ui and starts timer on it
    p_deposit->show();
    p_deposit->p_timer->start(1000);
    stop_timer();
    this->hide();
}

void deposit_instructions::deposit_done() {  // Shows this.ui with new information and ends the
                                             // deposit operation
    if (p_deposit->sum != 0.0f) {
        p_rest->add_transaction(p_id->account_id, p_deposit->sum);
        new_balance = p_deposit->sum + info.balance;
        ui->Balance->setText(QString().setNum(new_balance));
        p_rest->set_new_balance(p_id->account_id, new_balance);
    }

    qDebug() << "HERE";
    p_timer->start(1000);
    ui->label->setText("Talletus suoritettu");
    ui->start->hide();
    this->show();
}

void deposit_instructions::timer() {  // Timer setup
    ui->Time->setNum(time);
    time--;
    if (time < 0) {
        stop_timer();
        this->close();
    }
}

void deposit_instructions::stop_timer() {  // Stops timer and resets timer integer
    p_timer->stop();
    time = 10;
    ui->Time->setNum(time);
}

void deposit_instructions::reset(ids_t *id) {  // Resets the uis
    p_id = id;
    p_timer->start(1000);
    p_deposit->reset_sum();
    ui->label->setText(
        "Aloita talletus painamalla 'Aloita' ja syötä aukeavassa ikkunassa summa jonka haluat "
        "tallettaa, tai peruuta painamalla 'Sulje'");
    ui->start->show();
    p_rest->get_account_info(p_id->account_id);
    this->show();
}

void deposit_instructions::on_Close_clicked() {
    stop_timer();
    this->hide();
}

void deposit_instructions::update_balance(account_info_t info) {
    this->info = info;
    ui->Bank_account_num->setText(info.account_num);
    ui->Balance->setText(QString().setNum(info.balance));
    p_deposit->account_num = info.account_num;
    p_deposit->balance = info.balance;
}
