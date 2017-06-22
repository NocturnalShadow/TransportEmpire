QT += core widgets websockets network concurrent testlib
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

#DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_DEBUG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Database/Database.h                     \
    Database/Pointer.h                      \
    Database/Transaction.h                  \
    Database/Mapping.h                      \
    Database/Entity.h                       \
    Database/Entity-map.h                   \
    Database/EntityManager-inl.h            \
    Database/EntityManager.h                \
    Model/Credentials.h                     \
    Model/Credentials-map.h                 \
    Model/User.h                            \
    Model/User-map.h                        \
    Server/Server.h                         \
    Server/ServerBuilder.h                  \
    Server/ClientConnection.h               \
    Server/ConnectionManager.h              \
    Server/Request.h                        \
    Server/Response.h                       \
    Server/Router.h                         \
    Server/Task.h                           \
    Server/Controller.h                     \
    Server/ControllerSuite.h                \
    Server/Controllers/RouteController.h    \
    Server/Controllers/UserController.h     \
    Test/TestSuite.h                        \
    Test/Suites/DatabaseSuite.h             \
    Application/Display.h                   \
    Application/Core.h                      \
    Application/TransportEmpire.h           \
    function_traits.h                       \
    Utility.h                               \
    Role.h \
    Model/City.h \
    Model/Location.h \
    Model/Route.h \
    Model/City-map.h \
    Model/Location-map.h \
    Model/Route-map.h

SOURCES += \
    Database/Database.cpp                   \
    Database/EntityManager.cpp              \
    Database/Entity-map.cpp                 \
    Model/Credentials.cpp                   \
    Model/Credentials-map.cpp               \
    Model/User.cpp                          \
    Model/User-map.cpp                      \
    Server/Server.cpp                       \
    Server/ServerBuilder.cpp                \
    Server/ConnectionManager.cpp            \
    Server/ClientConnection.cpp             \
    Server/Request.cpp                      \
    Server/Response.cpp                     \
    Server/Router.cpp                       \
    Server/Controllers/RouteController.cpp  \
    Server/Controllers/UserController.cpp   \
    Test/Suites/DatabaseSuite.cpp           \
    Application/Display.cpp                 \
    Application/Core.cpp                    \
    Application/TransportEmpire.cpp         \
    main.cpp \
    Model/City.cpp \
    Model/Route.cpp \
    Model/Mapping/City-map.cpp \
    Model/Mapping/Location-map.cpp \
    Model/Mapping/route-map.cpp

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
LIBS += -L"$$_PRO_FILE_PWD_/Libraries/ODB/libodb/lib64/"
LIBS += -L"$$_PRO_FILE_PWD_/Libraries/ODB/libodb-mssql/lib64/"
LIBS += -L"$$_PRO_FILE_PWD_/Libraries/ODB/libodb-qt/lib64/"

CONFIG(debug, debug|release) {
    LIBS += -lodb-d
    LIBS += -lodb-mssql-d
    LIBS += -lodb-qt-d
}
CONFIG(release, debug|release) {
    LIBS += -lodb
    LIBS += -lodb-mssql
    LIBS += -lodb-qt
}

FORMS += \
    Application/display.ui


