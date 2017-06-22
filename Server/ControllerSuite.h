#pragma once

#include "Server/Controller.h"

#include <QList>
#include <QObject>

namespace db {
    class IDatabase;
}

namespace srv {

class ControllerSuite : public QObject
{
private:
    QList<IController*> suite;
    db::IDatabase* database;

public:
    ControllerSuite(db::IDatabase* _database)
        : database{ _database }
    {
    }

public:
    template<class Controller>
    void add()
    {
        suite.append(new Controller{ database });
    }

    const QList<IController*> controllers() const
    {
        return suite;
    }
};

} // namespace srv
