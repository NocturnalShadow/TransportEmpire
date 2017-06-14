#pragma once

#include <QVector>
#include <QThread>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>

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


inline QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}

inline auto threadId()
{
    return QThread::currentThreadId();
}
