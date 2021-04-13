
#include "engine_class.h"

engine_class::engine_class() {}

void engine_class::login(QByteArray hash, int card_num) {
    QJsonObject json;
    json.insert("hash", QString(hash.toBase64()));
    json.insert("card_num", card_num);

    QString site_url = "http://192.168.1.2:8080/login";

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    p_manager = new QNetworkAccessManager(this);

    connect(p_manager, &QNetworkAccessManager::finished, this, &engine_class::request_response);

    p_manager->post(request, QJsonDocument(json).toJson());
}

void engine_class::request_response(QNetworkReply *reply) {
    QByteArray response_date = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_date);
    QJsonObject json_obj = json_doc.object();

    ids_t ids;
    ids.account_id = QString::number(json_obj["Tili_id"].toInt());
    ids.customer_id = QString::number(json_obj["Asiakas_id"].toInt());
    ids.card_id = QString::number(json_obj["id"].toInt());

    qDebug() << ids.account_id;
    qDebug() << ids.customer_id;
    qDebug() << ids.card_id;

    return;
}
