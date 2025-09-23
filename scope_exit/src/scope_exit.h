#pragma once

#define SCOPE_EXIT_LINENAME_CAT(name, line) name##line
#define SCOPE_EXIT_LINENAME(name, line) SCOPE_EXIT_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(...) \
    lite::scope_exit SCOPE_EXIT_LINENAME(scope_exit, __LINE__)(lite::make_callback(##__VA_ARGS__))
