#pragma once

#include <odb/database.hxx>
#include <odb/mssql/database.hxx>

#include <QObject>
#include <QSharedPointer>

#include "entity.h"
#include "entity-odb.hxx"

namespace db
{
using odb::database;
using odb::core::transaction;

class EntityManager : public QObject
{
    Q_OBJECT
private:
    database* db = nullptr;

public:
    EntityManager(database* _db);
    virtual ~EntityManager() = default;

public:
    void abort();
    void begin();
    void end();

private slots:
    void onUpdateRequested();
    void onEraseRequested();

public:
    template<class T>
    void persist(IEntity& entity)
    {
        transactive([&] () {
            db->persist(entity);
            attach(&entity);
        });
    }
    template<class T>
    void persist(QSharedPointer<IEntity> entity)
    {
        transactive([&] () {
            db->persist(*entity);
            attach(entity.get());
        });
    }
    template<class T, typename K>
    QSharedPointer<T> load(K id)
    {
        QSharedPointer<T> result = nullptr;
        transactive([&] () {
            result = db->load<T>(id);
        });
        return result;
    }

private:    
    template<typename Action>
    void transactive(Action action)
    {
        if(transaction::has_current()) {
            action();
        } else {
            transaction(db->begin());
            action();
            transaction::current().commit();
        }
    }
    void attach(IEntity* entity);
};

}   // namespace db

