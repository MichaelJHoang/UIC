import grizzled.slf4j.Logging

@FacadeAnnotation
object Client extends App with Logging
{
    //info("Starting the application...")
    val facade = new TourAndTravelFacade
    val tourPackage = "Gold"
    val destination = "North Korea"
    val departure = "Chicago"
    println()
    facade.holidayPackageBooking(tourPackage, destination, departure)
    println()
    val serverFacade = new ServerFacade
    serverFacade.start()
    serverFacade.stop()
}
