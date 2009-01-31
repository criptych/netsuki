#ifndef CLR_LuaStack_H
#define CLR_LuaStack_H

#include "CLR_LuaTypes.h"

#include "CLR_LuaState.h"

namespace netsuki
{
   public ref class LuaStack sealed
   {
   private:
      LuaState ^_L;

   internal:
      LuaStack(LuaState ^l) { _L = l; }

   public:
      property int Count
      {
         int get();
         void set(int);
      }

      property Object ^default[int]
      {
         Object ^get(int);
      }

      property Object ^Top
      {
         Object ^get() { return this[Count]; }
      }

      int Push(Object^);

      void Pop(int n) { Count -= n; }
      Object ^Pop();

      void Insert(int);
      void Remove(int);
      void Replace(int);

      bool Grow(int);
   };
}

#endif
