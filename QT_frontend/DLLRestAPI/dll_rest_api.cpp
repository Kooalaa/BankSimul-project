#include "dll_rest_api.h"

dll_rest_api::dll_rest_api(QObject *parent) : QObject(parent) {
    p_engine = new engine_class;
    connect(p_engine, qOverload<int, int, ids_t>(&engine_class::result_ready), this,
            qOverload<int, int, ids_t>(&dll_rest_api::read_result));
    connect(p_engine, qOverload<QString, QString, QString, QString>(&engine_class::result_ready),
            this, qOverload<QString, QString, QString, QString>(&dll_rest_api::read_result));
}

dll_rest_api::~dll_rest_api() {
    delete p_engine;
    p_engine = nullptr;
}

void dll_rest_api::login(QByteArray hash, int card_num) { p_engine->login(hash, card_num); }

void dll_rest_api::get_customer_info(int customer_id) { p_engine->customer_info(customer_id); }

void dll_rest_api::read_result(int status, int attempts, ids_t ids) {
    switch (status) {
        case -1:
            emit card_locked();
            break;
        case 0:
            emit wrong_pin(attempts);
            break;
        case 1:
            emit logged_in(ids);
            break;
    }
}

void dll_rest_api::read_result(QString first_name, QString last_name, QString phone_num,
                               QString address) {
    qDebug() << "Got signal";
    customer_info.first_name = first_name;
    customer_info.last_name = last_name;
    customer_info.phone_num = phone_num;
    customer_info.address = address;
    emit info_ready(customer_info);
}
