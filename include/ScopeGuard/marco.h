#pragma once
#ifndef MARCO_H
#define MARCO_H

#ifndef UNIQUE
#if defined(__COUNTER__) && (__COUNTER__ + 1 == __COUNTER__ + 0)
#define UNIQUE __COUNTER__
#else
#define UNIQUE __LINE__
#endif // __COUNTER__
#endif // !UNIQUE

#ifndef UNIQUE_NAME_CAT
#define UNIQUE_NAME_CAT(name, unique) name##unique
#endif // !UNIQUE_NAME_CAT

#ifndef UNIQUE_NAME
#define UNIQUE_NAME(name, unique) UNIQUE_NAME_CAT(name, unique)
#endif // !SCOPE_GUARD_UNIQUE_NAME

#endif // !MARCO_H
