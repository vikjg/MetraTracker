#ifndef TRAINMODEL_H
#define TRAINMODEL_H

#include <QAbstractListModel>
#include <QList>

struct Train {
    QString routeId;
    double latitude;
    double longitude;
};

class TrainModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit TrainModel(QObject *parent = nullptr);

    enum TrainRoles {
        RouteIdRole = Qt::UserRole + 1,
        LatitudeRole,
        LongitudeRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void trainsUpdated();

public slots:
    void updateTrains(const QList<Train> &trains);

private:
    QList<Train> m_trains;
};

#endif // TRAINMODEL_H
