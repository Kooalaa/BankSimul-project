#include "network_handler.h"

network_handler::network_handler(QObject *parent) : QObject(parent) {
    p_manager = new QNetworkAccessManager(this);
}

network_handler::~network_handler() {
    delete p_manager;
    p_manager = nullptr;
}

// Request a new atm_token from the server.
void network_handler::request_token() {
    QString site_url = base_url + "/mobile/atm";

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this] {
        QNetworkReply *reply = get_reply(sender());
        QJsonObject obj = get_json_obj(reply);
        emit got_token(obj["token"].toString());
        reply->deleteLater();
    });
}

// Try to login and wait for response before cancelling.
void network_handler::try_login(QString atm_token) {
    QString site_url = base_url + "/mobile/login/" + atm_token;

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this] {
        QNetworkReply *reply = get_reply(sender());

        if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 504) {
            emit cancel_login();
            reply->deleteLater();
            return;
        }

        QJsonObject obj = get_json_obj(reply);
        if (obj["status"].toInt()) {
            QJsonObject ids_obj = obj["ids"].toObject();

            ids_t ids = {ids_obj["card_id"].toInt(), ids_obj["account_id"].toInt(),
                         ids_obj["customer_id"].toInt()};
            int64_t card_num = obj["card_num"].toDouble();

            emit logged_in(ids, card_num);
        } else {
            emit cancel_login();
        }
        reply->deleteLater();
    });
}

// Get the mobile token from databes or if no token exist get a new one.
void network_handler::request_mobile_token(int card_id) {
    QString site_url = base_url + "/mobile/token/" + QString().setNum(card_id);

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->put(request, QJsonDocument().toJson());

    connect(reply, &QNetworkReply::finished, this, &network_handler::handle_token_response);
}

// Get a new mobile token.
void network_handler::request_new_mobile_token(int card_id) {
    QString site_url = base_url + "/mobile/new_token/" + QString().setNum(card_id);

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->put(request, QJsonDocument().toJson());

    connect(reply, &QNetworkReply::finished, this, &network_handler::handle_token_response);
}

// Cancel the login request
void network_handler::cancel_login_request(QString atm_token) {
    QString site_url = base_url + "/mobile/cancel/" + atm_token;

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->deleteResource(request);

    connect(reply, &QNetworkReply::finished, this, [this] {
        QNetworkReply *reply = get_reply(sender());
        qDebug() << get_json_obj(reply);
        reply->deleteLater();
    });
}

void network_handler::handle_token_response() {
    QNetworkReply *reply = get_reply(sender());
    QJsonObject obj = get_json_obj(reply);

    QString token = obj["token"].toString();
    emit got_mobile_token(token);

    reply->deleteLater();
}

// Helper functions.
// Helper to get reply pointer.
QNetworkReply *network_handler::get_reply(QObject *sender) {
    return qobject_cast<QNetworkReply *>(sender);
}

// Helper to convert reply data to Json object.
QJsonObject network_handler::get_json_obj(QNetworkReply *reply) {
    return QJsonDocument::fromJson(reply->readAll()).object();
}
