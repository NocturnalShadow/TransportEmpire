#pragma once

#include "Server/Controller.h"

#include <QList>
#include <QObject>

namespace db {
    class Database;
}

namespace srv {

class ControllerSuite : public QObject
{
private:
    QList<IController*> suite;
    db::Database* database;

public:
    ControllerSuite(db::Database* _database)
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
