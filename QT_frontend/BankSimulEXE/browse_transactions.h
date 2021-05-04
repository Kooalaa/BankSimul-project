#ifndef BROWSE_TRANSACTIONS_H
#define BROWSE_TRANSACTIONS_H
#include <dll_rest_api.h>

#include <QDialog>

#include "graphical_transaction_view.h"

namespace Ui {
class browse_transactions;
}
class Main_window;

class browse_transactions : public QDialog {
    Q_OBJECT

public:
    explicit browse_transactions(QWidget *parent = nullptr);
    ~browse_transactions();
    void transaction_menu(ids_t *ids, Main_window *main_wnd);

private slots:
    void on_close_btn_clicked();
    void on_log_out_btn_clicked();
    void on_forward_btn_clicked();
    void on_back_btn_clicked();
    void reset_timer();
    void on_pushButton_clicked();

private:
    Ui::browse_transactions *ui;
    ids_t *p_ids;
    Main_window *main_wnd;
    dll_rest_api *p_rest;
    QTimer *p_timer;
    int time;
    int page = 0;
    int page_num;
    int pages;
    graphical_transaction_view *graph_view;
};

#endif  // BROWSE_TRANSACTIONS_H
