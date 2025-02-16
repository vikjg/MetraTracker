#include "trainfetcher.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>

TrainFetcher::TrainFetcher(TrainModel* model, QObject *parent)
    : QObject(parent), m_model(model) {

    // Fetch train data every 15 seconds
    connect(&m_timer, &QTimer::timeout, this, &TrainFetcher::fetchTrainData);
    m_timer.start(15000);

    // Fetch data immediately on startup
    fetchTrainData();
}

void TrainFetcher::fetchTrainData() {
    QString username = "insert_username_here";
    QString password = "insert_password_here";

    // Combine username and password into "username:password" format
    QString credentials = username + ":" + password;

    // Base64 encode the credentials
    QByteArray authData = credentials.toUtf8().toBase64();

    // Create the request
    QNetworkRequest request(QUrl("https://gtfsapi.metrarail.com/gtfs/positions"));
    request.setRawHeader("Authorization", "Basic " + authData);  // Set the Authorization header
    m_manager.get(request);

    connect(&m_manager, &QNetworkAccessManager::finished, this, &TrainFetcher::handleNetworkReply);
}


void TrainFetcher::handleNetworkReply(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Network error: " << reply->errorString().toStdString() << std::endl;
        reply->deleteLater();
        return;
    }

    // Parse JSON
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.isArray()) {
        //std::cerr << "Invalid JSON format!" << std::endl;
        reply->deleteLater();
        return;
    }

    QJsonArray jsonArray = doc.array();
    QList<Train> trainList;

    for (const auto &value : jsonArray) {
        QJsonObject obj = value.toObject();
        QJsonObject vehicle = obj["vehicle"].toObject();
        QJsonObject position = vehicle["position"].toObject();

        Train train;
        train.routeId = vehicle["trip"].toObject()["route_id"].toString();
        train.latitude = position["latitude"].toDouble();
        train.longitude = position["longitude"].toDouble();

        trainList.append(train);

        // // Debugging output: print the parsed train information
        // std::cout << "Route ID: " << train.routeId.toStdString() << std::endl;
        // std::cout << "Latitude: " << train.latitude << std::endl;
        // std::cout << "Longitude: " << train.longitude << std::endl;
        // std::cout << "-----------------------------" << std::endl;
    }

    // Update TrainModel
    m_model->updateTrains(trainList);

    reply->deleteLater();
}
