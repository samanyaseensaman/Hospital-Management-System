#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/*       Structures For Doctor And Patients      */

struct Doctor
{
    int id;
    string name;
    string specialization;
    string department;
    string timing;
    string availability;
    string experience;
};

struct Patient {
    int patientID;
    string name;
    int doctorID;
    string disease;
    string bloodGroup;
    double bill;
};

/*       For DMA     */

Doctor* doctors = nullptr;
int count = 0;



/*       Functions     */

void loadDoctors();
void addDoctor();
void viewDoctors();
void searchDoctor();
void doctorPatients();
void doctorMenu();



/* main file just for testing WILL REMOVE LATER */

int main() {

    loadDoctors(); 

    int choice;

    do {

        cout << "\n===== HOSPITAL SYSTEM =====";
        cout << "\n1. Doctor Module";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                doctorMenu();
                break;
        }

    } while(choice != 0);


    delete[] doctors;
    return 0;
}

                            /*    Definition of Functions    */





void loadDoctors()
{

        delete[] doctors;
        doctors = nullptr;
        count = 0;

    ifstream file("doctors.csv");

    if(!file)
    {
      return;
    }

    string line;

    while(getline(file, line))
    {
        count++;
    }

    file.close();

    if(count == 0)
    {
        doctors = nullptr;
        return;
    }

    doctors = new Doctor[count];

    file.open("doctors.csv");

    for(int i = 0; i < count; i++)
    {
        file >> doctors[i].id;
        file.ignore();

        getline(file, doctors[i].name, ',');
        getline(file, doctors[i].specialization, ',');
        getline(file, doctors[i].department, ',');
        getline(file, doctors[i].timing, ',');
        getline(file, doctors[i].availability, ',');

        getline(file, doctors[i].experience);
    }

    file.close();
}





/*         DOCTOR MENU FUNCITON        */

void doctorMenu()
{

int choice;

do  {
    cout << "\n===== DOCTOR MENU =====";
        cout << "\n1. Add Doctor";
        cout << "\n2. View Doctors";
        cout << "\n3. Search Doctor";
        cout << "\n4. View Doctor Patients";
        cout << "\n0. Back";
        cout << "\nEnter choice: ";
        cin >> choice;
    


    switch(choice) 
        {

            case 1: addDoctor(); break;
            case 2: viewDoctors(); break;
            case 3: searchDoctor(); break;
            case 4: doctorPatients(); break;

        }
}while(choice !=0);
}




/*             Add Doctor               */

void addDoctor()

{

    Doctor newDoc;

cout << "Enter Doctor ID: ";
    cin >> newDoc.id;

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, newDoc.name);

    cout << "Enter Specialization: ";
    getline(cin, newDoc.specialization);

    cout << "Enter Department: ";
    getline(cin, newDoc.department);

    cout << "Enter Timing: ";
    getline(cin, newDoc.timing);

    cout << "Enter Availability: ";
    getline(cin, newDoc.availability);

    cout << "Enter Experience: ";
    getline(cin, newDoc.experience);



  Doctor* temp = new Doctor[count + 1]; // dynamic array

    for(int i = 0; i < count; i++) //copy old data into new
    {
        temp[i] = doctors[i];
    }

    temp[count] = newDoc; //adds new doc

    delete[] doctors;

    doctors = temp;

    count++;

    ofstream file("doctors.csv", ios::app);

    if(file.is_open())
    {
        file << newDoc.id << ","
             << newDoc.name << ","
             << newDoc.specialization << ","
             << newDoc.department << ","
             << newDoc.timing << ","
             << newDoc.availability << ","
             << newDoc.experience << endl;

        file.close();
    }

    cout << "\nDoctor Added Successfully!\n";
}


/*         View Doctors           */


void viewDoctors()
{
    if(count == 0)
    {
        cout << "\nNo Doctors Found!\n";
        return;
    }

    cout << "\n===== DOCTOR LIST =====\n";

    for(int i = 0; i < count; i++)
    {
        cout << "\nDoctor " << i + 1;

        cout << "\nID: " << doctors[i].id;
        cout << "\nName: " << doctors[i].name;
        cout << "\nSpecialization: " << doctors[i].specialization;
        cout << "\nDepartment: " << doctors[i].department;
        cout << "\nTiming: " << doctors[i].timing;
        cout << "\nAvailability: " << doctors[i].availability;
        cout << "\nExperience: " << doctors[i].experience;

        cout << "\n----------------------";
    }
}






