
#ifdef ODB_COMPILER
    namespace db {
        #pragma db object(IEntity) polymorphic
        #pragma db member(IEntity::id) id auto
    }
#else
#   include "Mapping\Entity-odb.h"
#endif
