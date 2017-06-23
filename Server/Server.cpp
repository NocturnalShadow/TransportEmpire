#include "Server/Server.h"
#include "Server/ServerBuilder.h"
#include "Server/ClientConnection.h"
#include "Server/ConnectionManager.h"
#include "Server/Router.h"

#include "Utility.h"

namespace srv {

Server::Server()
    : router{ new Router{ this } },
      connectionManager {
          new ConnectionManager{ name, securityMode, this }
      },
      origin{ QThread::currentThread() }
{
    qStdOut() << securityMode << endl;
    connect(connectionManager, &ConnectionManager::newConnection,
            router, &Router::registerConnection);
}

Server::~Server()
{
    terminate();
}

ServerBuilder Server::build()
{
    return ServerBuilder{};
}

void Server::setControllerSuite(ControllerSuite* suite)
{
    suite->setParent(this);
    router->addControllerSuite(suite);
}

void Server::launch()
{
    bool success = connectionManager->open(address, port);
    if(success) {
        emit launched();
    } else {
        emit failedToLaunch();
    }
}

void Server::launchAsync()
{
    QThread* thread = new QThread;
    this->moveToThread(thread);

    connect(thread, &QThread::started, this, &Server::launch);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    connect(this, &Server::terminated, thread, &QThread::quit);
    connect(this, &Server::failedToLaunch, thread, &QThread::quit);

    thread->start();
}


void Server::terminate()
{
    QMetaObject::invokeMethod(this, "onTerminate");
}

void Server::onTerminate()
{
    connectionManager->close();
    emit terminated();
    this->moveToThread(origin);
}

} // srv namespace
