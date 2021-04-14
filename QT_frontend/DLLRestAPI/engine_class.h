#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <QByteArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QtNetwork>

struct ids_t {
    int customer_id;
    int account_id;
    int card_id;
};

class engine_class : public QObject {
    Q_OBJECT

public:
    engine_class();
    ~engine_class();
    void login(QByteArray hash, int card_num);
    void customer_info(int customer_id);

private slots:
    void login_response(QNetworkReply* reply);
    void customer_response(QNetworkReply* reply);

signals:
    void result_ready(int status, int attempts, ids_t ids);
    void result_ready(QString first_name, QString last_name, QString phone_num, QString address);

private:
    QNetworkAccessManager* p_manager;
};

#endif  // ENGINE_CLASS_H
