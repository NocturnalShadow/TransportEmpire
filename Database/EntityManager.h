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

template<typename T>
using Query = odb::query<T>;

class EntityManager : public QObject
{
    Q_OBJECT
private:
    odb::database* db = nullptr;
    odb::session se;

public:
    EntityManager(odb::database* _db);
    virtual ~EntityManager() = default;

public:
    void startSession();

    void abortTransaction();
    void beginTransaction();
    void endTransaction();

    void persist(Entity& entity);
    void persist(Pointer<Entity> entity);

private:
    void track(Entity* entity);

private slots:
    void onUpdateRequested();
    void onReloadRequested();
    void onEraseRequested();

public:
    template<class T>
    Pointer<T> load(unsigned int id);

    template<class T>
    QVector<Pointer<T>> load(const Query<T>& _query);

    template<class T>
    LazyPointer<T> loadLater(unsigned int id);

    template<class T>
    QVector<LazyPointer<T>> loadLater(const Query<T>& _query);

    template<class T>
    void erase(const Query<T>& _query);

private:
    template<class Action>
    auto transactive(Action action);
};

}   // namespace db

#include "EntityManager-inl.h"


