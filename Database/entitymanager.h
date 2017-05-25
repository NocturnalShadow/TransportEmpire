#pragma once

#include "entity.h"

#include <odb/database.hxx>
#include <odb/mssql/database.hxx>

#include <map>

#include <QObject>

namespace db
{
using namespace odb;

class EntityManager : public QObject
{
    Q_OBJECT
private:
    database* db = nullptr;

public:
    EntityManager(database* _db);
    virtual ~EntityManager() = default;

public:
    void reset();
    void begin();
    void end();

private slots:
    void onUpdateRequested();
    void onEraseRequested();

public:
    void persist(IEntity* entity);
    template<typename T, typename K>
    T* load(K id)
    {
        T* result = nullptr;
        _transactive([&] () { result = db->load<T>(id); });
        return result;
    }

private:
    void _persist(IEntity* entity);
    template<typename Action>
    void _transactive(Action action)
    {
        if(transaction::has_current()) {
            action();
        } else {
            transaction(db->begin());
            action();
            transaction::current().commit();
        }
    }
};

}   // namespace db

