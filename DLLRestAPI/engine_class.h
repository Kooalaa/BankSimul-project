#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <QByteArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QString>
#include <QtNetwork>

struct ids_t {
    QString customer_id;
    QString account_id;
    QString card_id;
};

class engine_class : public QObject {
    Q_OBJECT

public:
    engine_class();
    void login(QByteArray hash, int card_num);

private slots:
    void request_response(QNetworkReply* reply);

private:
    QNetworkAccessManager* p_manager;
};

#endif  // ENGINE_CLASS_H
