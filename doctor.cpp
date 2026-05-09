#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/*       Structures For Doctor           */

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

/*       For DMA     */

Doctor* doctors = nullptr;
int count = 0;



/*       Functions     */

void loadDoctors();
void saveDoctors();

void doctorMenu();

void addDoctor();
void viewDoctors();
void searchDoctor();
void updateDoctor();



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


/*        Loading Doctors       */


void loadDoctors()
{
    delete[] doctors;
    doctors = nullptr;
    count = 0;

    ifstream file("doctors.csv");
    if(!file) return;

    string line;
    while(getline(file, line))
        count++;

    if(count == 0) return;

    doctors = new Doctor[count];

    file.clear();
    file.seekg(0);

    for(int i = 0; i < count; i++)
    {
        string idStr;

        getline(file, idStr, ',');
        doctors[i].id = stoi(idStr);

        getline(file, doctors[i].name, ',');
        getline(file, doctors[i].specialization, ',');
        getline(file, doctors[i].department, ',');
        getline(file, doctors[i].timing, ',');
        getline(file, doctors[i].availability, ',');
        getline(file, doctors[i].experience);
    }

    file.close();
}



/*          Save Doctors         */

void saveDoctors()
{
    ofstream file("doctors.csv");

    for(int i = 0; i < count; i++)
    {
        file << doctors[i].id << ","
             << doctors[i].name << ","
             << doctors[i].specialization << ","
             << doctors[i].department << ","
             << doctors[i].timing << ","
             << doctors[i].availability << ","
             << doctors[i].experience << "\n";
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
        cout << "\n4. Update Information";
        cout << "\n0. Back";
        cout << "\nEnter choice: ";
        cin >> choice;
    


    switch(choice) 
        {

            case 1: addDoctor(); break;
            case 2: viewDoctors(); break;
            case 3: searchDoctor(); break;
            case 4: updateDoctor(); break;
            default:
            cout << "Invalid choice!\n";
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


      for(int i = 0; i < count; i++)
    {
        if(doctors[i].id == newDoc.id)
        {
            cout << "Doctor ID already exists!\n";
            return;
        }
    }

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



    Doctor* temp = new Doctor[count + 1];

    for(int i = 0; i < count; i++)
        temp[i] = doctors[i];

    temp[count] = newDoc;

    delete[] doctors;
    doctors = temp;
    count++;

    saveDoctors();

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


/*          Search Doctor          */

void searchDoctor()
{
    int searchID;
    bool found = false;

    cout << "\nEnter Doctor ID: ";
    cin >> searchID;

    for(int i = 0; i < count; i++)
    {
        if(doctors[i].id == searchID)
        {
            found = true;

            cout << "\nDoctor Found!\n";
            cout << "\nID: " << doctors[i].id;
            cout << "\nName: " << doctors[i].name;
            cout << "\nSpecialization: " << doctors[i].specialization;
            cout << "\nDepartment: " << doctors[i].department;
            cout << "\nTiming: " << doctors[i].timing;
            cout << "\nAvailability: " << doctors[i].availability;
            cout << "\nExperience: " << doctors[i].experience;
            break;
        }
    }

    if(!found)
        cout << "\nDoctor Not Found!\n";
}



/*          For Corrections            */
void updateDoctor()
{
    int id;
    bool found = false;
    char choice;

    cout << "Enter Doctor ID to update: ";
    cin >> id;
    cin.ignore();

    for(int i = 0; i < count; i++)
    {
        if(doctors[i].id == id)
        {
            found = true;

            cout << "\n--- CURRENT DATA ---\n";
            cout << "Name: " << doctors[i].name << endl;
            cout << "Specialization: " << doctors[i].specialization << endl;
            cout << "Department: " << doctors[i].department << endl;
            cout << "Timing: " << doctors[i].timing << endl;
            cout << "Availability: " << doctors[i].availability << endl;
            cout << "Experience: " << doctors[i].experience << endl;

            cout << "\n--- UPDATE OPTIONS ---\n";

            cout << "Change Name? (y/n): ";
            cin >> choice;
            cin.ignore();
            if(choice == 'y' || choice == 'Y')
            {
                cout << "Enter new name: ";
                getline(cin, doctors[i].name);
            }

            cout << "Change Specialization? (y/n): ";
            cin >> choice;
            cin.ignore();
            if(choice == 'y' || choice == 'Y')
            {
                cout << "Enter new specialization: ";
                getline(cin, doctors[i].specialization);
            }

            cout << "Change Department? (y/n): ";
            cin >> choice;
            cin.ignore();
            if(choice == 'y' || choice == 'Y')
            {
                cout << "Enter new department: ";
                getline(cin, doctors[i].department);
            }

            cout << "Change Timing? (y/n): ";
            cin >> choice;
            cin.ignore();
            if(choice == 'y' || choice == 'Y')
            {
                cout << "Enter new timing: ";
                getline(cin, doctors[i].timing);
            }

            cout << "Change Availability? (y/n): ";
            cin >> choice;
            cin.ignore();
            if(choice == 'y' || choice == 'Y')
            {
                cout << "Enter new availability: ";
                getline(cin, doctors[i].availability);
            }

            cout << "Change Experience? (y/n): ";
            cin >> choice;
            cin.ignore();
            if(choice == 'y' || choice == 'Y')
            {
                cout << "Enter new experience: ";
                getline(cin, doctors[i].experience);
            }

            saveDoctors();

            cout << "\nDoctor Updated Successfully!\n";
            break;
        }
    }

    if(!found)
    {
        cout << "\nDoctor Not Found!\n";
    }
}


