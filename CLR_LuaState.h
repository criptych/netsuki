#ifndef CLR_LuaState_H
#define CLR_LuaState_H

#include "CLR_LuaTypes.h"

#include "CLR_LuaStack.h"
#include "CLR_LuaGC.h"
#include "CLR_LuaTable.h"

namespace netsuki
{
   public ref class LuaState
   {
   protected:
      lua_State *_State;

      LuaStack ^_Stack;
      LuaGC ^_GC;

      LuaTable 
         ^_Environment,
         ^_Globals,
         ^_Registry;

      int _ErrorHandler;

      LuaError CheckError (LuaError error);

      LuaError LoadString(String ^chunk, String ^name);
      LuaError LoadFile(String ^filename);

      LuaError DoCall(int nargs, int nresults);

   internal:
      LuaState(lua_State*);
      ~LuaState() { Close(); }

      property lua_State *State
      {
         lua_State *get() { return _State; }
      }

   public:
      event LuaPanicEventHandler ^Panic;

      void Close();

      LuaError Call (String ^name, array<Object^> ^args);

      property LuaStack ^Stack
      {
         LuaStack ^get() { return _Stack; }
      }

      property LuaGC ^GC
      {
         LuaGC ^get() { return _GC; }
      }

      property LuaTable ^Environment
      {
         LuaTable ^get() { return _Environment; }
      }

      property LuaTable ^Globals
      {
         LuaTable ^get() { return _Globals; }
      }

      property LuaTable ^Registry
      {
         LuaTable ^get() { return _Registry; }
      }
   };
}

#endif
