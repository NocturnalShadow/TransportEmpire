#pragma once

#include <QObject>

namespace db {

class IEntity : public QObject
{
    Q_OBJECT
public:
    IEntity() = default;
    virtual ~IEntity() = default;

public:
    void update()   { emit updateRequested(); }
    void erase()    { emit eraseRequested();  }

signals:
    void updateRequested();
    void eraseRequested();
};

// TOBE moved to a separate header
#ifdef ODB_COMPILER

#   include <odb/core.hxx>

#   pragma db object(IEntity) abstract

#endif

} // namespace db
