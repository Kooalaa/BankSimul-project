#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H

#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QObject>
#include <QtNetwork>

// Struct to package ids for easier transportasion over functions
struct ids_t {
    // Fields
    int customer_id;
    int account_id;
    int card_id;

    // Methods
    ids_t() {}
    ids_t(int init) {
        customer_id = init;
        account_id = init;
        card_id = init;
    }
    ids_t(int customer_id, int account_id, int card_id) {
        this->customer_id = customer_id;
        this->account_id = account_id;
        this->card_id = card_id;
    }

    void operator=(int init) {
        customer_id = init;
        account_id = init;
        card_id = init;
    }
};

class network_handler : public QObject {
    Q_OBJECT
public:
    explicit network_handler(QObject *parent = nullptr);
    ~network_handler();
    void request_token();
    void try_login(QString atm_token);
    void request_mobile_token(int card_id);
    void request_new_mobile_token(int card_id);
    void cancel_login_request(QString atm_token);

private:
    QNetworkReply *get_reply(QObject *sender);
    QJsonObject get_json_obj(QNetworkReply *reply);
    QNetworkAccessManager *p_manager;
    QString base_url = "https://astru.ddns.net:8443";

signals:
    void got_token(QString token);
    void logged_in(ids_t ids, int64_t card_num);
    void cancel_login();
    void got_mobile_token(QString mobile_token);

private slots:
    void handle_token_response();
};

#endif  // NETWORK_HANDLER_H
