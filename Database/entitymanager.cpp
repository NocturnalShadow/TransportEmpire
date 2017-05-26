#include "entitymanager.h"

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

// >=========================< Private >=========================<

void EntityManager::attach(IEntity* entity)
{
    connect(entity, &IEntity::updateRequested,
            this, &EntityManager::onUpdateRequested,
            Qt::DirectConnection);
    connect(entity, &IEntity::eraseRequested,
            this, &EntityManager::onEraseRequested,
            Qt::DirectConnection);
}

} // namespace db
