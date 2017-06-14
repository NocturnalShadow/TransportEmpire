#include "TransportEmpireApp.h"

#include "Server/Server.h"
#include "Server/ControllerSuite.h"
#include "Server/Controllers/RouteController.h"
#include "Server/Controllers/UserController.h"

#include "Utility.h"

TransportEmpireApp::TransportEmpireApp(QObject* parent)
    : QObject{ parent },
      database{ "TransportEmpireDB" }
{
        database.connect();

        qStdOut() << "Native thread: " << threadId() << endl;

        auto suite = new srv::ControllerSuite{ &database };
        suite->add<srv::UserController>();
        suite->add<srv::RouteController>();

        server = srv::Server::build()
                .name("Test Server")
                .address(QHostAddress::LocalHost)
                .port(8080)
                .controllerSuite(suite)
                .makeUnique();

        server->launchAsync();
}
