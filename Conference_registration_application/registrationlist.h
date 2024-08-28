#ifndef REGISTRATIONLIST_H
#define REGISTRATIONLIST_H
#include "registration.h"
#include <QList>
#include <QString>
#include <QObject>

class RegistrationList : public QObject
{
    Q_OBJECT

public:
    RegistrationList();
    ~RegistrationList();
    bool addRegistration(Registration *r);
    bool isRegisterd(QString n) const;
    double totalFee(QString t) const;
    int totalRegitrations(QString a) const;
    QList<Registration*> getRegistration() const;

private:
    QList<Registration*> m_AttendeeList;
};

#endif // REGISTRATIONLIST_H
