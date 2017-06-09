QT += core websockets concurrent testlib
QT -= gui

CONFIG += c++11
CONFIG += warn_off

TARGET = TransportEmpire
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Database/Database.h                     \
    Database/Pointer.h                      \
    Database/Mapping.h                      \
    Database/Entity.h                       \
    Database/Entity-map.h                   \
    Database/EntityManager-inl.h            \
    Database/EntityManager.h                \
    Model/Credentials.h                     \
    Model/Credentials-map.h                 \
    Model/User.h                            \
    Model/User-map.h                        \
    Server/ClientConnection.h               \
    Server/ConnectionManager.h              \
    Server/Request.h                        \
    Server/Router.h                         \
    Server/RouterWizard.h                   \
    Server/Controller.h                     \
    Server/Controllers/RouteController.h    \
    Server/Controllers/UserController.h     \
    Test/TestSuite.h                        \
    Utility.h \
    Server/Response.h \
    Server/Task.h \
    Role.h \
    Server/Server.h \
    Test/Server/Client.h

SOURCES += \
    Database/Database.cpp                   \
    Database/EntityManager.cpp              \
    Database/Entity-map.cpp                 \
    Model/City.cpp                          \
    Model/Credentials.cpp                   \
    Model/Route.cpp                         \
    Model/User.cpp                          \
    Server/ConnectionManager.cpp            \
    Server/ClientConnection.cpp             \
    Server/Request.cpp                      \
    Server/Router.cpp                       \
    Server/Controllers/RouteController.cpp  \
    Server/Controllers/UserController.cpp   \
    main.cpp \
    Server/Response.cpp \
    Server/Server.cpp \
    Test/Server/Client.cpp

# Select the database we are going to use.
#
DEFINES += DATABASE_MSSQL

# Set ODB headers paths
#
INCLUDEPATH += "./Libraries/ODB/libodb"
INCLUDEPATH += "./Libraries/ODB/libodb-mssql"
INCLUDEPATH += "./Libraries/ODB/libodb-qt"

# Link to the ODB runtime libraries.
#
LIBS += -L"$$_PRO_FILE_PWD_/Libraries/ODB/libodb/lib64/"        -lodb
LIBS += -L"$$_PRO_FILE_PWD_/Libraries/ODB/libodb-mssql/lib64/"  -lodb-mssql
LIBS += -L"$$_PRO_FILE_PWD_/Libraries/ODB/libodb-qt/lib64/"     -lodb-qt

