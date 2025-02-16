#include "trainmodel.h"

TrainModel::TrainModel(QObject *parent)
    : QAbstractListModel(parent) {}

int TrainModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_trains.size();
}

QVariant TrainModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_trains.size())
        return QVariant();

    const Train &train = m_trains.at(index.row());
    switch (role) {
    case RouteIdRole: return train.routeId;
    case LatitudeRole: return train.latitude;
    case LongitudeRole: return train.longitude;
    default: return QVariant();
    }
}

QHash<int, QByteArray> TrainModel::roleNames() const {
    return {
        {RouteIdRole, "routeId"},
        {LatitudeRole, "latitude"},
        {LongitudeRole, "longitude"}
    };
}

void TrainModel::updateTrains(const QList<Train> &trains) {
    beginResetModel();
    m_trains = trains;
    emit trainsUpdated();  // Notify QML that the data has changed
    endResetModel();
}
