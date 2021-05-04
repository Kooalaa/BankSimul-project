#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <QByteArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QVector>
#include <QtNetwork>

#include "ids_t.h"

// Struct to package transactions data for easier transportasion over functions
struct transaction_t {
    double sum;
    QString date;
    QString time;
};

class engine_class : public QObject {
    Q_OBJECT

public:
    engine_class();
    ~engine_class();
    void login(QByteArray hash, long long card_num);
    void customer_info(int customer_id);
    void account_info(int account_id);
    void card_status(long long card_num);
    void transactions(int account_id, int index);
    void add_transaction(int account_id, double sum);
    void edit_balance(int account_id, double new_balance);
    void transaction_amount(int account_id);
    void get_transaction_year(int account_id, int year);

private:
    QNetworkAccessManager *p_manager;
    QJsonObject get_json_object(QNetworkReply &reply);
    QJsonArray get_json_array(QNetworkReply &reply);
    const QString site_base_url = "http://astru.ddns.net:8080";

signals:
    void result_ready(int status, int attempts, ids_t ids);
    void result_ready(QString first_name, QString last_name, QString phone_num, QString address);
    void result_ready(QString account_num, double balance);
    void result_ready(bool locked, int attempts);
    void result_ready(QVector<transaction_t> transactions);
    void result_ready(int amount);

private slots:
    void login_response();
    void customer_response();
    void account_response();
    void card_response();
    void transactions_response();
};

#endif  // ENGINE_CLASS_H
