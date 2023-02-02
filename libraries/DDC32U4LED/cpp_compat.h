#ifndef __INC_CPP_COMPAT_H
#define __INC_CPP_COMPAT_H

#include "DDC32U4LED.h"

#if __cplusplus <= 199711L

#define static_assert(expression, message)
#define constexpr const

#else

// things that we can turn on if we're in a C++11 environment
#endif

#endif
