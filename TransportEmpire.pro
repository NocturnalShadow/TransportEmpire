QT += core websockets testlib
QT -= gui

CONFIG += c++11
CONFIG += warn_off

TARGET = TransportEmpire
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    Server/serverclient.cpp \
    Server/webserver.cpp \
    Server/reply.cpp \
    Server/request.cpp \
    Server/router.cpp \
    Server/routerfactory.cpp \
    Server/Controllers/RouteController.cpp \
    Server/Controllers/UserController.cpp \
    Model/user.cpp \
    Model/credentials.cpp \
    Model/route.cpp \
    Model/city.cpp \
    Database/database.cpp \
    Database/entitymanager.cpp \
    Database/entity-odb.cxx

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
    Test/TestSuite.h \
    Server/serverclient.hpp \
    Server/webserver.hpp \
    Server/controller.h \
    Server/reply.h \
    Server/request.h \
    Server/router.h \
    Server/routerfactory.h \
    Server/Controllers/RouteController.h \
    Server/Controllers/UserController.h \
    specification.h \
    Model/user.h \
    Model/credentials.h \
    Model/route.h \
    Model/city.h \
    Model/location.h \
    utility.h \
    Database/database.h \
    Database/entity.h \
    Database/entitymanager.h

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

