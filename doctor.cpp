#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

/*       Structures For Doctor           */

struct Doctor
{
    string id;
    string name;
    string specialization;
    string department;
    string timing;
    string availability;
    string experience;
};

/*       For Dynamic Memory Allocation     */

Doctor* doctors = nullptr;
int count = 0;

/*       Functions        */

void loadDoctors();
void saveDoctors();
void doctorMenu();
void addDoctor();
void viewDoctors();
void searchDoctor();
void updateDoctor();
void deleteDoctor();

bool validName(string name);
string getValidDoctorID();
int getValidChoice(int min, int max);

string selectSpecialization();
string selectDepartment();
string selectAvailability();
string selectExperience();
string selectTiming();



/*    Definition of Functions    */

/*    Helper function for input validation    */

int getValidChoice(int min, int max)
{
    int choice;
    while(true)
    {
        cin >> choice;
        
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a number between " << min << " and " << max << ": ";
        }
        else if(choice < min || choice > max)
        {
            cout << "Invalid choice! Enter a number between " << min << " and " << max << ": ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

/*    Validation Functions    */

string getValidDoctorID()
{
    string id;

    while(true)
    {
        cout << "Enter Doctor ID (letters/numbers allowed): ";
        getline(cin, id);

        if(id.empty())
        {
            cout << "ID cannot be empty!\n";
            continue;
        }

        bool hasValidChar = false;
        for(int i = 0; i < id.length(); i++)
        {
            if(isalnum(id[i]))
            {
                hasValidChar = true;
            }
            else
            {
                cout << "ID can only contain letters and numbers!\n";
                hasValidChar = false;
                break;
            }
        }

        if(!hasValidChar)
            continue;

        bool exists = false;
        for(int i = 0; i < count; i++)
        {
            if(doctors[i].id == id)
            {
                exists = true;
                break;
            }
        }

        if(exists)
        {
            cout << "ID already exists! Please enter a unique ID.\n";
            continue;
        }

        return id;
    }
}

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

        if(i < name.length() - 1 && name[i] == ' ' && name[i + 1] == ' ')
        {
            return false;
        }
    }

    return true;
}

/*    Loading Doctors    */

void loadDoctors()
{
    delete[] doctors;
    doctors = nullptr;
    count = 0;

    ifstream file("doctors.csv");
    if(!file)
    {
        cout << "No existing data file found. Starting fresh.\n";
        return;
    }

    string line;
    while(getline(file, line))
    {
        if(!line.empty())
            count++;
    }

    if(count == 0)
    {
        file.close();
        return;
    }

    doctors = new Doctor[count];

    file.clear();
    file.seekg(0);

    for(int i = 0; i < count; i++)
    {
        getline(file, doctors[i].id, ',');
        getline(file, doctors[i].name, ',');
        getline(file, doctors[i].specialization, ',');
        getline(file, doctors[i].department, ',');
        getline(file, doctors[i].timing, ',');
        getline(file, doctors[i].availability, ',');
        getline(file, doctors[i].experience);
    }

    file.close();
    cout << "Loaded " << count << " doctor(s) from database.\n";
}

/*    Save Doctors    */

void saveDoctors()
{
    ofstream file("doctors.csv");

    if(!file)
    {
        cout << "Error: Could not save to file!\n";
        return;
    }

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

/*    DOCTOR MENU FUNCTION    */

void doctorMenu()
{
    loadDoctors();
    int choice;

    do {
        cout << "\n===== DOCTOR MENU =====";
        cout << "\n1. Add Doctor";
        cout << "\n2. View All Doctors";
        cout << "\n3. Search Doctor";
        cout << "\n4. Update Doctor Information";
        cout << "\n5. Delete Doctor";
        cout << "\n0. Back to Main Menu";
        cout << "\nEnter choice: ";
        choice = getValidChoice(0, 5);

        switch(choice)
        {
            case 0:
                cout << "Returning to main menu...\n";
                break;
            case 1:
                addDoctor();
                break;
            case 2:
                viewDoctors();
                break;
            case 3:
                searchDoctor();
                break;
            case 4:
                updateDoctor();
                break;
            case 5:
                deleteDoctor();
                break;
        }
    } while(choice != 0);
}

/*    Add Doctor    */

void addDoctor()
{
    cout << "\n===== ADD NEW DOCTOR =====\n";

    Doctor newDoc;

    newDoc.id = getValidDoctorID();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Enter Name: ";
    getline(cin, newDoc.name);

    if(!validName(newDoc.name))
    {
        cout << "Invalid Name! Only letters and spaces allowed.\n";
        return;
    }

    newDoc.specialization = selectSpecialization();
    if(newDoc.specialization == "Invalid")
    {
        cout << "Operation cancelled.\n";
        return;
    }

    newDoc.department = selectDepartment();
    if(newDoc.department == "Invalid")
    {
        cout << "Operation cancelled.\n";
        return;
    }

    newDoc.timing = selectTiming();
    if(newDoc.timing == "Invalid")
    {
        cout << "Operation cancelled.\n";
        return;
    }

    newDoc.availability = selectAvailability();
    if(newDoc.availability == "Invalid")
    {
        cout << "Operation cancelled.\n";
        return;
    }

    newDoc.experience = selectExperience();
    if(newDoc.experience == "Invalid")
    {
        cout << "Operation cancelled.\n";
        return;
    }

    // Dynamic array expansion
    Doctor* temp = new Doctor[count + 1];

    for(int i = 0; i < count; i++)
        temp[i] = doctors[i]; //copies old data

    temp[count] = newDoc;

    delete[] doctors;
    doctors = temp;
    count++;

    saveDoctors();

    cout << "\n✓ Doctor Added Successfully!\n";
}

/*    View Doctors    */

void viewDoctors()
{
    if(count == 0)
    {
        cout << "\n⚠ No Doctors Found in System!\n";
        return;
    }

    cout << "\n===== DOCTOR LIST (" << count << " Total) =====\n";

    for(int i = 0; i < count; i++)
    {
        cout << "\n--- Doctor #" << (i + 1) << " ---";
        cout << "\nID: " << doctors[i].id;
        cout << "\nName: " << doctors[i].name;
        cout << "\nSpecialization: " << doctors[i].specialization;
        cout << "\nDepartment: " << doctors[i].department;
        cout << "\nTiming: " << doctors[i].timing;
        cout << "\nAvailability: " << doctors[i].availability;
        cout << "\nExperience: " << doctors[i].experience;
        cout << "\n" << string(30, '-');
    }
}

/*    Search Doctor    */

void searchDoctor()
{
    if(count == 0)
    {
        cout << "\n⚠ No Doctors in System!\n";
        return;
    }

    string searchID;
    bool found = false;

    cout << "\nEnter Doctor ID to search: ";
    getline(cin, searchID);

    for(int i = 0; i < count; i++)
    {
        if(doctors[i].id == searchID)
        {
            found = true;

            cout << "\n✓ Doctor Found!\n";
            cout << "\n--- Details ---";
            cout << "\nID: " << doctors[i].id;
            cout << "\nName: " << doctors[i].name;
            cout << "\nSpecialization: " << doctors[i].specialization;
            cout << "\nDepartment: " << doctors[i].department;
            cout << "\nTiming: " << doctors[i].timing;
            cout << "\nAvailability: " << doctors[i].availability;
            cout << "\nExperience: " << doctors[i].experience << "\n";
            break;
        }
    }

    if(!found)
        cout << "\n⚠ Doctor with ID '" << searchID << "' not found!\n";
}

/*    Update Doctor    */

void updateDoctor()
{
    if(count == 0)
    {
        cout << "\n⚠ No Doctors in System!\n";
        return;
    }

    string id;
    bool found = false;
    char choice;

    cout << "\nEnter Doctor ID to update: ";
    getline(cin, id);

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(choice == 'y' || choice == 'Y')
            {
                string temp = selectSpecialization();
                if(temp != "Invalid")
                    doctors[i].specialization = temp;
            }

            // DEPARTMENT
            cout << "Change Department? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(choice == 'y' || choice == 'Y')
            {
                string temp = selectDepartment();
                if(temp != "Invalid")
                    doctors[i].department = temp;
            }

            // TIMING
            cout << "Change Timing? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(choice == 'y' || choice == 'Y')
            {
                string temp = selectTiming();
                if(temp != "Invalid")
                    doctors[i].timing = temp;
            }

            // AVAILABILITY
            cout << "Change Availability? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(choice == 'y' || choice == 'Y')
            {
                string temp = selectAvailability();
                if(temp != "Invalid")
                    doctors[i].availability = temp;
            }

            // EXPERIENCE
            cout << "Change Experience? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(choice == 'y' || choice == 'Y')
            {
                string temp = selectExperience();
                if(temp != "Invalid")
                    doctors[i].experience = temp;
            }

            saveDoctors();

            cout << "\n✓ Doctor Updated Successfully!\n";
            break;
        }
    }

    if(!found)
        cout << "\n⚠ Doctor with ID '" << id << "' not found!\n";
}

/*    Delete Doctor    */

void deleteDoctor()
{
    if(count == 0)
    {
        cout << "\n⚠ No Doctors in System!\n";
        return;
    }

    string id;
    bool found = false;
    char confirm;

    cout << "\nEnter Doctor ID to delete: ";
    getline(cin, id);

    for(int i = 0; i < count; i++)
    {
        if(doctors[i].id == id)
        {
            found = true;

            cout << "\n--- Doctor Details ---";
            cout << "\nName: " << doctors[i].name;
            cout << "\nSpecialization: " << doctors[i].specialization;
            
            cout << "\n\nAre you sure you want to delete this doctor? (y/n): ";
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(confirm == 'y' || confirm == 'Y')
            {
                // Shift all elements after deleted one
                for(int j = i; j < count - 1; j++)
                {
                    doctors[j] = doctors[j + 1];
                }

                count--;
                saveDoctors();

                cout << "\n✓ Doctor Deleted Successfully!\n";
            }
            else
            {
                cout << "\nDeletion cancelled.\n";
            }
            break;
        }
    }

    if(!found)
        cout << "\n⚠ Doctor with ID '" << id << "' not found!\n";
}

/*    Selection Functions with Validation    */

string selectSpecialization()
{
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

    int c = getValidChoice(1, 10);

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

    int c = getValidChoice(1, 10);

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
    cout << "\n========== AVAILABILITY MENU ==========";
    cout << "\n1. Available";
    cout << "\n2. Busy";
    cout << "\nChoice: ";

    int c = getValidChoice(1, 2);

    switch(c)
    {
        case 1: return "Available";
        case 2: return "Busy";
        default: return "Invalid";
    }
}

string selectExperience()
{
    cout << "\n========== EXPERIENCE MENU ==========";
    cout << "\n1. 1-2 Years";
    cout << "\n2. 3-5 Years";
    cout << "\n3. 5-10 Years";
    cout << "\n4. 10+ Years";
    cout << "\nChoice: ";

    int c = getValidChoice(1, 4);

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
    cout << "\n========== TIMING MENU ==========";
    cout << "\n1. 08:00 AM - 12:00 PM (Morning Shift)";
    cout << "\n2. 12:00 PM - 04:00 PM (Afternoon Shift)";
    cout << "\n3. 04:00 PM - 08:00 PM (Evening Shift)";
    cout << "\n4. 08:00 PM - 12:00 AM (Night Shift)";
    cout << "\n5. Full Day (24 Hours)";
    cout << "\nChoice: ";

    int c = getValidChoice(1, 5);

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
