#ifndef WITHDRAW_H
#define WITHDRAW_H
#include <dll_rest_api.h>

#include <QButtonGroup>
#include <QDebug>
#include <QDialog>
#include <QTimer>

#include "withdraw_done.h"
#include "withdraw_error.h"
namespace Ui {
class withdraw;
}

class withdraw : public QDialog {
    Q_OBJECT

public:
    explicit withdraw(QWidget *parent = nullptr);
    ~withdraw();
    void show_ui(ids_t *);
signals:
    void return_to_main();
private slots:
    void timer_timeout();
    void on_Sulje_clicked();
    void handle_buttons(QAbstractButton *button);
    void set_account_info(account_info_t info);
    void set_customer_info(customer_info_t);
    void update_balance(double);

private:
    void show_withdraw_done();

private:
    Ui::withdraw *ui;
    QTimer *timer;
    int time_int = 10;
    void stop_timer();
    dll_rest_api *p_rest;
    account_info_t info;
    ids_t *p_id;
    double sum;
    withdraw_done *p_withdraw_done;
    withdraw_error *p_error;
    QString name;
};

#endif  // WITHDRAW_H
