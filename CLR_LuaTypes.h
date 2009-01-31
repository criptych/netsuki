#ifndef CLR_LuaTypes_H
#define CLR_LuaTypes_H

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

using namespace System;

#include "CLR_LuaException.h"

namespace netsuki
{
   ref class Lua;
   ref class LuaGC;
   ref class LuaStack;
   ref class LuaState;
   ref class LuaTable;
   ref class LuaThread;

   public delegate int LuaCallbackFunction(lua_State*);

   public delegate void LuaPanicEventHandler(String^);

   public enum class LuaType
   {
      None = LUA_TNONE,
      Nil = LUA_TNIL,
      Boolean = LUA_TBOOLEAN,
      LightUserData = LUA_TLIGHTUSERDATA,
      Number = LUA_TNUMBER,
      String = LUA_TSTRING,
      Table = LUA_TTABLE,
      Function = LUA_TFUNCTION,
      UserData = LUA_TUSERDATA,
      Thread = LUA_TTHREAD,
   };

   public enum class LuaError
   {
      None = 0,
      Yield = LUA_YIELD,
      Runtime = LUA_ERRRUN,	
      Syntax = LUA_ERRSYNTAX,	
      Memory = LUA_ERRMEM,	
      Handler = LUA_ERRERR,
      IO = LUA_ERRFILE,
   };
}

#endif
