#include "CLR_LuaTypes.h"

#include "CLR_LuaState.h"
#include "CLR_LuaStack.h"
#include "CLR_LuaGC.h"
#include "CLR_LuaTable.h"

using namespace System::Runtime::InteropServices;

namespace netsuki
{
   LuaError LuaState::CheckError (LuaError error)
   {
      switch (error)
      {
      case LuaError::None:
      case LuaError::Yield:
         return error;

      case LuaError::Runtime:
         throw gcnew LuaException("runtime error: " + Stack->Top);

      case LuaError::Syntax:
         throw gcnew LuaSyntaxException("syntax error: " + Stack->Top);

      case LuaError::Memory:
         throw gcnew LuaMemoryException("out of memory: " + Stack->Top);

      case LuaError::Handler:
         throw gcnew LuaException("error calling error handler: " + Stack->Top);

      case LuaError::IO:
         throw gcnew LuaException("I/O error: " + Stack->Top);

      default:
         throw gcnew LuaException("unknown error: " + Stack->Top);
      }
   }

   LuaState::LuaState(lua_State *state)
   {
      _State = state;

      _Stack = gcnew LuaStack(this);
      _GC = gcnew LuaGC(this);

      _Environment = gcnew LuaTable(this, LUA_ENVIRONINDEX);
      _Globals = gcnew LuaTable(this, LUA_GLOBALSINDEX);
      _Registry = gcnew LuaTable(this, LUA_REGISTRYINDEX);

   }

   void LuaState::Close()
   {
      if (_State)
         lua_close(_State);
   }

   LuaError LuaState::LoadString(String ^chunk, String ^name)
   {
      IntPtr pChunk = Marshal::StringToHGlobalAnsi(chunk);
      IntPtr pName = Marshal::StringToHGlobalAnsi(name);

      LuaError error = (LuaError)luaL_loadbuffer(State, 
         (const char*)pChunk.ToPointer(), chunk->Length,
         (const char*)pName.ToPointer()
         );

      Marshal::FreeHGlobal(pChunk);
      Marshal::FreeHGlobal(pName);

      return CheckError(error);
   }

   LuaError LuaState::LoadFile(String ^filename)
   {
      IntPtr pFile = Marshal::StringToHGlobalAnsi(filename);

      LuaError error = (LuaError)luaL_loadfile(State, (const char*)pFile.ToPointer());

      Marshal::FreeHGlobal(pFile);

      return CheckError(error);
   }

   LuaError LuaState::DoCall (int nargs, int nresults)
   {
      return CheckError((LuaError)lua_pcall(State, nargs, nresults, _ErrorHandler));
   }

   LuaError LuaState::Call (String ^name, array<Object^> ^args)
   {
      Stack->Push(name);
      for each (Object ^o in args)
         Stack->Push(o);

      return DoCall(args->Length, 0);
   }
};
