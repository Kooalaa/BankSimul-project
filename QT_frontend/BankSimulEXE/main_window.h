#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <dll_mobile_login.h>
#include <dll_rest_api.h>

#include <QDialog>

#include "balance.h"
#include "browse_transactions.h"
#include "deposit_instructions.h"
#include "withdraw.h"
#include "withdraw_done.h"
namespace Ui {
class Main_window;
}

class Main_window : public QDialog {
    Q_OBJECT

public:
    explicit Main_window(QWidget *parent = nullptr);
    ~Main_window();
    void set_ids(ids_t ids);
    void set_card_num(const int64_t &card_num);
    void show_ui();

private:
    // Auto generated
    Ui::Main_window *ui;

    // Pointers:
    dll_rest_api *p_rest;
    dll_mobile_login *p_mobile;
    withdraw *p_withdraw;
    browse_transactions *p_browse;
    balance *p_balance;
    deposit_instructions *p_deposit_instruct;
    QTimer *p_timer;    
    withdraw_done *p_withdraw_done;
    ids_t *p_ids;

    // Variables
    int time = 30;
    QString name;
    int64_t card_num;

    // Functions
    void stop_timer();

signals:
    void logout();

private slots:
    void on_Browse_transactions_btn_clicked();
    void on_Deposit_btn_clicked();
    void on_Show_balance_btn_clicked();
    void on_Withdraw_btn_clicked();
    void on_Log_out_btn_clicked();
    void timer();
    void set_account_info(account_info_t);
    void set_customer_info(customer_info_t);
    void return_to_main_slot();
    void on_mobile_login_btn_clicked();
};

#endif  // MAIN_WINDOW_H
