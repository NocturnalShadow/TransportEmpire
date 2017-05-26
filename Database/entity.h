#pragma once

#include <QtCore/QObject>

namespace db {

class IEntity : public QObject
{
    Q_OBJECT
private:
    unsigned int id;

public:
    IEntity() = default;
    virtual ~IEntity() = default;

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



#ifdef ODB_COMPILER

#pragma db object(IEntity) polymorphic
#pragma db member(IEntity::id) id auto

#endif


} // namespace db
