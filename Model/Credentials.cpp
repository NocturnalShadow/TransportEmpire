#include "Credentials.h"


Credentials::Credentials(Role _role, QString _login, QString _password)
    : role{ _role }, login{ _login }, password{ _password }
{
}

Credentials::Credentials(QJsonObject credentials)
    : login { credentials["login"].toString() },
      password { credentials["password"].toString() }
{
}

QJsonObject Credentials::toJsonObject() const
{
    QJsonObject credentials;
    credentials["login"] = login;
    credentials["password"] = password;
    return credentials;
}
