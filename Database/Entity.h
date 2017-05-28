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

public:
    Entity() = default;
    virtual ~Entity() = default;

public:
    void update()   { emit updateRequested(); }
    void erase()    { emit eraseRequested();  }

signals:
    void updateRequested();
    void eraseRequested();

public:
    unsigned int getId() const { return id; }
};

} // namespace db

#include "Entity-map.h"


