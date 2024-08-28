#ifndef GUESTREGISTRATION_H
#define GUESTREGISTRATION_H
#include "person.h"
#include "registration.h"
#include <QObject>

class GuestRegistration : public Registration
{
    Q_OBJECT
public:

    GuestRegistration(Person a, const QString q);
    double calculateFee() const override;
    QString toString() const override;
    QString getCategory() const;

private:
    QString m_Category;
};

Q_DECLARE_METATYPE(GuestRegistration*)

#endif // GUESTREGISTRATION_H
