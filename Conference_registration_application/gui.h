#ifndef GUI_H
#define GUI_H
#include "registrationlist.h"
#include "registrationlistreader.h"

#include <QWidget>
class QTableWidget;
class QLineEdit;
class QLabel;
class QDateEdit;
class QComboBox;
class QPushButton;
class QComboBox;

class Gui : public QWidget
{
    Q_OBJECT
public:
    explicit Gui(QWidget *parent = nullptr);    

private slots:
    void addToList();
    void totalNumInstitution();
    void totalFees();
    void updateTable();
    void enableSearchButton();
    void searchList();
    void saveRegistrationList();
    void loadRegistrationList();

private:
    void setupGUI();

    QTableWidget *tblRegistrations;
    QLabel *lblRegister;
    QLabel *lblName;
    QLineEdit *edtName;
    QLabel *lblAffiliation;
    QLineEdit *edtAffiliation;
    QLabel *lblEmail;
    QLineEdit *edtEmail;
    QLabel *lblType;
    QComboBox *combType;
    QDateEdit *edtDate;
    QLabel *lblNumAttendees;
    QLabel  *lblInstitution;
    QLineEdit *edtInstitution;
    QPushButton *btnIntitution;
    QLineEdit *edtFees;
    QLineEdit *lblTotalFees;
    QComboBox *combTotalFee;
    QPushButton *btnTotalFee;
    QLineEdit *edtOutput;
    QPushButton *btnSearch;
    QPushButton *btnRegister;
    QPushButton *btnSave;
    QPushButton *btnLoad;

    RegistrationList list;
    RegistrationListReader listReader;
};

#endif // GUI_H
