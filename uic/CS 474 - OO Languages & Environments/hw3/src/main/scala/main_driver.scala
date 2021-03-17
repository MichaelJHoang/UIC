import CommandBuilder.{GetService, TestConnection}

import scala.sys.process._
import com.typesafe.config._
import com.typesafe.scalalogging.LazyLogging

import scala.io
import scala.reflect.internal.util.TableDef.Column

object main_driver extends App with LazyLogging
{
    // load the configuration files
    val config:Config = ConfigFactory.load()

    /********************************************************************************************************************

     @info
     System Check

     STOP BEFORE CONTINUING:

     THIS APPLICATION ONLY WORKS IF YOU ARE USING A WINDOWS COMPUTER WITH POWERSHELL OTHERWISE THIS PROGRAM WOULDN'T WORK

     *******************************************************************************************************************/
    // check if the OS the user is running on is a Windows machine because this application only supports Windows Powershell
    logger.info("Checking for the user's OS")
    if(System.getProperty("os.name").contains("Windows") || System.getProperty("os.name").contains("windows"))
    {
        // windows
        logger.info("Windows?: Yes")
        println("The OS you are running this application on: " + System.getProperty("os.name"))
    }
    // exit the application provided the user does not use a Windows machine (e.g. Ubuntu)
    else
    {
        // not windows
        logger.warn("Windows?: No")
        println("Please run this application on a machine with Windows")
        System.exit(-1)
    }



    /********************************************************************************************************************

     Test-Connect

     *******************************************************************************************************************/
    // builder for powershell's Test-Connection command
    // .build returns a Argument(List(...)), but
    // here we simply get the list
    logger.info("Making a TestConnection with the builder...")
    val testConnectionBuilder_result = CommandBuilder.TestConnection("danbooru.donmai.us")
                    .addCount("1")
                    .addDelay("1")
                    .addBufferSize("256")
                    .build(null)

    // with the list, turn it all into a single string
    logger.info("Converting the result from Argument type to a List and then to a String and executing it...")
    val TC_exeResult = testConnectionBuilder_result.getList().mkString("").!!

    // smash things together and execute it
    logger.info("Printing the result")
    println(TC_exeResult)



    /********************************************************************************************************************

     Get-Service

     *******************************************************************************************************************/
    // builder for powershell's Get-Service command
    // .build returns a Argument(List(...)), but
    // here we simply get the list
    logger.info("Making a GetService with the builder...")
    val getServiceBuilder_result = CommandBuilder.GetService()
            .addDisplayName("*nvidia*")
            .build(null)

    // with the list, turn it all into a single string
    logger.info("Converting the result from Argument type to a List and then to a String and executing it...")
    val GS_exeResult = getServiceBuilder_result.getList().mkString("").!!

    // print the result
    logger.info("Printing the result")
    println(GS_exeResult)



    /********************************************************************************************************************

     Get-Process

     *******************************************************************************************************************/
    // builder for powershell's Get-Process command
    // .build returns a Argument(List(...)), but
    // here we simply get the list
    logger.info("Making a GetProcess with the builder...")
    val getProcessBuilder_result = CommandBuilder.GetProcess()
            .addId("$PID")
            .build(null)

    // with the list, turn it all into a single string
    logger.info("Converting the result from Argument type to a List and then to a String and executing it...")
    val GP_exeResult = getProcessBuilder_result.getList().mkString("").!!

    // print the result
    logger.info("Printing the result")
    println(GP_exeResult)



    /********************************************************************************************************************

     Test-Path

     *******************************************************************************************************************/
    // builder for powershell's Test-Path command
    // .build returns a Argument(List(...)), but
    // here we simply get the list
    logger.info("Making a TestPath with the builder...")
    val testPath_result = CommandBuilder.TestPath("D:\\").build(null)

    // with the list, turn it all into a single string
    logger.info("Converting the result from Argument type to a List and then to a String and executing it...")
    val TP_exeResult = testPath_result.getList().mkString("").!!

    // print the result
    logger.info("Printing the result")
    println(TP_exeResult)



    /********************************************************************************************************************

     Get-Item

     *******************************************************************************************************************/
    // builder for powershell's Get-Item command
    // .build returns a Argument(List(...)), but
    // here we simply get the list
    logger.info("Making a GetItem with the builder...")
    val getItem_result = CommandBuilder.GetItem("C:").addForce().build(null)

    // with the list, turn it all into a single string
    logger.info("Converting the result from Argument type to a List and then to a String and executing it...")
    val GI_exeResult = getItem_result.getList().mkString("").!!

    // print the result
    logger.info("Printing the result")
    println(GI_exeResult)



    /********************************************************************************************************************

     Pipe tests that are completely arbitrary - testing multiple, different ways piping two things.

     *******************************************************************************************************************/
    getItem_result.pipe(CommandBuilder.GetService().build(null))
    CommandBuilder.GetService().build(null).pipe(CommandBuilder.GetProcess().build(null))
    testPath_result.pipe(CommandBuilder.TestConnection("my.uic.edu").build(null))
    CommandBuilder.TestConnection("danbooru.donmai.us").addQuiet().build(null).pipe(getProcessBuilder_result)
    testPath_result.pipe(CommandBuilder.GetProcess().build(null))
}
