#ifndef CLANY_TSTRING_H
#define CLANY_TSTRING_H

#include <string>
#include "clany_macros.h"


_CLANY_BEGIN
#ifdef _UNICODE
using tstring = wstring;
#else
using tstring = string;
#endif
_CLANY_END

#endif // CLANY_TSTRING_H
