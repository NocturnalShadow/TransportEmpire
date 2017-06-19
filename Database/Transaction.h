#pragma once

#include <odb/database.hxx>
#include <odb/transaction.hxx>

#include <QSet>
#include <QObject>

#include "Database/Entity.h"
#include "Database/EntityManager.h"

namespace db {

class Transaction : public QObject
{
private:
    odb::transaction*    transaction;
    QSet<Entity*>        updated;

public:
    Transaction(Transaction&& t) = delete;
    Transaction(const Transaction& t) = delete;

    Transaction& operator=(Transaction&& t) = delete;
    Transaction& operator=(const Transaction& t) = delete;

public:
    Transaction(EntityManager* manager)
        : transaction{ new odb::transaction(manager->db->begin()) }
    {
        connect(manager, &EntityManager::entityUpdated,
                this, &Transaction::onEntityUpdated,
                Qt::DirectConnection);
    }
    ~Transaction()
    {
        delete transaction;
        rollbackUpdated();
    }

public:
    void commit() {
        transaction->commit();
    }
    void rollback()
    {
        transaction->rollback();
        rollbackUpdated();
    }
    void reset(odb::transaction_impl* impl) {
        transaction->reset(impl);
    }
    bool finalized() const {
        return transaction->finalized();
    }

public slots:
    void onEntityUpdated(Entity* entity)
    {
        updated.insert(entity);
        connect(entity, &Entity::destroyed,
                this, &Transaction::onEnityDestroyed,
                Qt::DirectConnection);
    }

    void onEnityDestroyed()
    {
        Entity* entity = qobject_cast<Entity*>(sender());
        updated.remove(entity);
    }

private:
    void rollbackUpdated()
    {
        for(auto entity : updated) {
            entity->reload();
        }
    }

public:
    static bool active() {
        return odb::transaction::has_current();
    }
};

} // namespace db
