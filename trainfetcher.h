#ifndef TRAINFETCHER_H
#define TRAINFETCHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include "trainmodel.h"

class TrainFetcher : public QObject {
    Q_OBJECT
public:
    explicit TrainFetcher(TrainModel* model, QObject *parent = nullptr);

private slots:
    void fetchTrainData();
    void handleNetworkReply(QNetworkReply* reply);

private:
    TrainModel* m_model;
    QNetworkAccessManager m_manager;
    QTimer m_timer;
};

#endif // TRAINFETCHER_H
