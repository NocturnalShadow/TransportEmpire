
#ifdef ODB_COMPILER
    namespace db {
        #pragma db object(Entity) polymorphic optimistic
        #pragma db member(Entity::id) id auto
        #pragma db member(Entity::version) version
    }
#else
#   include "Mapping/Entity-odb.h"
#endif
