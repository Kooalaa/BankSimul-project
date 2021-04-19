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

struct account_info_t {
    QString account_num;
    double balance;
};

class DLLRESTAPI_EXPORT dll_rest_api : public QObject {
    Q_OBJECT
public:
    dll_rest_api(QObject *parent = nullptr);
    ~dll_rest_api();
    void login(QByteArray hash, int card_num);
    void get_customer_info(int customer_id);
    void get_account_info(int account_id);
    void get_card_status(int card_num);
    void get_transactions(int account_id, int index);
    void add_transaction(int account_id, int sum);
    void get_transactions_pages(int account_id);

private:
    engine_class *p_engine;
    ids_t ids;
    customer_info_t customer_info;
    account_info_t account_info;
    QVector<transaction_t> transactions;
    int pages;

signals:
    void wrong_pin(int attempts);
    void card_locked();
    void logged_in(ids_t ids);
    void info_ready(customer_info_t info);
    void info_ready(account_info_t info);
    void info_ready(QVector<transaction_t> transactions);
    void status_ready(bool locked, int attempts);
    void transactions_pages(int pages);

private slots:
    void read_result(int status, int attempts, ids_t ids);
    void read_result(QString first_name, QString last_name, QString phone_num, QString address);
    void read_result(QString account_num, double balance);
    void read_result(bool locked, int attempts);
    void read_result(QVector<transaction_t> transactions);
    void read_result(int amount);
};

#endif  // DLL_REST_API_H
