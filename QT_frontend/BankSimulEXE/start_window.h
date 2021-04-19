#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <dll_rest_api.h>
#include <dllpincode.h>

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

private slots:
    void logged_in(ids_t ids);
    void pin_received(QByteArray hash);
    void card_inserted();

private:
    Ui::start_window *ui;
    DLLPincode *p_pincode;
    Main_window *p_main_window;
    dll_rest_api *p_rest;
};
#endif  // START_WINDOW_H
