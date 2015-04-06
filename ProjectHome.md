# netsuki: rest easy. #

## Description ##
**netsuki** is an object-oriented interface to Lua for Microsoft.NET 2.0 or higher, ideal for embedding Lua as an extension language in your .NET application.

## Features ##
  * Fully object-oriented access to the Lua API.
  * Easy-to-use function library importing.
  * Builds as a single DLL, including the Lua core.

Using **netsuki**, you can embed Lua in your .NET application with as few as three lines of code: create a new `Lua` instance, register your function library, and run scripts with the `DoString` or `DoFile` methods.  Read more about using **netsuki** [here](UsingNetsuki.md).

## Limitations ##
  * Only certain functionality of the Lua API is accessible through **netsuki**.
  * **netsuki** does not make the calling `Lua` instance directly available to library functions.
  * Library functions must be declared `static`. (Non-`static` functions are ignored.)
  * Library functions cannot take `out` or optional parameters.
  * Library functions cannot be overloaded.
  * Lua's `userdata` type is not supported. The "light" userdata type, however, may be used via .NET's `IntPtr` type.

I'm working on reducing or removing these limitations for future revisions, but keep them in mind when writing function libraries.

## Motivation ##
Several C#.NET projects I am working on needed a way to add custom functionality without rebuilding. I chose the Lua scripting language, and started looking for a library; unfortunately, none of the ones I found met my needs. [dotLua](http://dotlua.berlios.de/) gave mainly low-level access to the API, making it awkward to use with a fully object-oriented system like .NET. (It hasn't been updated in a while, either.) [LuaInterface](http://luainterface.googlecode.com/) had a lot of very useful features - but as a "full CLS consumer," it exposed too much of the underlying system to scripts. [Lua Managed](http://luaforge.net/projects/luamanaged/) involved a total conversion of the Lua source, so it would be difficult to keep updated.

What I wanted instead was a library that provides a high-level, object-oriented view of the Lua API that only exposed functionality necessary to my application, and could easily be integrated with an existing system and built against the latest Lua distribution. Well, if you want something done right... so I wrote one myself, and netsuki was born.


## The Name ##
The name **netsuki** is sort of a multi-layered play on words. Taken as-is, the Japanese word _netsuki_ means "quality of sleep": thus the tagline. The portion _tsuki_ can also mean "moon," corresponding to Lua, the Portugese word for the same. And finally, it can be read "NET suki," in which _suki_ means "fondness" or "affinity." In all its many forms, the name was perfectly suited.