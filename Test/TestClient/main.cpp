#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>

#include <iostream>

#include "Client.h"


enum Type {
    LOGIN,
    ADD_ROUTE,
    GET_ROUTE,
    GET_ROUTE_LIST
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test::Client client;
    client.connect(QUrl{ "ws://localhost:8080" });

    QTest::qWait(2000);     // does not block

    QJsonObject message;
    message["command"] = LOGIN;
    message["data"] = QJsonObject{ { "credentials", "User credentials." } };
    client.sendMessage(QJsonDocument{ message }.toJson(QJsonDocument::Compact));

    std::cout
            << "Response: "
            << client.takeFirstMessage(500).toStdString()
            << std::endl;

    QTest::qWait(50);

    message["command"] = ADD_ROUTE;
    message["data"] = QJsonObject{ { "route", "Route data." } };
    client.sendMessage(QJsonDocument{ message }.toJson(QJsonDocument::Compact));

    std::cout
            << "Response: "
            << client.takeFirstMessage().toStdString()
            << std::endl;

    QTest::qWait(50);

    // TODO: error message handling
    message["fake"] = ADD_ROUTE;
    message["data"] = QJsonObject{ { "route", "Route data." } };
    client.sendMessage(QJsonDocument{ message }.toJson(QJsonDocument::Compact));

    std::cout
            << "Response: "
            << client.takeFirstMessage().toStdString()
            << std::endl;

    return a.exec();
}
