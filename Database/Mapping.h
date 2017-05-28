#pragma once

#include "Pointer.h"

#include <odb/core.hxx>

#define PERSISTENT \
    friend class ::odb::access;

