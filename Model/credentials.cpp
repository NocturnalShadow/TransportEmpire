#include "credentials.h"


Credentials::Credentials(const QJsonObject& credentials)
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
