# Jon-Michael Hoang's HW3 Submission's README File.

IF YOU CANNOT READ THIS README FILE CLEARLY, PLEASE READ IT IN EITHER NOTEPAD OR VISUAL STUDIO CODE BY TYPING: [ code README.md ] 

## How to install this program:

Simply install it, unzipping if necessary.

## How to run this program:

** THIS APPLICATION ONLY WORKS IF YOU ARE USING A WINDOWS COMPUTER WITH POWERSHELL OTHERWISE THIS PROGRAM WOULDN'T WORK **

If the project is opened in IntelliJ, open up your sbt shell and run it using the command:

sbt run

When the program is running, it will do the commands pre-programmed by me.
The implementation supports these commands that are also supported in Powershell:

- Test-Connection
- Get-Service
- Get-Process
- Test-Path
- Get-Item

## Pros:

- Runs on the sbt shell / terminal application - which makes it easy to use
- Supports 5 commands - to allow reasonable functionality as per write-up
- Has 2 input piping - to allow the output of one command as the input of another
- Programmer friendly - no need to type extraneous code
- Uses phantom types - where manifestations of abstract types are
    never instantiated and have no effect on runtime. This means that they can be erased from the resulting
    code by the compiler once it has shown the constraints hold.

## Cons:

- Runs on the sbt shell / terminal application - pretty boring to use
- Supports only 5 commands - not much room to do stuff like a real Powershell
- Does not provide multiple piping - only 2 input piping

## Log Messages

Log messages are provided to easily trace the application while it is running and to be easily
able to debug when problems arise.

## How to use the implementation

To use the implementation and its commands, simply type CommandBuilder._ , where 
(I hope you are using this with IntelliSense in this day and age) where it will allow
you to access the five commands:

- Test-Connection
- Get-Service
- Get-Process
- Test-Path
- Get-Item

Some of these may require inputs for their constructors, but to add more functionality to the
commands, simple type [ . ] and allow IntelliSense to produce a list of available commands at
your disposal.

Functions that are not listed here are because they are either:
    - No longer supported
    - Moved to another command name that is not this one
    - Deprecated
    - Requires Administrative accesses
    - Causes hanging, loops, or those alike
    - etc.

 Otherwise, below are most, if not all, of the additional parameters that are safe to use.

 After you are done, simply end it with [ .build(null).getList().mkString("").!! ] and println it to view the results. What the line does is that it builds the arguments using phantom types, extracts the elements as a list, extracts the elements in the list as a single String, and executes it using the built in scala sys.process._ shared library with .!!.

 An example of this would be:

 val testConnectionBuilder_result = CommandBuilder.TestConnection("danbooru.donmai.us")
                    .addCount("1")
                    .addDelay("1")
                    .addBufferSize("256")
                    .build(null)

val TC_exeResult = testConnectionBuilder_result.getList().mkString("").!!

println(TC_exeResult)

Where the product is 1 ping of 256 bytes @ 1 second to the site: danbooru.donmai.us - to which it is displayed as a list in the sbt shell console window:

Source        Destination     IPV4Address      IPV6Address                              Bytes    Time(ms)
------        -----------     -----------      -----------                              -----    --------
DESKTOP-8K... danbooru.don... 104.20.135.45    2606:4700:10::6814:862d                  256      18

Another example: 

val getProcessBuilder_result = CommandBuilder.GetProcess()
            .addId("$PID")
            .build(null)

val GP_exeResult = getProcessBuilder_result.getList().mkString("").!!

println(GP_exeResult)

Which retrieves a table of processes with id $PID:

Handles  NPM(K)    PM(K)      WS(K)     CPU(s)     Id  SI ProcessName
-------  ------    -----      -----     ------     --  -- -----------
    527      27    54792      56848       0.36  14596  10 powershell

## Piping

Piping is where you take the output of one command as input for the other.

To pipe, simply get the Argument build and utilize the .pipe(arg : Argument) function.
The piping in the application can only support 2 inputs, so multiple inputs are
impossible.

An example of piping can be found in the code such as:

getItem_result.pipe(CommandBuilder.GetService().build(null))


CommandBuilder.GetService().build(null).pipe(CommandBuilder.GetProcess().build(null))


testPath_result.pipe(CommandBuilder.TestConnection("my.uic.edu").build(null))


CommandBuilder.TestConnection("danbooru.donmai.us").addQuiet().build(null).pipe(getProcessBuilder_result)


testPath_result.pipe(CommandBuilder.GetProcess().build(null))

There are multiple ways to pipe with this implementation, but it is limited to 2 arguments.

## Runtime

The application may take awhile to complete - especially when it has to ping servers online

## Memory

Not that much important since it does not use heavy processes/processing or big data.