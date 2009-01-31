#ifndef CLR_Lua_H
#define CLR_Lua_H

#include "CLR_LuaTypes.h"

#include "CLR_LuaState.h"
#include "CLR_LuaThread.h"
#include "CLR_LuaFunctionWrapper.h"

using namespace System::Collections::Generic;
using namespace System::Reflection;

namespace netsuki
{
   public ref class Lua sealed : public LuaState
   {
   private:
      static System::Version ^_Version = gcnew System::Version(5, 1, 4);

   public:
      static property System::Version ^Version 
      {
         System::Version ^get() { return _Version; }
      }

      static LuaType TypeOf(Object^);

   protected:
      virtual int OnPanic (lua_State *state);

      List<LuaFunctionWrapper^> ^_LibFunctions;

   public:
      LuaCallbackFunction ^_Panic;

      Lua();

      LuaThread ^CreateThread();
      LuaTable ^CreateTable();

      void RegisterFunction(LuaTable^, MethodInfo^);
      void RegisterFunction(MethodInfo ^method) { RegisterFunction(Globals, method); }
      
      void RegisterLibrary(Type ^lib);

      void RegisterLibrary(Assembly ^assembly)
      {
         for each (Type ^cls in assembly->GetTypes())
            RegisterLibrary(cls);
      }

      void RegisterLibrary(String ^filename)
      {
         RegisterLibrary(Assembly::LoadFrom(filename));
      }

      void DoString(String ^chunk, String ^name);
      
      void DoString(String ^chunk) 
      {
         DoString(chunk, "<immediate>"); 
      }

      void DoFile(String ^filename);
   };
}

#endif
