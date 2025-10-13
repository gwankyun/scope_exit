#pragma once
#include "src/unique.h"

#define LOCAL_FUNCTION_BEGIN(_ret) \
    struct UNIQUE_NAME(CB_, UNIQUE_ID) \
    { \
        _ret operator()

#define LOCAL_FUNCTION_END(_name) \
    } \
    _name
