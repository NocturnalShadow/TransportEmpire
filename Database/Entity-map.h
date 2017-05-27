
#ifdef ODB_COMPILER
    namespace db {
        #pragma db object(Entity) polymorphic
        #pragma db member(Entity::id) id auto
    }
#else
#   include "Mapping\Entity-odb.h"
#endif
