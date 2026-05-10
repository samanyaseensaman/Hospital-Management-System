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

string selectSpecialization();
string selectDepartment();
string selectAvailability();
string selectExperience();
string selectTiming();





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


     newDoc.specialization = selectSpecialization();
    if(newDoc.specialization == "Invalid") return;


    newDoc.department = selectDepartment();
    if(newDoc.department == "Invalid") return;

    newDoc.availability = selectAvailability();
    if(newDoc.availability == "Invalid") return;

    newDoc.experience = selectExperience();
    if(newDoc.experience == "Invalid") return;

    newDoc.timing = selectTiming();
    if(newDoc.timing == "Invalid") return;



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
            doctors[i].specialization = selectSpecialization();


            // DEPARTMENT
            doctors[i].department = selectDepartment();

            // TIMING
            doctors[i].timing = selectTiming();
      
            // AVAILABILITY
            doctors[i].availability = selectAvailability();

            // EXPERIENCE
            doctors[i].experience = selectExperience();

            saveDoctors();

            cout << "\nDoctor Updated Successfully!\n";
            break;
        }
    }

    if(!found)
        cout << "\nDoctor Not Found!\n";
}



string selectSpecialization()
{
    int c;

    cout << "\n========== SPECIALIZATION MENU ==========";
    cout << "\n1. Cardiologist (Heart Specialist)";
    cout << "\n2. Neurologist (Brain/Nervous System)";
    cout << "\n3. Dermatologist (Skin Specialist)";
    cout << "\n4. Orthopedic Surgeon (Bones/Joints)";
    cout << "\n5. Pediatrician (Children Specialist)";
    cout << "\n6. General Physician (General Doctor)";
    cout << "\n7. ENT Specialist (Ear, Nose, Throat)";
    cout << "\n8. Gynecologist (Women Health)";
    cout << "\n9. Psychiatrist (Mental Health)";
    cout << "\n10. Radiologist (Imaging/X-Ray)";
    cout << "\nChoice: ";

    cin >> c;

    switch(c)
    {
        case 1: return "Cardiologist";
        case 2: return "Neurologist";
        case 3: return "Dermatologist";
        case 4: return "Orthopedic Surgeon";
        case 5: return "Pediatrician";
        case 6: return "General Physician";
        case 7: return "ENT Specialist";
        case 8: return "Gynecologist";
        case 9: return "Psychiatrist";
        case 10: return "Radiologist";
        default: return "Invalid";
    }
}

string selectDepartment()
{
    int c;

    cout << "\n========== DEPARTMENT MENU ==========";
    cout << "\n1. Cardiology Department";
    cout << "\n2. Neurology Department";
    cout << "\n3. Orthopedics Department";
    cout << "\n4. Pediatrics Department";
    cout << "\n5. Emergency Department";
    cout << "\n6. Surgery Department";
    cout << "\n7. Radiology Department";
    cout << "\n8. Outpatient Department (OPD)";
    cout << "\n9. Intensive Care Unit (ICU)";
    cout << "\n10. Administration";
    cout << "\nChoice: ";

    cin >> c;

    switch(c)
    {
        case 1: return "Cardiology";
        case 2: return "Neurology";
        case 3: return "Orthopedics";
        case 4: return "Pediatrics";
        case 5: return "Emergency";
        case 6: return "Surgery";
        case 7: return "Radiology";
        case 8: return "OPD";
        case 9: return "ICU";
        case 10: return "Administration";
        default: return "Invalid";
    }
}


string selectAvailability()
{
    int c;
    cout << "\n========== AVAILABILITY MENU ==========";
    cout << "\n1.Available 2.Busy\nChoice: ";
    cin >> c;

    switch(c)
    {
        case 1: return "Available";
        case 2: return "Busy";
        default: return "Invalid";
    }
}


string selectExperience()
{
    int c;
    cout << "\n========== EXPERIENCE MENU ==========";

    cout << "\n 1.1-2 Years\n 2.3-5 Years\n 3.5-10 Years\n 4.10+\nChoice: ";
    cin >> c;

    switch(c)
    {
        case 1: return "1-2 Years";
        case 2: return "3-5 Years";
        case 3: return "5-10 Years";
        case 4: return "10+ Years";
        default: return "Invalid";
    }
}

string selectTiming()
{
    int c;

    cout << "\n--- SELECT TIMING ---";
    cout << "\n1. 08:00 AM - 12:00 PM (Morning Shift)";
    cout << "\n2. 12:00 PM - 04:00 PM (Afternoon Shift)";
    cout << "\n3. 04:00 PM - 08:00 PM (Evening Shift)";
    cout << "\n4. 08:00 PM - 12:00 AM (Night Shift)";
    cout << "\n5. Full Day (24 Hours)";
    cout << "\nChoice: ";

    cin >> c;

    switch(c)
    {
        case 1: return "08:00 AM - 12:00 PM";
        case 2: return "12:00 PM - 04:00 PM";
        case 3: return "04:00 PM - 08:00 PM";
        case 4: return "08:00 PM - 12:00 AM";
        case 5: return "24 Hours";
        default: return "Invalid";
    }
}
