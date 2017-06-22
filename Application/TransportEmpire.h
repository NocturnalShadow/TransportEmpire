#pragma once

#include "Application/Core.h"
#include "Application/Display.h"

#include <QObject>
#include <QApplication>

namespace app {

class TransportEmpire : public QObject
{
private:
    QApplication    application;
    Core            core;
    Display         display;

public:
    TransportEmpire(int argc, char* argv[]);

private:
    void test(std::string login, std::string password);

public:
    void run();

private slots:
    void onLaunchButtonClicked();
};

}
