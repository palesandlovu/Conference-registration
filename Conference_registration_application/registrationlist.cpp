#include "registrationlist.h"
#include "registration.h"
#include <QMetaObject>
#include <QMetaProperty>

//constructor
RegistrationList::RegistrationList()
{
}

//destructor
RegistrationList::~RegistrationList()
{
    qDeleteAll(m_AttendeeList);
}

//add user registration to list
bool RegistrationList::addRegistration(Registration *r)
{
    for (const auto &reg : m_AttendeeList)
    {
        if ( reg->getAttendee().getEmail() == r->getAttendee().getEmail() &&
            reg->getAttendee().getName() != r->getAttendee().getName())
        {
            return false;
        }
    }
    m_AttendeeList.append(r);
    return true;
}

//check if user input is registered by checking if name entered is in the list
bool RegistrationList::isRegisterd(QString n) const
{
    for (const auto &reg : m_AttendeeList)
    {
        if (reg->getAttendee().getName() == n)
        {
            return true;
        }
    }
    return false;
}

//return the total number of registration fee for students, guests, standard registrations and all
double RegistrationList::totalFee(QString t) const
{
    double total = 0.0;

    //use metaObject to check if type is equal to class name
    for (const auto &reg : m_AttendeeList)
    {
        if (t == "All" || reg->metaObject()->className() == t) {
            total += reg->calculateFee();
        }
    }
    return total;
}

//return the total number of registrations
int RegistrationList::totalRegitrations(QString a) const
{
    int count = 0;

    //go througgh list and compare user input to affiliations in list
    for (const auto &reg : m_AttendeeList)
    {
        if (reg->getAttendee().getAffiliation() == a) {
            ++count;
        }
    }
    return count;
}

//get registrations
QList<Registration*> RegistrationList::getRegistration() const
{
    return m_AttendeeList;
}
