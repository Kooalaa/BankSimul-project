#ifndef BALANCE_H
#define BALANCE_H

#include <dll_rest_api.h>

#include <QDialog>

namespace Ui {
class balance;
}

class balance : public QDialog {
    Q_OBJECT

public:
    explicit balance(QWidget *parent = nullptr);
    ~balance();
    void init_and_show(ids_t *ids, QDialog *main_wnd);

private slots:
    void on_close_btn_clicked();

private:
    Ui::balance *ui;
    ids_t *p_ids;
    QDialog *main_wnd;
    dll_rest_api *p_rest;
    QTimer *p_timer;
    int time;
};

#endif  // BALANCE_H
