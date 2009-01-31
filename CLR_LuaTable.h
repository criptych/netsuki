#ifndef CLR_LuaTable_H
#define CLR_LuaTable_H

#include "CLR_LuaTypes.h"

#include "CLR_LuaState.h"

using namespace System::Collections;

namespace netsuki
{
   public ref class LuaTable sealed : IEnumerable
   {
   private:
      LuaState ^_L;
      int _Index;

   internal:
      LuaTable(LuaState ^l, int index) { _L = l; _Index = index; }
 
      property int Index
      {
         int get() { return _Index; }
      }

      ref class LuaTableEnumerator: IEnumerator
      {
      private:
         Object ^_Current;
         LuaTable ^_Table;

      internal:
         LuaTableEnumerator(LuaTable ^table)
         {
            _Table = table;
            Reset();
         }

      public:
         virtual property Object ^Current{
            Object ^get()
            {
               if (_Current == nullptr)         
                  throw gcnew InvalidOperationException();
               else
                  return _Current; 
            }
         }

         virtual bool MoveNext();

         virtual void Reset()
         {
            _Current = nullptr;
         }
      };

   public:
      property Object ^default[Object^]
      {
         Object ^get(Object^);
         void set(Object^, Object^);
      }

      virtual IEnumerator ^GetEnumerator();
   };
}

#endif
