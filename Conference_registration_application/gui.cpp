#include "gui.h"
#include "person.h"
#include "registration.h"
#include "studentregistration.h"
#include "guestregistration.h"
#include "registrationlist.h"
#include "registrationlistwriter.h"

#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QGridLayout>
#include <QDebug>
#include <QGroupBox>
#include <QFileDialog>
#include <QDomDocument>
#include <QDomElement>


Gui::Gui(QWidget *parent)
    : QWidget{parent},
    tblRegistrations (new QTableWidget),
    edtName (new QLineEdit),
    edtAffiliation (new QLineEdit),
    edtEmail (new QLineEdit),
    edtInstitution (new QLineEdit),
    edtFees (new QLineEdit),
    edtOutput (new QLineEdit),
    combType (new QComboBox),
    combTotalFee (new QComboBox),
    btnSearch (new QPushButton("Search")),
    btnRegister (new QPushButton("Register")),
    btnIntitution (new QPushButton("Total Attendees")),
    btnTotalFee (new QPushButton("Total Fees")),
    btnSave (new QPushButton ("Save to File")),
    btnLoad (new QPushButton ("Load from File"))
{

    setupGUI(); //call gui function

    //set the window title and size
    setWindowTitle("Conference Registration");
    setMinimumSize(150, 100);

    //connection signals to enable buttons and assign buttons to functions
    connect(edtName, &QLineEdit::textChanged, this, &Gui::enableSearchButton);
    connect(btnSearch, &QPushButton::clicked, this, &Gui::searchList);
    connect(btnRegister, &QPushButton::clicked, this, &Gui::addToList);
    connect(btnIntitution, &QPushButton::clicked, this, &Gui::totalNumInstitution);
    connect(btnTotalFee, &QPushButton::clicked, this, &Gui::totalFees);
    connect(btnSave, &QPushButton::clicked, this, &Gui::saveRegistrationList);
    connect(btnLoad, &QPushButton::clicked, this, &Gui::loadRegistrationList);
}

//Sesarch button will be enabled when edtName has text
void Gui::enableSearchButton()
{
    if (edtName->text().size() != 0)
    {
        btnSearch->setEnabled(true);
    }
}


//When user presses button search, search list and check if user input(name) is already registered or not
void Gui::searchList()
{
    QString name = edtName->text();
    bool isRegistered = list.isRegisterd(name);

    if (isRegistered == true)
    {
        //if user is registered, show messagebox and not enable register button
        QMessageBox::information(this, "Search Completed","User registered");
        btnRegister->setEnabled(false);
        edtName->clear();
        edtAffiliation->clear();
        edtEmail->clear();
        btnSearch->setEnabled(false);
        btnRegister->setEnabled(false);
    }else
        //else if not registered, then enable register button
        QMessageBox::information(this, "Search Completed","User not registered. \nContinue");
        btnRegister->setEnabled(true);
}


//save/write registration list to xml file
void Gui::saveRegistrationList()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Registration List"), "", tr("XML Files (*.xml)"));
    if (!fileName.isEmpty()) {
        if (RegistrationListWriter::write(list, fileName)) {
            QMessageBox::information(this, "Saved", "Registration list saved");
        } else {
            QMessageBox::warning(this, "Error", "Failed to save ragistration list");
        }
    }
    btnSave->setEnabled(false);
    tblRegistrations->clear();
}

//load registration to table widget
void Gui::loadRegistrationList()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Registration List", "", "XML Files (*.xml)");
    if (!fileName.isEmpty()){
        QList<Registration*> registrations = listReader.read(fileName);
        if (registrations.isEmpty()) {
            QMessageBox::warning(this, "Error", "Failed to load registration list");
        } else {
            for (Registration* reg: registrations) {
                list.addRegistration(reg);
            }
        }
         updateTable();
    }
}

//Add user input,together with registration fee, and qualification/category to table widget
void Gui::addToList()
{
    //Get the person information
    QString name = edtName->text();
    QString affiliation = edtAffiliation->text();
    QString email = edtEmail->text();
    QString type = combType->currentText();

    //assign the information to class Person
    Person attendee(name, affiliation, email);
    Registration *registration = nullptr; //registration instance

    QString textQualification;
    QString textCategory;
    bool ok;

    //type of registration, and if registration is student/guest, get qualification/category through Inputdialog
    if (type == "Standard")
    {
        registration = new Registration(attendee);
    }
    if (type == "Student")
    {
        textQualification = QInputDialog::getText(0, "Input Dialog", "Enter your qualification: ", QLineEdit::Normal, "", &ok);
        registration = new StudentRegistration(attendee, textQualification);
    }
    else if (type == "Guest"){
        textCategory = QInputDialog::getText(0, "Input Dialog", "Enter your category: ", QLineEdit::Normal, "", &ok);
        registration = new GuestRegistration(attendee, textCategory);
    }

    //if we are adding registraion ifo to list, output registration information to table widget
    if (list.addRegistration(registration))
    {
        updateTable();
    } else {
        delete registration; //if not, delete registration
    }

    //clear widgets after adding information to table widget
    edtName->clear();
    edtAffiliation->clear();
    edtEmail->clear();
    btnSearch->setEnabled(false);
    btnRegister->setEnabled(false);
    btnSave->setEnabled(true);
    QMessageBox::information(this, "Registration", "Registration added"); //message box, after successfully adding to the table widget
}

//get the total number of institute registrations
void Gui::totalNumInstitution()
{
    QString institution = edtInstitution->text();
    int count = list.totalRegitrations(institution);
    edtOutput->setText(QString::number(count) + " attendee/s"); //output total number into editbox
    edtInstitution->clear(); //clear institute edit box
}

//get the total number of registered fees, for registration types
void Gui::totalFees()
{
    QString type = combTotalFee->currentText();
    double total = list.totalFee(type);
    edtOutput->setText(type + " fees: " + QString::number(total)); //output total fees into editbox
}

void Gui::updateTable()
{
    tblRegistrations->setRowCount(0);
    const QList<Registration*> r = list.getRegistration(); //list class instance

    //for every registration in the list, add the information to the table widget
    foreach (Registration* reg, r){
        int rowCount = tblRegistrations->rowCount();
        tblRegistrations->insertRow(rowCount);

        tblRegistrations->setItem(rowCount, 0, new QTableWidgetItem(reg->getAttendee().getName()));
        tblRegistrations->setItem(rowCount, 1, new QTableWidgetItem(reg->getAttendee().getAffiliation()));
        tblRegistrations->setItem(rowCount, 2, new QTableWidgetItem(reg->getAttendee().getEmail()));
        tblRegistrations->setItem(rowCount, 3, new QTableWidgetItem(QString::number(reg->calculateFee())));
        tblRegistrations->setItem(rowCount, 4, new QTableWidgetItem(reg->getBookingDate().toString("yyyy/MM/dd")));
        tblRegistrations->setItem(rowCount, 5, new QTableWidgetItem(reg->metaObject()->className()));

        //for students/guests add qualification/category from the StudentRegistration/GuestRegistration class

        if (qobject_cast<StudentRegistration*>(reg)){
            auto studentReg = qobject_cast<StudentRegistration*>(reg);
            tblRegistrations->setItem(rowCount, 6, new QTableWidgetItem(studentReg->getQualification()));
        } else if (qobject_cast<GuestRegistration*>(reg)){
            auto studentReg = qobject_cast<GuestRegistration*>(reg);
            tblRegistrations->setItem(rowCount, 6, new QTableWidgetItem(studentReg->getCategory()));
        }
    }
}

//Set up the GUI
void Gui::setupGUI()
{
    QGridLayout *layout = (new QGridLayout(this));

    //Widgeta
    QLabel *lblName = new QLabel (tr("Name:"));
    QLabel *lblAffiliation = new QLabel (tr("Affiliation:"));
    QLabel *lblEmail = new QLabel (tr("Email:"));
    QLabel *lblType = new QLabel (tr("Type"));
    QLabel *lblNumAttendee = new QLabel (tr("\tTotal number of Attendees"));
    QLabel *lblInstitution = new QLabel (tr("Institute:"));
    QLabel *lblTotalFees = new QLabel (tr("\tTotal registration fess"));

    QGroupBox *registerBox = new QGroupBox(tr("Register")); //Register group box for registration user inputs widgets
    QGroupBox *viewBox = new QGroupBox(tr("View")); //View group box for widgets to view total numbers
    //vertical layout for Register and View group boxes
    QBoxLayout *vbox = new QVBoxLayout;
    QVBoxLayout *vbox2 = new QVBoxLayout;

    //Registration types into combobox
    combType->addItem("Standard");
    combType->addItem("Student");
    combType->addItem("Guest");

    //Add widgets to the Register group box
    vbox->addWidget(lblName);
    vbox->addWidget(edtName);
    vbox->addWidget(lblAffiliation);
    vbox->addWidget(edtAffiliation);
    vbox->addWidget(lblEmail);
    vbox->addWidget(edtEmail);
    vbox->addWidget(lblType);
    vbox->addWidget(combType);
    vbox->addStretch(1);
    registerBox->setLayout(vbox);

    //Registration types into combobox
    combTotalFee->addItem("Registration");
    combTotalFee->addItem("StudentRegistration");
    combTotalFee->addItem("GuestRegistration");
    combTotalFee->addItem("All");

    //Add widgets to the View group box
    vbox2->addWidget(lblNumAttendee);
    vbox2->addWidget(lblInstitution);
    vbox2->addWidget(edtInstitution);
    vbox2->addWidget(btnIntitution);
    vbox2->addWidget(lblTotalFees);
    vbox2->addWidget(combTotalFee);
    vbox2->addWidget(btnTotalFee);
    vbox2->addStretch(1);
    viewBox->setLayout(vbox2);

    //Layout all the widgets in an appropriate readable manner

    layout->addWidget(registerBox,0,0);
    layout->addWidget(tblRegistrations,0,1);
    tblRegistrations->setRowCount(tblRegistrations->rowCount());
    tblRegistrations->setColumnCount(8);
    //assign column names to table widget
    QStringList tblLabels;
    tblLabels << "Name" << "Affiliation" << "Email Address" << "Registration Fee" << "Date" << "Type" << "Qualification" << "Category";
    tblRegistrations->setHorizontalHeaderLabels(tblLabels);

    layout->addWidget(viewBox,0,2);

    layout->addWidget(btnSearch,1,0);
    layout->addWidget(btnRegister,1,1);
    layout->addWidget(edtOutput,1,2);
    layout->addWidget(btnSave, 1,3);
    layout ->addWidget(btnLoad, 2, 3);

    //clear widgets
    btnSearch->setEnabled(false);
    btnRegister->setEnabled(false);
    btnSave->setEnabled(false);
    setLayout(layout);

}
