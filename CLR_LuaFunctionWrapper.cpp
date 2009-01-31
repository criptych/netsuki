#include "CLR_LuaTypes.h"

#include "CLR_LuaState.h"
#include "CLR_LuaFunctionWrapper.h"

using namespace System::Reflection;

namespace netsuki
{
   LuaFunctionWrapper::LuaFunctionWrapper(MethodInfo ^method)
   {
      _Method = method;
      _Callback = gcnew LuaCallbackFunction (this, &LuaFunctionWrapper::Call);
      _NumArgs = 0;
      _NumResults = method->ReturnType == Void::typeid ? 0 : 1;

      for each (ParameterInfo ^p in method->GetParameters())
      {
         if (p->IsOut)
            //_NumResults++;
            throw gcnew NotSupportedException("methods with 'out' parameters are not supported");
         else if (p->IsOptional)
            throw gcnew NotSupportedException("methods with optional parameters are not supported");
         else if (p->GetCustomAttributes(ParamArrayAttribute::typeid, false)->Length > 0)
            throw gcnew NotSupportedException("methods with parameter arrays are not supported");
         else
            _NumArgs++;
      }
   }

   LuaFunctionWrapper::~LuaFunctionWrapper()
   {
   }

   int LuaFunctionWrapper::Call(lua_State *L)
   {
      LuaState ^state = gcnew LuaState(L);

      array<Object^> ^parameters = gcnew array<Object^>(_NumArgs);

      for (int i = 0; i < _NumArgs && i < state->Stack->Count; i++)
         parameters[i] = state->Stack[i + 1];

      Object ^result = Method->Invoke(nullptr, parameters);

      state->Stack->Push(result);

      return _NumResults;
   }
}
