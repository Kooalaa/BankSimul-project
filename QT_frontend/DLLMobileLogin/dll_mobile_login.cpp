#include "dll_mobile_login.h"

dll_mobile_login::dll_mobile_login(QObject *parent) : QObject(parent) {
    p_display = new QR_display;
    p_mobile_display = new QR_mobile_token;
    p_network = new network_handler;

    ids = -1;
    atm_token = "null";
    mobile_token = "null";
    connect(p_network, &network_handler::got_token, this, &dll_mobile_login::got_token);
    connect(p_network, &network_handler::logged_in, this, &dll_mobile_login::login_success);
    connect(p_network, &network_handler::cancel_login, this, &dll_mobile_login::login_canceled);
    connect(p_network, &network_handler::got_mobile_token, this,
            &dll_mobile_login::got_mobile_token);

    connect(p_mobile_display, &QR_mobile_token::request_new_token, this,
            [this] { generate_new_mobile_token(ids.account_id); });
    connect(p_display, &QR_display::cancel_login, this,
            [this] { p_network->cancel_login_request(atm_token); });
}

dll_mobile_login::~dll_mobile_login() {
    delete p_network;
    delete p_display;
    delete p_mobile_display;
}

// Start full login process.
void dll_mobile_login::login() {
    callback.append(&dll_mobile_login::try_login);
    get_atm_token();
}

// network_handler calls:
void dll_mobile_login::get_atm_token() { p_network->request_token(); }
void dll_mobile_login::try_login(QString atm_token) { p_network->try_login(atm_token); }
void dll_mobile_login::try_login() { p_network->try_login(atm_token); }
void dll_mobile_login::get_or_generate_mobile_token(int card_id) {
    p_network->request_mobile_token(card_id);
}
void dll_mobile_login::generate_new_mobile_token(int card_id) {
    p_network->request_new_mobile_token(card_id);
}

// Getters:
ids_t dll_mobile_login::get_ids() const { return ids; }

// Slots:
void dll_mobile_login::got_token(QString atm_token) {
    this->atm_token = atm_token;
    p_display->start(atm_token);

    if (!callback.isEmpty()) {
        foreach (void (dll_mobile_login::*call)(), callback) { (this->*call)(); }
        callback.clear();
    }

    emit token_ready(atm_token);
}

void dll_mobile_login::login_success(ids_t ids, int64_t card_num) {
    this->ids = ids;
    p_display->stop();
    emit logged_in(ids, card_num);
}

void dll_mobile_login::login_canceled() {
    p_display->stop();
    emit cancel_login();
}

void dll_mobile_login::got_mobile_token(QString mobile_token) {
    this->mobile_token = mobile_token;
    p_mobile_display->start(mobile_token);
}
