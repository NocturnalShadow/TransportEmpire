#include "entitymanager.h"

db::EntityManager::EntityManager(odb::database* _db)
    : db{ _db }
{
}

// public

void db::EntityManager::reset()
{
    if(transaction::has_current()) {
        transaction::reset_current();
    }
}

void db::EntityManager::begin()
{
    reset();
    transaction(db->begin());
}

void db::EntityManager::end() {
    if(transaction::has_current()) {
        transaction::current().commit();
    }
}

void db::EntityManager::persist(db::IEntity *entity)
{
    _transactive([&] () { _persist(entity); });
}

// slots

void db::EntityManager::onUpdateRequested()
{
    IEntity* entity = qobject_cast<IEntity*>(sender());
    _transactive([&] () { db->update(entity); });
}

void db::EntityManager::onEraseRequested()
{
    IEntity* entity = qobject_cast<IEntity*>(sender());
    _transactive([&] () { db->erase(entity); });
}

// private

void db::EntityManager::_persist(db::IEntity *entity) {
    db->persist(entity);
    connect(entity, &IEntity::updateRequested,
            this, &EntityManager::onUpdateRequested,
            Qt::DirectConnection);
    connect(entity, &IEntity::eraseRequested,
            this, &EntityManager::onEraseRequested,
            Qt::DirectConnection);
}
