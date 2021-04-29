#include "dll_mobile_login.h"

dll_mobile_login::dll_mobile_login(QObject *parent) : QObject(parent) {
    p_display = new QR_display;
    p_network = new network_handler;
    ids = -1;
    token = "null";

    connect(p_network, &network_handler::got_token, this, &dll_mobile_login::got_token);
    connect(p_network, &network_handler::logged_in, this, &dll_mobile_login::login_success);
    connect(p_network, &network_handler::cancel_login, this, &dll_mobile_login::login_canceled);
}

dll_mobile_login::~dll_mobile_login() { delete p_network; }

// network_handler callers:
void dll_mobile_login::get_token() { p_network->request_token(); }
void dll_mobile_login::try_login(QString atm_token) { p_network->try_login(atm_token); }
void dll_mobile_login::try_login() { p_network->try_login(token); }

ids_t dll_mobile_login::get_ids() const { return ids; }

// Slots:
void dll_mobile_login::got_token(QString atm_token) {
    this->token = atm_token;
    p_display->start(token);
    emit token_ready(atm_token);
}

void dll_mobile_login::login_success(ids_t ids, int64_t card_num) {
    this->ids = ids;
    emit logged_in(ids, card_num);
}

void dll_mobile_login::login_canceled() { emit cancel_login(); }
