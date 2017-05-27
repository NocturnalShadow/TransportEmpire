#include "EntityManager.h"

namespace db {

EntityManager::EntityManager(database* _db)
    : db{ _db }
{
}

// >=========================< Public >=========================<

void EntityManager::abort()
{
    if(transaction::has_current()) {
        transaction::reset_current();
    }
}

void EntityManager::begin()
{
    abort();
    transaction(db->begin());
}

void EntityManager::end() {
    if(transaction::has_current()) {
        transaction::current().commit();
    }
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
        db->persist(*entity);
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
}

// >=========================< Slots >=========================<

void EntityManager::onUpdateRequested()
{
    Entity* entity = qobject_cast<Entity*>(sender());
    transactive([&] () { db->update(*entity); });
}

void EntityManager::onEraseRequested()
{
    Entity* entity = qobject_cast<Entity*>(sender());
    transactive([&] () { db->erase(*entity); });
}

} // namespace db
