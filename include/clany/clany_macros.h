#ifndef CLANY_MACROS_H
#define CLANY_MACROS_H

#define _CLANY_BEGIN	namespace clany {
#define _CLANY_END		}

#if defined CLANYAPI_EXPORTS
#  define CLANY_EXPORTS __declspec(dllexport)
#else
#  define CLANY_EXPORTS
#endif

#define DBGVAR( os, var ) \
  (os) << "DBG: " << __FILE__ << "(" << __LINE__ << ") "\
       << #var << " = [" << (var) << "]" << std::endl

#define DBGMSG( os, msg ) \
  (os) << "DBG: " << __FILE__ << "(" << __LINE__ << ") " \
       << msg << std::endl

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

_CLANY_BEGIN
using namespace std;
_CLANY_END

#endif // CLANY_MACROS_H
