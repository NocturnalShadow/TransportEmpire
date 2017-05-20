#pragma once

#include <QString>
#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

class Credentials
{
private:
    QString login;
    QString password;

public:
    Credentials(const QJsonObject& credentials);

public:
    const QString& getLogin() const { return login; }

public:
    QJsonObject toJsonObject() const;

public:
    void Debug() const
    {
        qDebug().nospace()
                << "Credentials (login: "   << login
                << ", password: "           << password
                << ")";
    }
};

