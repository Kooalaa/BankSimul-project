#ifndef DLL_MOBILE_LOGIN_H
#define DLL_MOBILE_LOGIN_H

#include <QObject>

#include "DLLMobileLogin_global.h"
#include "network_handler.h"
#include "qr_display.h"

class DLLMOBILELOGIN_EXPORT dll_mobile_login : public QObject {
    Q_OBJECT
public:
    dll_mobile_login(QObject *parent = nullptr);
    ~dll_mobile_login();
    void get_token();
    void try_login(QString atm_token);
    void try_login();
    ids_t get_ids() const;

private:
    QR_display *p_display;
    network_handler *p_network;
    QString token;
    ids_t ids;

signals:
    void token_ready(QString atm_token);
    void logged_in(ids_t ids, int64_t card_num);
    void cancel_login();

private slots:
    void got_token(QString atm_token);
    void login_success(ids_t ids, int64_t card_num);
    void login_canceled();
};

#endif  // DLL_MOBILE_LOGIN_H
