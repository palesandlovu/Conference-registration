#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "person.h"
#include <QObject>
#include <QDate>

class Registration  : public QObject
{
    Q_OBJECT
public:
    static constexpr double STANDARD_FEE = 500;

    Registration(Person a);

    Person getAttendee() const;
    QDate getBookingDate() const;
    virtual double calculateFee() const;
    virtual QString toString() const;

protected:
    Person m_Attendee;
    QDate m_BookingDate;
};

Q_DECLARE_METATYPE(Registration*)

#endif // REGISTRATION_H
