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

void EntityManager::persist(IEntity& entity)
{
    transactive([&] () {
        db->persist(entity);
        track(&entity);
    });
}

void EntityManager::persist(QSharedPointer<IEntity> entity)
{
    transactive([&] () {
        db->persist(*entity);
        track(entity.data());
    });
}

// >=========================< Private >=========================<

void EntityManager::track(IEntity* entity)
{
    connect(entity, &IEntity::updateRequested,
            this, &EntityManager::onUpdateRequested,
            Qt::DirectConnection);
    connect(entity, &IEntity::eraseRequested,
            this, &EntityManager::onEraseRequested,
            Qt::DirectConnection);
}

// >=========================< Slots >=========================<

void EntityManager::onUpdateRequested()
{
    IEntity* entity = qobject_cast<IEntity*>(sender());
    transactive([&] () { db->update(*entity); });
}

void EntityManager::onEraseRequested()
{
    IEntity* entity = qobject_cast<IEntity*>(sender());
    transactive([&] () { db->erase(*entity); });
}

} // namespace db
