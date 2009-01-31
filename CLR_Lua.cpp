#include "CLR_LuaTypes.h"

#include "CLR_Lua.h"
#include "CLR_LuaThread.h"
#include "CLR_LuaFunctionWrapper.h"

#include <string.h>

using namespace System::Reflection;
using namespace System::Runtime::InteropServices;

namespace netsuki
{
   LuaType Lua::TypeOf(Object^ o)
   {
      if (o == nullptr)
         return LuaType::Nil;
      else
      {
         Type ^t = o->GetType();

         if (t == Boolean::typeid)
            return LuaType::Boolean;

         if (t == String::typeid || t == Char::typeid)
            return LuaType::String;

         if (t == IntPtr::typeid)
            return LuaType::LightUserData;

         if (t->IsPrimitive || t->IsEnum)
            return LuaType::Number;

         if (t == LuaTable::typeid)
            return LuaType::Table;

         if (t == LuaCallbackFunction::typeid)
            return LuaType::Function;

         if (t == LuaThread::typeid)
            return LuaType::Thread;

         return LuaType::UserData;
      }
   }

   Lua::Lua(): LuaState(luaL_newstate())
   {      
      luaL_openlibs(State);

      _Panic = gcnew LuaCallbackFunction(this, &Lua::OnPanic);

      _ErrorHandler = Stack->Push(_Panic);

      IntPtr p = Marshal::GetFunctionPointerForDelegate(_Panic);
      lua_atpanic(State, (lua_CFunction)p.ToPointer());

      _LibFunctions = gcnew List<LuaFunctionWrapper^>();
   }

   int Lua::OnPanic (lua_State *state)
   {
      Panic(Stack->Top->ToString());
      return 0;
   }

   LuaThread ^Lua::CreateThread()
   {
      return gcnew LuaThread(lua_newthread(_State));
   }

   LuaTable ^Lua::CreateTable()
   {
      lua_createtable(_State, 0, 0);
      return gcnew LuaTable(this, Stack->Count);
   }

   void Lua::RegisterFunction(LuaTable ^tbl, MethodInfo ^method)
   {
      String ^name = method->Name;
      //array<Object^> ^attrs = method->GetCustomAttributes(LuaFunctionAttribute::typeid, false);
      //if (attrs->Length > 0) name = ((LuaFunctionAttribute^)attrs[0])->Name;
      LuaFunctionWrapper ^fw = gcnew LuaFunctionWrapper(method);
      _LibFunctions->Add(fw); tbl[name] = fw->Callback;
   }

   void Lua::RegisterLibrary(Type ^lib)
   {
      if (lib->IsClass)
      {
         LuaTable ^tbl = CreateTable();
         Globals[lib->Name] = tbl;

         array<MethodInfo^> ^methods = lib->GetMethods(
            BindingFlags::Public | BindingFlags::Static | BindingFlags::DeclaredOnly);

         for (int i = 0; i < methods->Length; i++)
         {
            if (tbl[methods[i]->Name] != nullptr)
               throw gcnew NotSupportedException("classes with overloaded methods are not supported");

            RegisterFunction(tbl, methods[i]);
         }
      }
   }

   void Lua::DoString(String ^chunk, String ^name)
   {      
      LoadString(chunk, name);
      DoCall(0, 0);
   }

   void Lua::DoFile(String ^filename)
   {
      LoadFile(filename);
      DoCall(0, 0);
   }
}
