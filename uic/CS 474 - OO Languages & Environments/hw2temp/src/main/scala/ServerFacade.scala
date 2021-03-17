/*

  https://www.javacodegeeks.com/2015/09/facade-design-pattern.html

 */


trait ServerScheduler
{
  def startBooting (): Unit =
  {
    println("Starting to boot the servers...")
    Thread.sleep(2500)
    readSystemConfigFile()
    init()
    initContex()
    initListeners()
    createSysObj()
    Thread.sleep(2500)
    println("...done\n")
  }

  def readSystemConfigFile (): Unit =
  {
    print("Reading configuration files...")
    Thread.sleep(2500)
    print("done.\n")
  }
  def init (): Unit =
  {
    print("Initializing values...")
    Thread.sleep(2500)
    print("done.\n")
  }

  def initContex (): Unit =
  {
    print("Initializing contexts...")
    Thread.sleep(2500)
    print("done.\n")
  }

  def initListeners (): Unit =
  {
    print("Initializing listeners...")
    Thread.sleep(2500)
    print("done.\n")
  }

  def createSysObj (): Unit =
  {
    print("Creating system objects...")
    Thread.sleep(2500)
    print("done.\n")
  }

  def releaseProcesses () {}
  def destroy () {}
  def destroySysObj () {}
  def destroyListeners () {}
  def destroyContext () {}
  def shutdown () {}
}

class ServerFacade extends ServerScheduler
{
  //val serverScheduler = new ServerScheduler

  def start (): Boolean =
  {
    startBooting()
    true
  }

  def stop () : Boolean =
    {
      shutdown()
      true
    }
}