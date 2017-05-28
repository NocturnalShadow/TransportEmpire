#pragma once

#include <odb/database.hxx>
#include <odb/mssql/database.hxx>

#include <QObject>
#include <QVector>
#include <QScopedPointer>

#include "Database/Pointer.h"
#include "Database/Entity.h"

namespace db
{
using namespace odb;

class EntityManager : public QObject
{
    Q_OBJECT
private:
    database* db = nullptr;
    QScopedPointer<session> se;

public:
    EntityManager(database* _db);
    virtual ~EntityManager() = default;

public:
    void abort();
    void begin();
    void end();

    void persist(Entity& entity);
    void persist(Pointer<Entity> entity);

private:
    void track(Entity* entity);

private slots:
    void onUpdateRequested();
    void onEraseRequested();

public:
    template<class T>
    Pointer<T> load(unsigned int id);

    template<class T>
    QVector<Pointer<T>> load(const query<T>& _query);

    template<class T>
    LazyPointer<T> loadLater(unsigned int id);

    template<class T>
    QVector<LazyPointer<T>> loadLater(const query<T>& _query);

    template<class T>
    void erase(const query<T>& _query);

private:
    template<class Action>
    auto transactive(Action action);
};

}   // namespace db

#include "EntityManager-inl.h"


