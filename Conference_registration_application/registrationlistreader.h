#ifndef REGISTRATIONLISTREADER_H
#define REGISTRATIONLISTREADER_H
#include "registrationlist.h"
#include "person.h"

#include <QObject>
#include <QString>
#include <QList>
#include <QXmlStreamReader>

class RegistrationListReader
{
public:
    RegistrationListReader();
    QList<Registration *> read(const QString &fileName) const;
};

#endif // REGISTRATIONLISTREADER_H
