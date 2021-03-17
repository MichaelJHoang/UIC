/*

  Source: https://blog.knoldus.com/scala-facade-design-pattern/


 */

class GuideBooking
{
  def bookGuide(destination : String) : Unit =
    {
      println("A guide is booked for sightseeing at " + destination)
    }
}



class ShuttleBooking
{
  def bookShuttle(tourPackage : String) : Unit =
    {
      println ("Shuttle is booked under package " + tourPackage)
    }
}



class HotelBooking
{
  def bookHotel(tourPackage : String,
                destination : String) : Unit =
    {
      println("Hotel booked at " + destination +
              " under package " + tourPackage)
    }
}



class TicketBooking
{
  def bookFlight(tourPackage : String,
                 destination : String,
                 departure : String) : Unit =
    {
      println("Round-trip flight tickets for "
              + destination + " & " + departure +
              " is booked under package " + tourPackage)
    }
}



class TourAndTravelFacade
{
  val ticketBooking = new TicketBooking
  val hotelBooking = new HotelBooking
  val cabBooking = new ShuttleBooking
  val guideBooking = new GuideBooking

  def holidayPackageBooking(tourPackage : String,
                            destination : String,
                            departure : String): Boolean =
    {
      ticketBooking.bookFlight(tourPackage, destination, departure)
      hotelBooking.bookHotel(tourPackage, destination)
      cabBooking.bookShuttle(tourPackage)
      guideBooking.bookGuide(destination)

      true
    }
}
