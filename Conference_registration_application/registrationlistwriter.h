#ifndef REGISTRATIONLISTWRITER_H
#define REGISTRATIONLISTWRITER_H

#include <QDomDocument>
#include <QString>
#include "registrationlist.h"


class RegistrationListWriter
{
public:
    RegistrationListWriter();
    static bool write(const RegistrationList &registrationList, const QString &filePath);
};

#endif // REGISTRATIONLISTWRITER_H
