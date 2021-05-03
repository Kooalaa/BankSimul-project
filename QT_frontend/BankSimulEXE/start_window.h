#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <dll_mobile_login.h>
#include <dll_rest_api.h>
#include <dllpincode.h>
#include <dllserialport.h>

#include <QDebug>
#include <QMainWindow>

#include "main_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class start_window;
}
QT_END_NAMESPACE

class start_window : public QMainWindow {
    Q_OBJECT

public:
    start_window(QWidget *parent = nullptr);
    ~start_window();

private:
    Ui::start_window *ui;
    DLLPincode *p_pincode;
    Main_window *p_main_window;
    dll_rest_api *p_rest;
    DLLSerialPort *p_serial_port;
    dll_mobile_login *p_mobile;

private slots:
    void logged_in(ids_t ids);
    void pin_received(QByteArray hash);
    void card_inserted(QString num);
    void get_status(bool locked);
    void logout();

    // Mobile login slots:
    void logged_in(ids_t ids, int64_t card_num);
    void on_mobile_btn_clicked();
};
#endif  // START_WINDOW_H
