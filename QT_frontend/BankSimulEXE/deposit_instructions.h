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
private slots:
    void on_start_clicked();
    void deposit_done();
    void timer();
    void on_Close_clicked();
    void update_balance(account_info_t info);

private:
    Ui::deposit_instructions *ui;
    deposit *p_deposit;
    int time = 10;
    QTimer *p_timer;
    void stop_timer();
    dll_rest_api *p_rest;
    double new_balance;
    ids_t *p_id;
    account_info_t info;
};

#endif  // DEPOSIT_INSTRUCTIONS_H
