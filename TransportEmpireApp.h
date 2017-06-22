#pragma once

#include <QObject>

#include <memory>

#include "Server/Server.h"
#include "Database/Database.h"

class TransportEmpireApp : public QObject
{
    Q_OBJECT
private:
    db::Database database;
    std::unique_ptr<srv::Server> server;

public:
    explicit TransportEmpireApp(QObject* parent = nullptr);

public:
    void init();
    void launch();
};

