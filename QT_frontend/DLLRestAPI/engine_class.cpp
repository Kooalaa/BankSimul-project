
#include "engine_class.h"

engine_class::engine_class() { p_manager = new QNetworkAccessManager(this); }

engine_class::~engine_class() {
    delete p_manager;
    p_manager = nullptr;
}

// Post request to check the login credential and login if they match.
void engine_class::login(QByteArray hash, int card_num) {
    QJsonObject json;
    json.insert("hash", QString(hash.toBase64()));
    json.insert("card_num", card_num);

    QString site_url = site_base_url + "/login";

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, &engine_class::login_response);
}

// Request to get the customer information.
void engine_class::customer_info(int customer_id) {
    QString site_url = site_base_url + "/customer/" + QString().setNum(customer_id);

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &engine_class::customer_response);
}

// Request to get balance and account number of the account.
void engine_class::account_info(int account_id) {
    QString site_url = site_base_url + "/account/" + QString().setNum(account_id);

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &engine_class::account_response);
}

// Request to get info if the card is locked and how many attempts before the card will lock.
void engine_class::card_status(int card_num) {
    QString site_url = site_base_url + "/card/" + QString().setNum(card_num);

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &engine_class::card_response);
}

// Request to get ten transactions
// The index is used to select witch set of ten transactions to reques
void engine_class::transactions(int account_id, int index) {
    QString site_url =
        site_base_url + "/actions/" + QString().setNum(account_id) + "/" + QString().setNum(index);

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &engine_class::transactions_response);
}

void engine_class::add_transaction(int account_id, double sum) {
    QString site_url = site_base_url + "/actions";
    QJsonObject json;
    json.insert("account_id", account_id);
    json.insert("sum", sum);

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, [this]() {
        QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
        QJsonObject json_obj = get_json_object(*reply);
        int insert_id = json_obj["insertId"].toInt();
        qDebug() << insert_id;
        reply->deleteLater();
    });
}

void engine_class::edit_balance(int account_id, double new_balance) {
    QString site_url = site_base_url + "/actions";
    QJsonObject json;
    json.insert("account_id", account_id);
    json.insert("new_balance", new_balance);

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    context = new QObject;

    QNetworkReply *reply = p_manager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, [this]() {
        QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
        QJsonObject json_obj = get_json_object(*reply);
        int changed_rows = json_obj["changedRows"].toInt();
        qDebug() << changed_rows;
        reply->deleteLater();
    });
}

// Gets the ammount of trans actions on the account.
void engine_class::transaction_amount(int account_id) {
    QString site_url = site_base_url + "/actions/" + QString().setNum(account_id);

    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = p_manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this]() {
        QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
        QJsonObject json_obj = get_json_object(*reply);

        int ret_amount = json_obj["amount"].toInt();
        emit result_ready(ret_amount);
        reply->deleteLater();
    });
}

// Receives the request response message
void engine_class::login_response() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QJsonObject json_obj = get_json_object(*reply);

    QJsonObject ids_obj = json_obj["ids"].toObject();

    ids_t ids;
    ids.account_id = ids_obj["account_id"].toInt();
    ids.customer_id = ids_obj["customer_id"].toInt();
    ids.card_id = ids_obj["card_id"].toInt();
    int status = json_obj["status"].toInt();
    int attempts = json_obj["attempts_left"].toInt();

    emit result_ready(status, attempts, ids);
    reply->deleteLater();
}

void engine_class::customer_response() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QJsonObject json_obj = get_json_object(*reply);

    QString first_name = json_obj["Nimi"].toString();
    QString last_name = json_obj["Sukunimi"].toString();
    QString address = json_obj["Osoite"].toString();
    QString phone_num = json_obj["Puhelinnumero"].toString();

    emit result_ready(first_name, last_name, phone_num, address);
    reply->deleteLater();
}

void engine_class::account_response() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QJsonObject json_obj = get_json_object(*reply);

    QString account_num = json_obj["Tilinumero"].toString();
    double balance = json_obj["Saldo"].toDouble();

    emit result_ready(account_num, balance);
    reply->deleteLater();
}

void engine_class::card_response() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QJsonObject json_obj = get_json_object(*reply);

    int attempts = json_obj["Väärä_pin"].toInt();
    bool locked = json_obj["Lukossa"].toBool();

    emit result_ready(locked, attempts);
    reply->deleteLater();
}

void engine_class::transactions_response() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QJsonArray json_arr = get_json_array(*reply);
    QVector<transaction_t> ret;

    foreach (const QJsonValue &json_val, json_arr) {
        QJsonObject json_obj = json_val.toObject();

        // clang-format off
        transaction_t transaction {
            .sum = json_obj["Summa"].toDouble(),
            .date = [&] {
                QString str = json_obj["Aika"].toString();
                QStringList list = str.split("T");
                list[0].remove(0, 1);
                return list[0];
            }(),
            .time = [&] {
                QString str = json_obj["Aika"].toString();
                QStringList list = str.split("T");
                list = list[1].split(".");
                return list[0];
            }()
        };
        // clang-format on
        ret.append(transaction);
    }

    emit result_ready(ret);
    reply->deleteLater();
}

QJsonObject engine_class::get_json_object(QNetworkReply &reply) {
    QByteArray response_data = reply.readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    return json_obj;
}

QJsonArray engine_class::get_json_array(QNetworkReply &reply) {
    QByteArray response_data = reply.readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_arr = json_doc.array();
    return json_arr;
}
