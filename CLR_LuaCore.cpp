#define LUA_CORE
#define LUA_LIB
#define loslib_c

#include "lua.h"

#pragma unmanaged

#include "lapi.c"
#include "lauxlib.c"
#include "lbaselib.c"
#include "lcode.c"
#include "ldblib.c"
#include "ldebug.c"
#include "ldo.c"
#include "ldump.c"
#include "lfunc.c"
#include "lgc.c"
#include "linit.c"
#include "liolib.c"
#include "llex.c"
#include "lmathlib.c"
#include "lmem.c"
#include "loadlib.c"
#include "lobject.c"
#include "lopcodes.c"
#include "loslib.c"
#include "lparser.c"
#include "lstate.c"
#include "lstring.c"
#include "lstrlib.c"
#include "ltable.c"
#include "ltablib.c"
#include "ltm.c"
#include "lundump.c"
#include "lvm.c"
#include "lzio.c"
