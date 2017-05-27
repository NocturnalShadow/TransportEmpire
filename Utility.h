#pragma once

#include <QVector>
#include <QJsonArray>
#include <QJsonObject>

template<typename T>
QVector<T> toVector(const QJsonArray& jsonArray)
{
    QVector<T> vector;
    for(const auto& item : jsonArray) {
        vector.append(item.toObject());
    }
    return std::move(vector);
}

template<typename T>
QJsonArray toJsonArray(const QVector<T>& vector)
{
    QJsonArray jsonArray;
    for(const auto& item : vector) {
        jsonArray.append(item.toJsonObject());
    }
    return std::move(jsonArray);
}
