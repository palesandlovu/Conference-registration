#ifndef STUDENTREGISTRATION_H
#define STUDENTREGISTRATION_H
#include "person.h"
#include "registration.h"
#include <QObject>

class StudentRegistration : public Registration
{
    Q_OBJECT
public:
    StudentRegistration(Person a, const QString q);
    double calculateFee() const override;
    QString toString() const override;
    QString getQualification() const;

private:
    QString m_Qualification;
};

Q_DECLARE_METATYPE(StudentRegistration*)
#endif // STUDENTREGISTRATION_H
