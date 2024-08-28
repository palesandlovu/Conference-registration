#include "person.h"
#include "registration.h"

//Constructor
Registration::Registration(Person a)
    :m_Attendee(a), m_BookingDate(QDate::currentDate()) //set the date to the current date
{
}

//Get attendee information from Person, which is name, affiliationa and email from Person
Person Registration::getAttendee() const
{
    return m_Attendee;
}

//Get date, which is assigned to current date
QDate Registration::getBookingDate() const
{
    return m_BookingDate;
}

//calculate registration fee, which is constant is assigned to R500
double Registration::calculateFee() const
{
    return STANDARD_FEE;
}

//Display registration information
QString Registration::toString() const
{
    return "Attendee: " + Person(m_Attendee).toString() +
           "\nBookind Date: " + m_BookingDate.toString();
}
