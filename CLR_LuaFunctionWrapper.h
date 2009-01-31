#ifndef CLR_LuaFunctionWrapper_H
#define CLR_LuaFunctionWrapper_H

#include "CLR_LuaTypes.h"

using namespace System::Reflection;

namespace netsuki
{
   ref class LuaFunctionWrapper
   {
   private:
      MethodInfo ^_Method;
      LuaCallbackFunction ^_Callback;
      int _NumArgs, _NumResults;

      int Call (lua_State*);

   public:
      LuaFunctionWrapper(MethodInfo^);
      ~LuaFunctionWrapper();

      property MethodInfo ^Method
      {
         MethodInfo ^get() { return _Method; }
      }

      property LuaCallbackFunction ^Callback
      {
         LuaCallbackFunction ^get() { return _Callback; }
      }

      operator LuaCallbackFunction^ ()
      {
         return Callback;
      }
   };
}

#endif
