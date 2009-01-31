#ifndef CLR_LuaThread_H
#define CLR_LuaThread_H

#include "CLR_LuaTypes.h"

#include "CLR_LuaState.h"

namespace netsuki
{
   public ref class LuaThread sealed : public LuaState
   {
   private:
      bool _IsAlive;

   internal:
      LuaThread(lua_State *state): LuaState(state) { _IsAlive = true; }

   protected:
      bool Resume (int);
      int Yield (int);

   public:
      property bool IsAlive
      {
         bool get() { return _IsAlive; }
      }

      bool Resume (... array<Object^> ^args)
      {
         for each (Object^ o in args)
            Stack->Push(o);
         return Resume(args->Length);
      }

      int Yield (... array<Object^> ^results)
      {
         for each (Object^ o in results)
            Stack->Push(o);
         return Yield(results->Length);
      }
   };
}

#endif
