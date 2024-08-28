#include "person.h"

//Constructor
Person::Person(QString &n, QString &a, QString &e)
    :m_Name(n), m_Affiiation(a), m_Email(e)
{

}

//Get name
QString Person::getName() const
{
    return m_Name;
}

void Person::setName(QString &n)
{
    n = m_Name;
}

//Get affiliation(Institution)
QString Person::getAffiliation() const
{
    return m_Affiiation;
}

void Person::setAffiliation(QString &a)
{
    a = m_Affiiation;
}

//Get email
QString Person::getEmail() const
{
    return m_Email;
}

void Person::setEmail(QString &e)
{
    e = m_Email;
}

//Display user information
QString Person::toString()
{
    return "Name: " + m_Name +
            "\nAffiliation " + m_Affiiation +
            "\nEmail " + m_Email;
}
