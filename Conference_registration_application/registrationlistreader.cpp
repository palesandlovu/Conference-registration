#include "registrationlistreader.h"
#include "person.h"
#include "registration.h"
#include "studentregistration.h"
#include "guestregistration.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDate>

RegistrationListReader::RegistrationListReader() {}

QList<Registration *> RegistrationListReader::read(const QString &fileName) const
{
    //Open file from device
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QList<Registration*>();
    }

    QXmlStreamReader reader(&file); //use xmlstreamreader to read through xml file
    QList<Registration*> registrations;
    //assign null pointers to attendee parameters
    QString attendeeName = nullptr;
    QString attendeeAffiliation = nullptr;
    QString attendeeEmail = nullptr;


    QString type;
    QString qualification, category;
    QDate currentDate;
    double fee;

    //read through the xml file and assign the appropriate line to an appropriate variable
    while (!reader.atEnd() && !reader.hasError()){

        reader.readNext();
        if (reader.isStartElement()){
            if (reader.name().toString() == "registration"){
                type = reader.attributes().value("type").toString();

            //get attendee information
            } else if (reader.name().toString() == "name"){
                attendeeName = reader.readElementText();
            } else if (reader.name().toString() == "affiliation"){
                attendeeAffiliation = reader.readElementText();
            } else if (reader.name().toString() == "email"){
                attendeeEmail = reader.readElementText();

            //get registration information
            } else if (reader.name().toString() == "bookingdate"){
                currentDate = QDate::fromString(reader.readElementText());
            } else if (reader.name().toString() == "registrationfee"){
                fee = reader.readElementText().toDouble();
            } else if (reader.name().toString() == "qualification"){
                qualification = reader.readElementText();
            } else if (reader.name().toString() == "category"){
                category = reader.readElementText();
            }
        //get type of qualification/category for student and guest registrations
        } else if (reader.isEndElement() && reader.name().toString() == "registration"){
            Registration * registration = nullptr;
            Person attendee(attendeeName, attendeeAffiliation, attendeeEmail);
            if (type == "StudentRegistration") {
                registration = new StudentRegistration(attendee, qualification);
            } else if (type == "GuestRegistration"){
                registration = new GuestRegistration(attendee, category);
            }

            //append everything to registration list
            registrations.append(registration);
            attendee = Person(attendeeName, attendeeAffiliation, attendeeEmail);
            qualification.clear();
            category.clear();
        }

    }
    //open file error
    if (reader.hasError()) {
        qDeleteAll(registrations);
        return QList<Registration*>();
    }
    file.close();
    return registrations;

}
