#pragma once

#include <odb/database.hxx>
#include <odb/mssql/database.hxx>

#include <QObject>
#include <QVector>
#include <QSharedPointer>

#include "Entity.h"

namespace db
{
using namespace odb;

class EntityManager : public QObject
{
    Q_OBJECT
public:
    template<class T>
    using EntityPointer = QSharedPointer<T>;

private:
    database* db = nullptr;

public:
    EntityManager(database* _db);
    virtual ~EntityManager() = default;

public:
    void abort();
    void begin();
    void end();

    void persist(IEntity& entity);
    void persist(EntityPointer<IEntity> entity);

private:
    void track(IEntity* entity);

private slots:
    void onUpdateRequested();
    void onEraseRequested();

public:
    template<class T>
    EntityPointer<T> load(unsigned int id);
    template<class T>
    QVector<EntityPointer<T>> load(const query<T>& _query);
    template<class T>
    void erase(const query<T>& _query);

private:
    template<class Action>
    auto transactive(Action action);
};

}   // namespace db

#include "EntityManager-inl.h"


