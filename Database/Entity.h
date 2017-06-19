#pragma once

#include "Database/Mapping.h"

#include <QtCore/QObject>

namespace db {

class Entity : public QObject
{
    Q_OBJECT
    PERSISTENT
private:
    unsigned int id;
    unsigned int version;

public:
    Entity() = default;
    virtual ~Entity() = default;

public:
    void update()   { emit updateRequested();   }
    void erase()    { emit eraseRequested();    }
    void reload()   { emit reloadRequested();      }

signals:
    void updateRequested();
    void eraseRequested();
    void reloadRequested();

public:
    unsigned int getId() const { return id; }
};

} // namespace db

#include "Entity-map.h"


