#ifndef CLR_LuaException_H
#define CLR_LuaException_H

namespace netsuki
{
   public ref class LuaException: public Exception
   {
   public:
      LuaException (): 
         Exception()
      {
      }

      LuaException(String ^message): 
         Exception(message) 
      {
      }

      LuaException(String ^message, Exception ^innerException): 
         Exception(message, innerException) 
      {
      }
   };

   public ref class LuaSyntaxException: public LuaException
   {
   public:
      LuaSyntaxException (): 
         LuaException()
      {
      }

      LuaSyntaxException(String ^message): 
         LuaException(message) 
      {
      }

      LuaSyntaxException(String ^message, Exception ^innerException): 
         LuaException(message, innerException) 
      {
      }
   };

   public ref class LuaMemoryException: public LuaException
   {
   public:
      LuaMemoryException (): 
         LuaException()
      {
      }

      LuaMemoryException(String ^message): 
         LuaException(message) 
      {
      }

      LuaMemoryException(String ^message, Exception ^innerException): 
         LuaException(message, innerException) 
      {
      }
   };
}

#endif
