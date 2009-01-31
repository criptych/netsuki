#include "CLR_LuaTypes.h"

#include "CLR_LuaTable.h"

using namespace System::Collections;

namespace netsuki
{
   Object ^LuaTable::default::get(Object ^key)
   {
      _L->Stack->Push(key);
      lua_gettable(_L->State, Index);
      return _L->Stack->Pop();
   }

   void LuaTable::default::set(Object ^key, Object ^value)
   {
      _L->Stack->Push(key);
      _L->Stack->Push(value);
      lua_settable(_L->State, Index);
   }

   IEnumerator ^LuaTable::GetEnumerator()
   {
      return gcnew LuaTableEnumerator(this);
   }

   bool LuaTable::LuaTableEnumerator::MoveNext()
   {
      _Table->_L->Stack->Push(Current);
      
      if (0 != lua_next(_Table->_L->State, _Table->Index))
      {
         _Current = _Table->_L->Stack->Top;
         _Table->_L->Stack->Pop(2);
         return true;
      }
      else
      {
         _Current = nullptr;
         return false;
      }
   }
}
