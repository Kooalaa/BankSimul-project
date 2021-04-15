#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>

#include "balance.h"
#include "browse_transactions.h"
#include "deposit.h"
#include "withdraw.h"

namespace Ui {
class Main_window;
}

class Main_window : public QDialog {
    Q_OBJECT

public:
    explicit Main_window(QWidget *parent = nullptr);
    ~Main_window();

private slots:

    void on_Browse_transactions_btn_clicked();

    void on_Deposit_btn_clicked();

    void on_Show_balance_btn_clicked();

    void on_Withdraw_btn_clicked();

    void on_Log_out_btn_clicked();

private:
    Ui::Main_window *ui;
    withdraw *p_withdraw;
    browse_transactions *pselaa;
    balance *psaldo;
    deposit *ptalleta;
};

#endif  // MAIN_WINDOW_H
