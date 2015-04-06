# Using Netsuki #

The **netsuki** download package includes a test app that demonstrates how to use the library. This app creates a function library and registers it with the Lua engine, then runs a script that uses the library.

## Function Libraries ##
Any class that contains `public static` functions can be used as a function library for **netsuki**, with a few exceptions.
  * _Functions cannot be overloaded._
> > Due to the way functions are registered, only the last function found with its name would be available. To prevent this confusion, **netsuki** currently throws a `NotSupportedException` when trying to register more than one function with the same name.
  * _Functions cannot take `out` parameters or optional parameters (including parameter arrays)._
> > They can return only one value to Lua scripts, and must have a fixed number of parameters.
  * _Functions cannot take or return complex types._
> > Besides `String` and `LuaTable`, functions can only take or return primitive types. **netsuki** will not prevent you from registering a library with functions that violate this restriction, but will throw an `ArgumentException` if you try to call one.

So what does a function library look like?  Here's the library used by the test app:
```
      class dotnet
      {
         public static void print(string msg)
         {
            Console.WriteLine(msg);
         }
         public static void msgbox(string msg)
         {
            MessageBox.Show(msg, "Message");
         }
         public static bool query(string msg)
         {
            return MessageBox.Show(msg, "Query", MessageBoxButtons.YesNo) == DialogResult.Yes;
         }
      }
```

Notice that all of its functions are declared `public static`. **netsuki** ignores instance methods, so if you need to, you _can_ declare them. For example, your function library can double as your application's basic data unit, and you can use the static methods to manipulate class instances.

Plus, you can create and import more than one library; each library's functions are stored in a separate table, named after the class that contains them.

## Creating the Engine ##

Before you can use this library, though, you need to create a new instance of `Lua`.  The recommended method is to create a single instance to be used by your entire application, but you can also create one for each application module, or even one for each script that you run.

The test app creates a single instance, and uses it each time the script is run:
```
      Lua lua = new Lua();
```

Wasn't that easy? Lua (and thus the `Lua` class) requires no configuration, so it takes just one line to get it ready to run a script.

## Registering Libraries ##

But, wait-- to do anything _useful_ with this new `Lua`, we need to register our function library.  One more line should do it:
```
      lua.RegisterLibrary(typeof(dotnet));
```

This tells the engine where to find our functions. The `RegisterLibrary` method searches the class for `public static` functions, and adds them to a `table` with the name of the class. For our test library, this means we can access its functions as `dotnet.print`, `dotnet.msgbox`, and `dotnet.query`.

For each function, `RegisterLibrary` also creates a wrapper that handles all the stack operations involved in a call, so you can write your functions just as if you weren't using Lua at all.

## Running a Script ##
Now that all the setup is done, we're ready to run a script. **netsuki** currently supports two ways of doing this:
  * Run scripts stored in a `String` with the `DoString` method.
> > This method also takes an optional parameter to specify the name of the script; the default is "`<immediate>`".
  * Run scripts stored in a file with the `DoFile` method.
> > In this case, the filename is used as the name of the script.

For the test app, the script is written in a `TextBox`, so we'll use the `DoString` method:
```
      lua.DoString(textBox1.Text);
```

If any errors occur in the script, `Lua` will throw a `LuaException`, so you can handle them by adding a `try`/`catch` block around `DoString`.

# Conclusion #
That's all there is to using **netsuki**. With just three lines of code, you can put the power of Lua scripting into your application.