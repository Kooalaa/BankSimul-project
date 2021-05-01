#ifndef DLL_MOBILE_LOGIN_H
#define DLL_MOBILE_LOGIN_H

#include <QObject>

#include "DLLMobileLogin_global.h"
#include "network_handler.h"
#include "qr_display.h"
#include "qr_mobile_token.h"

class DLLMOBILELOGIN_EXPORT dll_mobile_login : public QObject {
    Q_OBJECT
public:
    dll_mobile_login(QObject *parent = nullptr);
    ~dll_mobile_login();

    void login();

    void get_atm_token();
    void try_login(QString atm_token);
    void try_login();
    void get_or_generate_mobile_token(int account_id);
    void generate_new_mobile_token(int account_id);

    ids_t get_ids() const;

private:
    QR_display *p_display;
    QR_mobile_token *p_mobile_display;
    network_handler *p_network;
    QList<void (dll_mobile_login::*)()> callback;
    QString atm_token;
    QString mobile_token;
    ids_t ids;

signals:
    void token_ready(QString atm_token);
    void logged_in(ids_t ids, int64_t card_num);
    void cancel_login();

private slots:
    void got_token(QString atm_token);
    void login_success(ids_t ids, int64_t card_num);
    void login_canceled();
    void got_mobile_token(QString mobile_token);
};

#endif  // DLL_MOBILE_LOGIN_H
