#pragma once

#include <string>
#include "shared/include/entityType.h"

namespace rtype::comp {

    struct NetSync {
        EntityType type;
    };

    struct NetworkIdentity {
        std::string address;
        unsigned short port;
    };

}
