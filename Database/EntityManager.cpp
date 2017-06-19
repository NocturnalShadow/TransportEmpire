#include "EntityManager.h"

#include <odb/session.hxx>

namespace db {

EntityManager::EntityManager(odb::database* _db)
    : db{ _db }, session{ false }
{
}

// >=========================< Public >=========================<

void EntityManager::startSession()
{
    odb::session::current(session);
}

void EntityManager::persist(Entity& entity)
{
    transactive([&] () {
        db->persist(entity);
        track(&entity);
    });
}

void EntityManager::persist(QSharedPointer<Entity> entity)
{
    transactive([&] () {
        db->persist(entity);
        track(entity.data());
    });
}

// >=========================< Private >=========================<

void EntityManager::track(Entity* entity)
{
    connect(entity, &Entity::updateRequested,
            this, &EntityManager::onUpdateRequested,
            Qt::DirectConnection);
    connect(entity, &Entity::eraseRequested,
            this, &EntityManager::onEraseRequested,
            Qt::DirectConnection);
    connect(entity, &Entity::reloadRequested,
            this, &EntityManager::onReloadRequested,
            Qt::DirectConnection);
}

// >=========================< Slots >=========================<

void EntityManager::onUpdateRequested()
{
    Entity* entity = qobject_cast<Entity*>(sender());
    transactive([&] () { db->update(*entity); });
    emit entityUpdated(entity);
}

void EntityManager::onReloadRequested()
{
    Entity* entity = qobject_cast<Entity*>(sender());
    transactive([&] () { db->reload(*entity); });
}

void EntityManager::onEraseRequested()
{
    Entity* entity = qobject_cast<Entity*>(sender());
    transactive([&] () { db->erase(*entity); });
}

} // namespace db
