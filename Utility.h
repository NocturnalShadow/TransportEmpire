#pragma once

#include <QVector>
#include <QThread>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include "Database/Pointer.h"

template<typename T>
QVector<Pointer<T>> toVector(const QJsonArray& jsonArray)
{
    QVector<Pointer<T>> vector;
    for(const auto& item : jsonArray) {
        Pointer<T> temp = make<T>(item.toObject());
        vector.append(temp);
    }
    return std::move(vector);
}

template<typename T>
QJsonArray toJsonArray(const QVector<T>& vector)
{
    QJsonArray jsonArray;
    for(const auto& item : vector) {
        jsonArray.append(item->toJsonObject());
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
