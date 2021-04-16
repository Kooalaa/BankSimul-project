#ifndef DLL_REST_API_H
#define DLL_REST_API_H

#include <QObject>

#include "DLLRestAPI_global.h"
#include "engine_class.h"

struct customer_info_t {
    QString first_name;
    QString last_name;
    QString phone_num;
    QString address;
};

class DLLRESTAPI_EXPORT dll_rest_api : public QObject {
    Q_OBJECT
public:
    dll_rest_api(QObject *parent = nullptr);
    ~dll_rest_api();
    void login(QByteArray hash, int card_num);
    void get_customer_info(int customer_id);

private:
    engine_class *p_engine;
    ids_t *p_ids;
    customer_info_t customer_info;

signals:
    void wrong_pin(int attempts);
    void card_locked();
    void logged_in(ids_t ids);
    void info_ready(customer_info_t info);

private slots:
    void read_result(int status, int attempts, ids_t ids);
    void read_result(QString first_name, QString last_name, QString phone_num, QString address);
};

#endif  // DLL_REST_API_H
