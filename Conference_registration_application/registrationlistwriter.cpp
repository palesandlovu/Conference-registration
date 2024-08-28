#include "registrationlistwriter.h"
#include "studentregistration.h"
#include "guestregistration.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

RegistrationListWriter::RegistrationListWriter() {}

bool RegistrationListWriter::write(const RegistrationList &registrationList, const QString &filePath)
{
    QDomDocument doc("registrationlist");
    QDomElement root = doc.createElement("registrationlist");
    doc.appendChild(root);

    for (const auto &reg : registrationList.getRegistration()) {

        //append infromation in the registration list to the document element
        QDomElement regElement = doc.createElement("registration");
        regElement.setAttribute("type", reg->metaObject()->className());
        root.appendChild(regElement);

        QDomElement attendeeElement = doc.createElement("attendee");
        regElement.appendChild(attendeeElement);

        QDomElement nameElement = doc.createElement("name");
        nameElement.appendChild(doc.createTextNode(reg->getAttendee().getName()));
        attendeeElement.appendChild(nameElement);

        QDomElement affiliationElement = doc.createElement("affiliation");
        affiliationElement.appendChild(doc.createTextNode(reg->getAttendee().getAffiliation()));
        attendeeElement.appendChild(affiliationElement);

        QDomElement emailElement = doc.createElement("email");
        emailElement.appendChild(doc.createTextNode(reg->getAttendee().getEmail()));
        attendeeElement.appendChild(emailElement);

        QDomElement bookingDateElement = doc.createElement("bookingdate");
        bookingDateElement.appendChild(doc.createTextNode(reg->getBookingDate().toString()));
        regElement.appendChild(bookingDateElement);

        QDomElement registrationFeeElement = doc.createElement("registrationfee");
        registrationFeeElement.appendChild(doc.createTextNode(QString::number(reg->calculateFee())));
        regElement.appendChild(registrationFeeElement);

        if (auto studentReg = qobject_cast<StudentRegistration*>(reg)) {
            QDomElement qualificationElement = doc.createElement("qualification");
            qualificationElement.appendChild(doc.createTextNode(studentReg->getQualification()));
            regElement.appendChild(qualificationElement);
        } else if (auto guestReg = qobject_cast<GuestRegistration*>(reg)) {
            QDomElement categoryElement = doc.createElement("category");
            categoryElement.appendChild(doc.createTextNode(guestReg->getCategory()));
            regElement.appendChild(categoryElement);
        }
    }

    //output to the file
    QFile file(filePath);
    if (!file.open((QIODevice::WriteOnly | QIODevice::Text)))
    {
        return -1;
    }

    QTextStream output(&file);
    output << doc.toString();
    file.close();

    return true;

}
