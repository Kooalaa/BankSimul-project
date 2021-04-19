#include "dll_rest_api.h"

dll_rest_api::dll_rest_api(QObject *parent) : QObject(parent) {
    p_engine = new engine_class;

    connect(p_engine, qOverload<int, int, ids_t>(&engine_class::result_ready), this,
            qOverload<int, int, ids_t>(&dll_rest_api::read_result));

    connect(p_engine, qOverload<QString, QString, QString, QString>(&engine_class::result_ready),
            this, qOverload<QString, QString, QString, QString>(&dll_rest_api::read_result));

    connect(p_engine, qOverload<QString, double>(&engine_class::result_ready), this,
            qOverload<QString, double>(&dll_rest_api::read_result));

    connect(p_engine, qOverload<bool, int>(&engine_class::result_ready), this,
            qOverload<bool, int>(&dll_rest_api::read_result));

    connect(p_engine, qOverload<QVector<transaction_t>>(&engine_class::result_ready), this,
            qOverload<QVector<transaction_t>>(&dll_rest_api::read_result));

    connect(p_engine, qOverload<int>(&engine_class::result_ready), this,
            qOverload<int>(&dll_rest_api::read_result));
}

dll_rest_api::~dll_rest_api() {
    delete p_engine;
    p_engine = nullptr;
}

void dll_rest_api::login(QByteArray hash, int card_num) { p_engine->login(hash, card_num); }
void dll_rest_api::get_customer_info(int customer_id) { p_engine->customer_info(customer_id); }
void dll_rest_api::get_account_info(int account_id) { p_engine->account_info(account_id); }
void dll_rest_api::get_card_status(int card_num) { p_engine->card_status(card_num); }
void dll_rest_api::get_transactions(int account_id, int index) {
    p_engine->transactions(account_id, index);
}
void dll_rest_api::add_transaction(int account_id, int sum) {
    p_engine->add_transaction(account_id, sum);
}
void dll_rest_api::get_transactions_pages(int account_id) {
    p_engine->transaction_amount(account_id);
}

void dll_rest_api::read_result(int status, int attempts, ids_t ids) {
    switch (status) {
        case -1:
            emit card_locked();
            break;
        case 0:
            emit wrong_pin(attempts);
            break;
        case 1:
            this->ids = ids;
            emit logged_in(ids);
            break;
    }
}

void dll_rest_api::read_result(QString first_name, QString last_name, QString phone_num,
                               QString address) {
    customer_info.first_name = first_name;
    customer_info.last_name = last_name;
    customer_info.phone_num = phone_num;
    customer_info.address = address;

    emit info_ready(customer_info);
}

void dll_rest_api::read_result(QString account_num, double balance) {
    account_info.account_num = account_num;
    account_info.balance = balance;

    emit info_ready(account_info);
}

void dll_rest_api::read_result(bool locked, int attempts) { emit status_ready(locked, attempts); }

void dll_rest_api::read_result(QVector<transaction_t> transactions) {
    this->transactions = transactions;
    emit info_ready(transactions);
}

void dll_rest_api::read_result(int amount) {
    pages = amount / 10 + ((amount % 10) == 0 ? 0 : 1);
    emit transactions_pages(pages);
}
