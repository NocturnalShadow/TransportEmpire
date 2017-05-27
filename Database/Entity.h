#pragma once

#include <QtCore/QObject>

namespace db {

class Entity : public QObject
{
    Q_OBJECT
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
    void setId(unsigned int _id) { id = _id; }
};

} // namespace db

#include "Entity-map.h"


