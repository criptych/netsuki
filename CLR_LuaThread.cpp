#include "CLR_LuaTypes.h"

#include "CLR_LuaThread.h"

namespace netsuki
{
   bool LuaThread::Resume(int nargs)
   {
      return _IsAlive = (CheckError((LuaError)lua_resume(State, nargs)) == LuaError::Yield);
   }

   int LuaThread::Yield(int nresults)
   {
      return lua_yield(State, nresults);
   }
}
