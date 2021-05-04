#ifndef DEPOSIT_INSTRUCTIONS_H
#define DEPOSIT_INSTRUCTIONS_H

#include <dll_rest_api.h>

#include <QDialog>

#include "deposit.h"

namespace Ui {
class deposit_instructions;
}

class deposit_instructions : public QDialog {
    Q_OBJECT

public:
    explicit deposit_instructions(QWidget *parent = nullptr);
    ~deposit_instructions();
    void reset(ids_t *);
signals:
    void log_out();
    void return_to_main();
private slots:
    void on_start_clicked();
    void deposit_done();
    void timer();
    void on_Close_clicked();
    void set_account_info(account_info_t info);
    void set_customer_info(customer_info_t);

private:
    Ui::deposit_instructions *ui;
    deposit *p_deposit;
    QTimer *p_timer;
    dll_rest_api *p_rest;
    ids_t *p_id;
    account_info_t info;
    QString name;
    int time = 10;
    double new_balance;
    void stop_timer();
    int status;
};

#endif  // DEPOSIT_INSTRUCTIONS_H
