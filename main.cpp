#include "Application/TransportEmpire.h"

#include <QEventLoop>

int main(int argc, char* argv[])
{
    app::TransportEmpire application{ argc, argv };
    application.run();
}
