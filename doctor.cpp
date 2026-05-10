#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
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

bool validName(string name);
bool validDepartment(string dept);
bool validSpecialization(string spec);
bool validTiming(string timing);
bool validAvailability(string status);
bool validExperience(string exp);




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


/*             Validation Functions                 */


bool validName(string name)
{
    if(name.empty())
        return false;

    if(name[0] == ' ' || name[name.length() - 1] == ' ')
        return false;

    for(int i = 0; i < name.length(); i++)
    {
        if(!isalpha(name[i]) && name[i] != ' ')
        {
            return false;
        }

        // Prevent double spaces
        if(name[i] == ' ' && name[i + 1] == ' ')
        {
            return false;
        }
    }

    return true;
}

bool validDepartment(string dept)
{
    if(dept.empty())
        return false;

    for(int i = 0; i < dept.length(); i++)
    {
        if(!isalpha(dept[i]) &&
           dept[i] != ' ' &&
           dept[i] != '&')
        {
            return false;
        }
    }

    return true;
}


bool validSpecialization(string spec)
{
    if(spec.empty())
        return false;

    for(int i = 0; i < spec.length(); i++)
    {
        if(!isalpha(spec[i]) && spec[i] != ' ')
        {
            return false;
        }
    }

    return true;
}

bool validTiming(string timing)
{
    if(timing.empty())
        return false;

    for(int i = 0; i < timing.length(); i++)
    {
        if(!isdigit(timing[i]) &&
           !isalpha(timing[i]) &&
           timing[i] != ':' &&
           timing[i] != '-' &&
           timing[i] != ' ')
        {
            return false;
        }
    }

    return true;
}

bool validAvailability(string status)
{
    return (status == "Available" ||
            status == "Busy");
}



bool validExperience(string exp)
{
    if(exp.empty())
        return false;

    for(int i = 0; i < exp.length(); i++)
    {
        char c = exp[i];

        if(isdigit(c))
            continue;

        if(c == ' ')
            continue;

        if(isalpha(c))
            continue;

        return false;
    }

    return true;
}


                        
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
            case 0: cout << "Returning...\n";break;
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

        if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid ID!\n";
        return;
    }

    if(newDoc.id <= 0)
{
    cout << "Invalid ID!\n";
    return;
}

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

    if(!validName(newDoc.name))
    {
        cout << "Invalid Name!\n";
        return;
    }


    cout << "Enter Specialization: ";
    getline(cin, newDoc.specialization);

    if(!validSpecialization(newDoc.specialization))
    {
        cout << "Invalid Specialization!\n";
        return;
    }



    cout << "Enter Department: ";
    getline(cin, newDoc.department);

    if(!validDepartment(newDoc.department))
    {
        cout << "Invalid Department!\n";
        return;
    }



    cout << "Enter Timing: ";
    getline(cin, newDoc.timing);

        if(!validTiming(newDoc.timing))
    {
        cout << "Invalid Timing!\n";
        return;
    }



    cout << "Enter Availability: ";
    getline(cin, newDoc.availability);

    if(!validAvailability(newDoc.availability))
    {
        cout << "Invalid Availability!\n";
        return;
    }



    cout << "Enter Experience: ";
    getline(cin, newDoc.experience);

    if(!validExperience(newDoc.experience))
    {
        cout << "Invalid Experience!\n";
        return;
    }



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
        cout << "\nDoctor: " << i + 1;

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

        if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid ID!\n";
        return;
    }

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

    if(cin.fail() || id <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid ID!\n";
        return;
    }

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

            // NAME
            cout << "Change Name? (y/n): ";
            cin >> choice;
            cin.ignore();

            if(choice == 'y' || choice == 'Y')
            {
                string temp;
                cout << "Enter new name: ";
                getline(cin, temp);

                if(validName(temp))
                    doctors[i].name = temp;
                else
                    cout << "Invalid Name! Not Updated.\n";
            }

            // SPECIALIZATION
            cout << "Change Specialization? (y/n): ";
            cin >> choice;
            cin.ignore();

            if(choice == 'y' || choice == 'Y')
            {
                string temp;
                cout << "Enter new specialization: ";
                getline(cin, temp);

                if(validSpecialization(temp))
                    doctors[i].specialization = temp;
                else
                    cout << "Invalid Specialization!\n";
            }

            // DEPARTMENT
            cout << "Change Department? (y/n): ";
            cin >> choice;
            cin.ignore();

            if(choice == 'y' || choice == 'Y')
            {
                string temp;
                cout << "Enter new department: ";
                getline(cin, temp);

                if(validDepartment(temp))
                    doctors[i].department = temp;
                else
                    cout << "Invalid Department!\n";
            }

            // TIMING
            cout << "Change Timing? (y/n): ";
            cin >> choice;
            cin.ignore();

            if(choice == 'y' || choice == 'Y')
            {
                string temp;
                cout << "Enter new timing: ";
                getline(cin, temp);

                if(validTiming(temp))
                    doctors[i].timing = temp;
                else
                    cout << "Invalid Timing!\n";
            }

            // AVAILABILITY
            cout << "Change Availability? (y/n): ";
            cin >> choice;
            cin.ignore();

            if(choice == 'y' || choice == 'Y')
            {
                string temp;
                cout << "Enter (Available/Busy): ";
                getline(cin, temp);

                if(validAvailability(temp))
                    doctors[i].availability = temp;
                else
                    cout << "Invalid Availability!\n";
            }

            // EXPERIENCE
            cout << "Change Experience? (y/n): ";
            cin >> choice;
            cin.ignore();

            if(choice == 'y' || choice == 'Y')
            {
                string temp;
                cout << "Enter experience: ";
                getline(cin, temp);

                if(validExperience(temp))
                    doctors[i].experience = temp;
                else
                    cout << "Invalid Experience!\n";
            }

            saveDoctors();

            cout << "\nDoctor Updated Successfully!\n";
            break;
        }
    }

    if(!found)
        cout << "\nDoctor Not Found!\n";
}


