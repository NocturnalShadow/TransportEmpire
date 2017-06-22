#pragma once

#include "Server/Server.h"
#include "Database/Database.h"

#include <QObject>
#include <QScopedPointer>

namespace app {

class Core : public QObject
{
    Q_OBJECT
private:
    QScopedPointer<db::IDatabase>   database;
    QScopedPointer<srv::Server,
        QScopedPointerDeleteLater>  server;

public:
    explicit Core(QObject* parent = nullptr);

public:
    void prepare(std::string login, std::string password);
    void launch();
    void terminate();

signals:
    void serverLaunched();
    void serverTerminated();
    void serverFailedToLaunch();
    void databasePreparationFailed(std::exception_ptr e);
};

} //namespace app
