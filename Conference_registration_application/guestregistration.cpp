#include "guestregistration.h"
#include "registration.h"

//constructer
GuestRegistration::GuestRegistration(Person a, const QString q)
    :Registration(a), m_Category(q)
{
}

//return the guest fee, which is 10% the standard fee
double GuestRegistration::calculateFee() const
{
    return Registration::STANDARD_FEE * 10/100;
}

//toString to Display Guest info
QString GuestRegistration::toString() const
{
    return  "Guest " + Registration::toString() +
            "\nCategory: " + m_Category +
            "\nFee: " + QString::number(calculateFee());
}

//Get type of guest category to insert into table widget
QString GuestRegistration::getCategory() const
{
    return m_Category;
}
