#include "studentregistration.h"
#include "registration.h"

//constructor
StudentRegistration::StudentRegistration(Person a, const QString q)
:Registration(a), m_Qualification(q)
{
}

//return student fee, which is half the standard fee
double StudentRegistration::calculateFee() const
{
    return Registration::STANDARD_FEE * 1/2;

}

//Display student information
QString StudentRegistration::toString() const
{
    return "Student " + Registration::toString() +
           "\nQualification: " + m_Qualification +
           "\nFee: " + QString::number(calculateFee());
}

//return student qualification to insert into table widget
QString StudentRegistration::getQualification() const
{
    return m_Qualification;
}

