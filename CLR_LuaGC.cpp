#include "CLR_LuaTypes.h"

#include "CLR_LuaGC.h"

namespace netsuki
{
   LuaGC::LuaGC(LuaState ^l)
   {
      _L = l;

      Pause = lua_gc(_L->State, LUA_GCSETPAUSE, 200);
      StepMul = lua_gc(_L->State, LUA_GCSETSTEPMUL, 200);
   }

   void LuaGC::Pause::set(int value)
   {
      lua_gc(_L->State, LUA_GCSETPAUSE, _Pause = value);
   }

   void LuaGC::StepMul::set(int value)
   {
      lua_gc(_L->State, LUA_GCSETSTEPMUL, _StepMul = value);
   }

   int LuaGC::UsedKBytes::get()
   {
      return lua_gc(_L->State, LUA_GCCOUNT, 0);
   }

   int LuaGC::UsedBytes::get()
   {
      return UsedKBytes * 1024 + lua_gc(_L->State, LUA_GCCOUNTB, 0);
   }

   void LuaGC::Collect()
   {
      lua_gc(_L->State, LUA_GCCOLLECT, 0);
   }

   bool LuaGC::Step(int size)
   {
      return 0 != lua_gc(_L->State, LUA_GCSTEP, size);
   }

   void LuaGC::Stop()
   {
      lua_gc(_L->State, LUA_GCSTOP, 0);
   }

   void LuaGC::Restart()
   {
      lua_gc(_L->State, LUA_GCRESTART, 0);
   }
}
