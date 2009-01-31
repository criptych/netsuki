#ifndef CLR_LuaGC_H
#define CLR_LuaGC_H

#include "CLR_LuaTypes.h"

#include "CLR_LuaState.h"

namespace netsuki
{
   public ref class LuaGC sealed
   {
   private:
      LuaState ^_L;

      int _Pause, _StepMul;

   internal:
      LuaGC(LuaState^);

   public:
      property int Pause
      {
         int get() { return _Pause; }
         void set(int);
      }

      property int StepMul
      {
         int get() { return _StepMul; }
         void set(int);
      }

      property int UsedKBytes
      {
         int get();
      }

      property int UsedBytes
      {
         int get();
      }

      void Collect();
      bool Step(int size);

      void Stop();
      void Restart();
      
      void Start() { Restart(); }

   };
}


#endif
