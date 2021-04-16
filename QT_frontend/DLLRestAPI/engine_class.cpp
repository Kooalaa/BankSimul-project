
#include "engine_class.h"

engine_class::engine_class() { p_manager = new QNetworkAccessManager(this); }

engine_class::~engine_class() {
    delete p_manager;
    p_manager = nullptr;
}

// Posts a login request to the RestAPI.
void engine_class::login(QByteArray hash, int card_num) {
    QJsonObject json;
    json.insert("hash", QString(hash.toBase64()));
    json.insert("card_num", card_num);

    QString site_url = "http://192.168.1.2:8080/login";

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(p_manager, &QNetworkAccessManager::finished, this, &engine_class::login_response);

    p_manager->post(request, QJsonDocument(json).toJson());
}

void engine_class::customer_info(int customer_id) {
    QString site_url = "http://192.168.1.2:8080/customer/" + QString().setNum(customer_id);

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(p_manager, &QNetworkAccessManager::finished, this, &engine_class::customer_response);

    p_manager->get(request);
}

// Receives the request response message
void engine_class::login_response(QNetworkReply *reply) {
    QByteArray response_date = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_date);
    QJsonObject json_obj = json_doc.object();

    QJsonObject ids_obj = json_obj["ids"].toObject();

    ids_t ids;
    ids.account_id = ids_obj["account_id"].toInt();
    ids.customer_id = ids_obj["customer_id"].toInt();
    ids.card_id = ids_obj["card_id"].toInt();
    int status = json_obj["status"].toInt();
    int attempts = json_obj["attempts_left"].toInt();

    qDebug() << ids.account_id;
    qDebug() << ids.customer_id;
    qDebug() << ids.card_id;

    emit result_ready(status, attempts, ids);
    disconnect(p_manager, &QNetworkAccessManager::finished, this, &engine_class::login_response);
}

void engine_class::customer_response(QNetworkReply *reply) {
    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QString first_name = json_obj["Nimi"].toString();
    QString last_name = json_obj["Sukunimi"].toString();
    QString address = json_obj["Osoite"].toString();
    QString phone_num = json_obj["Puhelinnumero"].toString();

    qDebug() << first_name;
    qDebug() << last_name;
    qDebug() << phone_num;
    qDebug() << address;

    emit result_ready(first_name, last_name, phone_num, address);
    disconnect(p_manager, &QNetworkAccessManager::finished, this, &engine_class::customer_response);
}
