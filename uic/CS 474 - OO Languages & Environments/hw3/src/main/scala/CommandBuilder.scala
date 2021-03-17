/********************************************************************************************************************

    CommandBuilder.scala: My implementation utilizes Phantom Types - where manifestations of abstract types are
    never instantiated and have no effect on runtime. This means that they can be erased from the resulting
    code by the compiler once it has shown the constraints hold.

 *******************************************************************************************************************/



import CommandBuilder.{GetItem, GetProcess, GetService, TestConnection, TestPath}
import sys.process._

/********************************************************************************************************************

    Argument class to hold the list of arguments per command

 *******************************************************************************************************************/
case class Argument(args : Seq[String])
{
    // returns the arguments as a list of strings
    def getList() : Seq[String] = args

    def pipe(arg : Argument) = {
        println("\nPiping command: " + this.getList().mkString("") + " with command " + arg.getList().mkString("") + " -->\n" + (this.getList().mkString("") #| arg.getList().mkString("")).!!)
    }
}



/********************************************************************************************************************

     Concrete Builder: Test-Connection

 Functions that are not listed here are because they are either:
    - No longer supported
    - Moved to another command name that is not this one
    - Deprecated
    - Requires Administrative accesses
    - Causes hanging, loops, or those alike
    - etc.

 Otherwise, below are most, if not all, of the additional parameters that are safe to use.

 *******************************************************************************************************************/
class TestConnectionBuilder [customCommand <: CommandBuilder.Command] (args : Seq[String] = Seq())
{
    import CommandBuilder.TestConnection._

    /*
        no longer needed because of redundancies
     */
    @Deprecated
    def testConnection() : TestConnectionBuilder[customCommand] = new TestConnectionBuilder(args :+ "Test-Connection")

    // modifies the amount of pings to the URL
    def addCount(count : String) : TestConnectionBuilder[customCommand with Count] = new TestConnectionBuilder(args :+ (" -Count " + count))

    // modifies the delay between pings
    def addDelay(delay : String) : TestConnectionBuilder[customCommand with Delay] = new TestConnectionBuilder(args :+ (" -Delay " + delay))

    // outputs only the results, whether the test is successful or not
    def addQuiet() : TestConnectionBuilder[customCommand with Quiet] = new TestConnectionBuilder(args :+ " -Quiet")

    // modifies the buffer size when pinging
    def addBufferSize(bufferSize : String) : TestConnectionBuilder[customCommand with BufferSize] = new TestConnectionBuilder(args :+ (" -BufferSize " + bufferSize))

    /*
        no longer needed because constructor now requires a URL
     */
    @Deprecated
    def addURL(url : String) : TestConnectionBuilder[customCommand with URL] = new TestConnectionBuilder(args :+ (" " + url))

    def build(implicit ev : TestConnection <:< testConnection_full) : Argument = Argument(args)
}



/********************************************************************************************************************

     Concrete Builder: Get-Service

  Functions that are not listed here are because they are either:
    - No longer supported
    - Moved to another command name that is not this one
    - Deprecated
    - Requires Administrative accesses
    - Causes hanging, loops, or those alike
    - etc.

 Otherwise, below are most, if not all, of the additional parameters that are safe to use.

 *******************************************************************************************************************/
class GetServiceBuilder [customCommand <: CommandBuilder.Command] (args : Seq[String] = Seq())
{
    import CommandBuilder.GetService._

    /*
        no longer needed because of redundancies
     */
    @Deprecated
    def getService() : GetServiceBuilder[customCommand] = new GetServiceBuilder(args :+ "Get-Service")

    // displays services that matches the input name
    def addDisplayName(name : String) : GetServiceBuilder[customCommand] = new GetServiceBuilder(args :+ (" -DisplayName " + name))

    // allows retrieval of a specific service
    def addName(name : String) : GetServiceBuilder[customCommand] = new GetServiceBuilder(args :+ (" -Name " + name))

    // allows retrieval of specific services matching the include
    def addInclude(include : String) : GetServiceBuilder[customCommand] = new GetServiceBuilder(args :+ (" -Include " + include))

    // excludes a set of services given a string
    def addExclude(exclude: String) : GetServiceBuilder[customCommand] = new GetServiceBuilder(args :+ (" -Exclude " + exclude))

    // displays the services that are dependent on said service
    def addDependentServices(service : String) : GetServiceBuilder[customCommand] = new GetServiceBuilder(args :+ (" -DependentServices " + service))

    // displays the services that this service requires
    def addRequiredServices(service : String) : GetServiceBuilder[customCommand] = new GetServiceBuilder(args :+ (" -RequiredServices " + service))

    // build the command
    def build(implicit ev : GetService <:< getService_full) : Argument = Argument(args)
}



/********************************************************************************************************************

     Concrete Builder: Get-Process

  Functions that are not listed here are because they are either:
    - No longer supported
    - Moved to another command name that is not this one
    - Deprecated
    - Requires Administrative accesses
    - Causes hanging, loops, or those alike
    - etc.

 Otherwise, below are most, if not all, of the additional parameters that are safe to use.

 *******************************************************************************************************************/
class GetProcessBuilder [customCommand <: CommandBuilder.Command] (args : Seq[String] = Seq())
{
    import CommandBuilder.GetProcess._

    /*
        no longer needed because of redundancies
     */
    @Deprecated
    def getProcess() : GetProcessBuilder[customCommand] = new GetProcessBuilder(args :+ "Get-Process")

    // displays file version info of a given file
    def addFileVersionInfo(file : String) : GetProcessBuilder[customCommand] = new GetProcessBuilder(args :+ (" -FileVersionInfo " + file))


    // targets a specific process id
    def addId(id : String) : GetProcessBuilder[customCommand] = new GetProcessBuilder(args :+ (" -Id " + id))

    // retrieves processes included by the user
    def addIncludeUserName (username : String) : GetProcessBuilder[customCommand] = new GetProcessBuilder(args :+ (" -IncludeUserName " + username))

    // specify a module
    def addModule (module : String) : GetProcessBuilder[customCommand] = new GetProcessBuilder(args :+ (" -Module "  + module))

    // specify a process name
    def addName (name : String) : GetProcessBuilder[customCommand] = new GetProcessBuilder(args :+ (" -Name " + name))

    // build the command
    def build(implicit ev : GetProcess <:< getProcess_full): Argument = Argument(args)
}



/********************************************************************************************************************

     Concrete Builder: Test-Path

  Functions that are not listed here are because they are either:
    - No longer supported
    - Moved to another command name that is not this one
    - Deprecated
    - Requires Administrative accesses
    - Causes hanging, loops, or those alike
    - etc.

 Otherwise, below are most, if not all, of the additional parameters that are safe to use.

 *******************************************************************************************************************/
class TestPathBuilder [customCommand <: CommandBuilder.Command] (args : Seq[String] = Seq())
{
    import CommandBuilder.TestPath._

    /*
        no longer needed because of redundancies
     */
    @Deprecated
    def testPath() : TestPathBuilder[customCommand] = new TestPathBuilder(args :+ "Test-Path")

    // exclude from the output a given input
    def addExclude (exclude : String) : TestPathBuilder[customCommand] = new TestPathBuilder(args :+ (" -Exclude " + exclude))

    // filters out whatever the user does and does not want
    def addFilter (filter : String) : TestPathBuilder[customCommand] = new TestPathBuilder(args :+ (" -Filter " + filter))

    // includes the string the user is looking for
    def addInclude (include : String) : TestPathBuilder[customCommand] = new TestPathBuilder(args :+ (" -Include " + include))

    // checks if the path exists
    def addIsValid (path : String) : TestPathBuilder[customCommand] = new TestPathBuilder(args :+ (" -Path " + path))

    // allows specification of a literal path
    def addLiteralPath (path : String) : TestPathBuilder[customCommand] = new TestPathBuilder(args :+ (" -LiteralPath " + path))

    // check for files newer than a certain date
    def addNewerThan (date : String) : TestPathBuilder[customCommand] = new TestPathBuilder(args :+ (" -NewerThan " + date))

    // check for files older than a certain date
    def addOlderThan (date : String) : TestPathBuilder[customCommand] = new TestPathBuilder(args :+ (" -OlderThan " + date))

    /*
        no longer needed because constructor now requires a path
     */
    @Deprecated
    def addPath (path : String) : TestPathBuilder[customCommand] = new TestPathBuilder(args :+  (" -Path " + path))

    // build the command
    def build(implicit ev : TestPath <:< testPath_full): Argument = Argument(args)
}



/********************************************************************************************************************

     Concrete Builder: Get-Item

  Functions that are not listed here are because they are either:
    - No longer supported
    - Moved to another command name that is not this one
    - Deprecated
    - Requires Administrative accesses
    - Causes hanging, loops, or those alike
    - etc.

 Otherwise, below are most, if not all, of the additional parameters that are safe to use.

 *******************************************************************************************************************/
class GetItemBuilder [customCommand <: CommandBuilder.Command] (args : Seq[String] = Seq())
{
    import CommandBuilder.GetItem._

    /*
        no longer needed because of redundancies
     */
    @deprecated
    def getItem (item : String) : GetItemBuilder[customCommand] = new GetItemBuilder(args :+ ("Get-Item " + item))

    // exclude certain items from the output
    def addExclude (exclude : String) : GetItemBuilder[customCommand] = new GetItemBuilder(args :+ (" -Exclude " + exclude))

    // filters out what the user does and does not want in the output
    def addFilter (filter : String) : GetItemBuilder[customCommand] = new GetItemBuilder(args :+ (" -Filter " + filter))

    // gets items that cannot be accessed such as hidden files
    def addForce () : GetItemBuilder[customCommand] = new GetItemBuilder(args :+ " -Force ")

    // include a certain set of items
    def addInclude (include : String) : GetItemBuilder[customCommand] = new GetItemBuilder(args :+ (" -Include " + include))

    // specify a path
    def addPath (path : String) : GetItemBuilder[customCommand] = new GetItemBuilder(args :+ (" -Path " + path))

    // gets the specified alternate NTFS file stream from the file
    def addStream (stream : String) : GetItemBuilder[customCommand] = new GetItemBuilder(args :+ (" -Stream " + stream))

    // build the command
    def build(implicit ev : GetItem <:< getItem_full): Argument = Argument(args)
}



/********************************************************************************************************************

     Builder: CommandBuilder, which allows access to build any of the concrete builders above

 *******************************************************************************************************************/
object CommandBuilder
{
    // supported commands set by the command builder
    sealed class Command
    sealed trait TestConnection extends Command
    sealed trait GetService extends Command
    sealed trait GetProcess extends Command
    sealed trait TestPath extends Command
    sealed trait GetItem extends Command

    object TestConnection extends Command
    {
        // refer to the note at the top of the classes for reasons as to why some parameters are missing
        // otherwise, these are optional parameters/traits for the given command
        sealed trait EmptyTestConnection extends TestConnection
        sealed trait Count extends TestConnection
        sealed trait Delay extends TestConnection
        sealed trait Quiet extends TestConnection
        sealed trait BufferSize extends TestConnection
        sealed trait URL extends TestConnection

        // minimum requirements
        type testConnection_full = EmptyTestConnection with URL

        // apply functions that also provides a constructor-like functionality
        def apply[T <: TestConnection](args : Seq[String], url : String) : TestConnectionBuilder[T] = new TestConnectionBuilder[T](args :+ "powershell.exe /c " :+ ("Test-Connection " + url))

        def apply(url : String): TestConnectionBuilder[TestConnection.EmptyTestConnection] = apply[TestConnection.EmptyTestConnection](Seq(), url)
    }



    object GetService extends Command
    {
        // refer to the note at the top of the classes for reasons as to why some parameters are missing
        // otherwise, these are optional parameters/traits for the given command
        sealed trait EmptyGetService extends GetService
        sealed trait DisplayName extends GetService
        sealed trait Name extends GetService
        sealed trait Include extends GetService
        sealed trait Exclude extends GetService
        sealed trait DependentServices extends GetService
        sealed trait RequiredServices extends GetService

        // minimum requirements
        type getService_full = EmptyGetService with Name

        // apply functions that also provides a constructor-like functionality
        def apply[T <: GetService](args : Seq[String]) : GetServiceBuilder[T] = new GetServiceBuilder[T](args :+ "powershell.exe /c " :+ "Get-Service")

        def apply(): GetServiceBuilder[GetService.EmptyGetService] = apply[GetService.EmptyGetService](Seq())
    }



    object GetProcess extends Command
    {
        // refer to the note at the top of the classes for reasons as to why some parameters are missing
        // otherwise, these are optional parameters/traits for the given command
        sealed trait EmptyGetProcess extends GetProcess
        sealed trait FileVersionInfo extends GetProcess
        sealed trait Id extends GetProcess
        sealed trait IncludeUserName extends GetProcess
        sealed trait Module extends GetProcess
        sealed trait Name extends GetProcess

        // minimum requirements
        type getProcess_full = EmptyGetProcess with Name

        // apply functions that also provides a constructor-like functionality
        def apply[T <: GetProcess](args : Seq[String]) : GetProcessBuilder[T] = new GetProcessBuilder[T](args :+ "powershell.exe /c " :+ "Get-Process")

        def apply() : GetProcessBuilder[GetProcess.EmptyGetProcess] = apply[GetProcess.EmptyGetProcess](Seq())
    }



    object TestPath extends Command
    {
        // refer to the note at the top of the classes for reasons as to why some parameters are missing
        // otherwise, these are optional parameters/traits for the given command
        sealed trait EmptyTestPath extends TestPath
        sealed trait Exclude extends TestPath
        sealed trait Filter extends TestPath
        sealed trait Include extends TestPath
        sealed trait IsValid extends TestPath
        sealed trait LiteralPath extends TestPath
        sealed trait NewerThan extends TestPath
        sealed trait OlderThan extends TestPath
        sealed trait Path extends TestPath

        // minimum requirements
        type testPath_full = EmptyTestPath with Path

        // apply functions that also provides a constructor-like functionality
        def apply[T <: TestPath](args : Seq[String], path : String) : TestPathBuilder[T] = new TestPathBuilder[T](args :+ "powershell.exe /c " :+ ("Test-Path " + path))

        def apply(path : String) : TestPathBuilder[TestPath.EmptyTestPath] = apply[TestPath.EmptyTestPath](Seq(), path)
    }



    object GetItem extends Command
    {
        // refer to the note at the top of the classes for reasons as to why some parameters are missing
        // otherwise, these are optional parameters/traits for the given command
        sealed trait EmptyGetItem extends GetItem
        sealed trait Exclude extends GetItem
        sealed trait Filter extends GetItem
        sealed trait Force extends GetItem // no params
        sealed trait Include extends GetItem
        sealed trait Path extends GetItem
        sealed trait Stream extends GetItem

        // minimum requirements
        type getItem_full = EmptyGetItem

        // apply functions that also provides a constructor-like functionality
        def apply[T <: GetItem](args : Seq[String], item : String) : GetItemBuilder[T] = new GetItemBuilder[T](args :+ "powershell.exe /c " :+ ("Get-Item " + item))

        def apply(item : String) : GetItemBuilder[GetItem.EmptyGetItem] = apply[GetItem.EmptyGetItem](Seq(), item)
    }
}
