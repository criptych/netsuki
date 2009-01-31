#include "CLR_LuaTypes.h"

#include "CLR_Lua.h"
#include "CLR_LuaState.h"
#include "CLR_LuaStack.h"

using namespace System::Runtime::InteropServices;

namespace netsuki
{
   int LuaStack::Count::get()
   {
      return lua_gettop(_L->State);
   }

   void LuaStack::Count::set(int index)
   {
      lua_settop(_L->State, index);
   }
   
   Object ^LuaStack::default::get(int index)
   {
      switch ((LuaType)lua_type(_L->State, index))
      {
      default:
         throw gcnew LuaException("index out of range");

      case LuaType::Nil:
         return nullptr;

      case LuaType::Boolean:
         return 0 != lua_toboolean(_L->State, index);

      case LuaType::UserData:
         // TODO: convert back to original userdata type if possible
      case LuaType::LightUserData:
         return gcnew IntPtr(lua_touserdata(_L->State, index));

      case LuaType::Number:
         return lua_tonumber(_L->State, index);
         
      case LuaType::String: 
         {
            size_t len;
            const char *s = lua_tolstring(_L->State, index, &len);
            return gcnew String(s, 0, len, Text::Encoding::UTF8);
         }
      
      case LuaType::Table:
         return gcnew LuaTable(_L, index);
      
      case LuaType::Function:
         {
            void *f = lua_tocfunction(_L->State, index);
            if (f)
               return Marshal::GetDelegateForFunctionPointer(IntPtr(f), LuaCallbackFunction::typeid);
            else
               return nullptr;
         }
      
      case LuaType::Thread:
         return gcnew LuaThread(lua_tothread(_L->State, index));
      }
   }           

   int LuaStack::Push(Object ^o)
   {
      if (o == nullptr)
         lua_pushnil(_L->State);
      else
      {
         switch (Lua::TypeOf(o))
         {
         case LuaType::Boolean:
            lua_pushboolean(_L->State, (bool)o);
            break;

         case LuaType::LightUserData:
            lua_pushlightuserdata(_L->State, ((IntPtr)o).ToPointer());
            break;

         case LuaType::Number:
            lua_pushnumber(_L->State, Convert::ToDouble(o));
            break;

         case LuaType::String:
            {
               IntPtr p = Marshal::StringToHGlobalAnsi(Convert::ToString(o));
               lua_pushstring(_L->State, (const char*)(p.ToPointer()));
               Marshal::FreeHGlobal(p);
            }
            break;

         case LuaType::Table:
            lua_pushvalue(_L->State, ((LuaTable^)o)->Index);
            break;

         case LuaType::Function:
            {
               IntPtr p = Marshal::GetFunctionPointerForDelegate((LuaCallbackFunction^)o);
               lua_pushcclosure(_L->State, (lua_CFunction)(p.ToPointer()), 0);
            }
            break;

         case LuaType::UserData:
            throw gcnew ArgumentException("stack pushed unsupported data type");
            break;

         case LuaType::Thread:
            break;

         }
      }

      return Count;
   }

   Object ^LuaStack::Pop()
   {
      Object ^r = this[-1];
      Pop(1);
      return r;
   }

   void LuaStack::Insert(int index)
   {
      lua_insert(_L->State, index);
   }

   void LuaStack::Remove(int index)
   {
      lua_remove(_L->State, index);
   }

   void LuaStack::Replace(int index)
   {
      lua_replace(_L->State, index);
   }

   bool LuaStack::Grow(int size)
   {
      return 0 != lua_checkstack (_L->State, size);
   }
}
