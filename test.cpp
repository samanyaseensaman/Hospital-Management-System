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

/* Main function */

// int new_func() {                          //USE LOADDOCTORS IN BEGINNING OF MAIN AND DELETE[]DOCTORS AT END 
//
//    loadDoctors(); //loads doctors into memory


    int choice;

    do {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====";
        cout << "\n1. Doctor Module";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        choice = getValidChoice(0, 1);

        switch(choice) {
            case 1:
                doctorMenu();
                break;
            case 0:
                cout << "\nExiting system...\n";
                break;
        }

    } while(choice != 0);

    delete[] doctors;
    return 0;
}

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



struct Patient {
    int patientID;
    string name;
    int age;
    string disease;
    string bloodGroup;
    string admissionDate;
    double totalBill;
};

struct PatientManager {
    int TOTAL_HOSPITAL_BEDS = 20;
    Patient patients[20];

    double RATE_PER_DAY = 500.0;
    string FILENAME = "patientsinfo.csv";
    int patientCount = 0;

    int displayAllPatients() {
        // Load patients from CSV 
        ifstream file(FILENAME);
        if (!file.is_open()) {
            cout << "Error opening file\n";
            return 1;
        }

        patientCount = 0; 

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            if (patientCount >= TOTAL_HOSPITAL_BEDS) break;

     
            string val;
            stringstream ss(line);
            Patient p{};

           
            if (!getline(ss, val, ',')) continue;    // basically reads each line and assigns value between the commas to the patientID
            p.patientID = stoi(val);

            
            if (!getline(ss, val, ',')) val = ""; //ss acts as a pointer as well as it shifts the cursor after reading value like *ptr++
            p.name = val;   // matlab pointers are covered in this project 💪💪💪

          
            if (!getline(ss, val, ',')) val = "0";
            p.age = stoi(val);   //stoi converts the strings to ints because stringstream reads all values as a string

           
            if (!getline(ss, val, ',')) val = "";
            p.disease = val;

            
            if (!getline(ss, val, ',')) val = "";
            p.bloodGroup = val;

            
            if (!getline(ss, val, ',')) val = "";
            p.admissionDate = val;


            if (getline(ss, val, ',')) {
                p.totalBill = val.empty() ? 0.0 : stod(val);  //ternary operator to make things compact
            } else {
                p.totalBill = 0.0;
            }

            patients[patientCount] = p;
            patientCount++;
        }

        file.close();

        for (int i = 0; i < patientCount; i++) {
            cout << "patients ID: " << patients[i].patientID << "\n"
                 << "name: " << patients[i].name << "\n"
                 << "age: " << patients[i].age << "\n"
                 << "disease: " << patients[i].disease << "\n"
                 << "blood group: " << patients[i].bloodGroup << "\n"
                 << "date of admission: " << patients[i].admissionDate << "\n"
                 << "total bill for stay: $" << patients[i].totalBill << "\n";
                 cout<<endl;
        }
        cout << "--------------------------------------------------------------------------------\n";
        return 0;
    }

    void savePatients() {
        ofstream file(FILENAME);
        if (!file.is_open()) {
            cout << "Error: Could not save data to file.\n";
            return;
        }
        for (int i = 0; i < patientCount; i++) {    //saves data to the csv file and separates them by commas beforehand
            file << patients[i].patientID << ","
                 << patients[i].name << ","
                 << patients[i].age << ","
                 << patients[i].disease << ","
                 << patients[i].bloodGroup << ","
                 << patients[i].admissionDate << ","
                 << patients[i].totalBill << "\n";
        }
        file.close();
    }

    void PateintInfo() {
        int searchID;
        cout << "\nEnter Patient ID to search: ";
        cin >> searchID;

        for (int i = 0; i < patientCount; i++) {
            if (patients[i].patientID == searchID) {
                cout << "\n--- Patient Details ---\n";
                cout << "ID: " << patients[i].patientID << "\n";
                cout << "Name: " << patients[i].name << "\n";
                cout << "Age: " << patients[i].age << "\n";
                cout << "Disease: " << patients[i].disease << "\n";
                cout << "Blood Group: " << patients[i].bloodGroup << "\n";
                cout << "Admission Date: " << patients[i].admissionDate << "\n";
                cout << "Current Bill: $" << patients[i].totalBill << "\n";
                cout<<endl;
                return;
            }
        }
        cout << "Patient with ID " << searchID << " not found.\n";
    }

    void dischargePatient() {
        int dischargeID;
        cout << "\nEnter Patient ID to discharge: ";
        cin >> dischargeID;

        for (int i = 0; i < patientCount; i++) {
            if (patients[i].patientID == dischargeID) {
                cout << "Patient " << patients[i].name << " found.\n";

                int daysStayed;
                cout << "Enter total number of days stayed: ";
                cin >> daysStayed;
                patients[i].totalBill = daysStayed * RATE_PER_DAY;

                cout << "Final Bill Generated: $" << patients[i].totalBill << "\n";
                cout << "Patient successfully discharged.\n";

                for (int j = i; j < patientCount - 1; j++) {    // deletes the memory of given patient and moves the rest up
                    patients[j] = patients[j + 1];  //the entries below the pateint are moved up
                }
                patientCount--;
                savePatients(); // Updates the record by rewriting whole file, and excludes the discharged one because it doesnt exist in memory again
                return;
            }
        }
        cout << "Patient with ID " << dischargeID << " not found.\n";
    }

    void admitPatient() {
        if (patientCount >= TOTAL_HOSPITAL_BEDS) {
            cout << "Sorry, no beds available for new admissions.\n";
            return;
        }

        Patient p;
        cout << "\n--- Admit New Patient ---\n";
        cout << "Enter Patient ID: ";
        cin >> p.patientID;
        cin.ignore();

        for (int i = 0; i < patientCount; i++) {
            if (patients[i].patientID == p.patientID) {
                cout << "Error: Patient ID already exists!\n";
                return;
            }
        }

        cout << "Enter Name: ";
        getline(cin, p.name);

        cout << "Enter Age: ";
        while (!(cin >> p.age)) {
            cout << "Invalid input. enter a number illiterate\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cin.ignore(1000, '\n');
        cout << "Enter Disease: ";
        getline(cin, p.disease);
        cout << "Enter Blood Group: ";
        getline(cin, p.bloodGroup);
        cout << "Enter Date of Admission (DD-MM-YYYY): ";
        getline(cin, p.admissionDate);

        p.totalBill = 0.0;

        patients[patientCount] = p;
        patientCount++;

        savePatients();
        cout << "Patient " << p.name << " admitted successfully.\n";
    }

    void availableBeds() {
        int available = TOTAL_HOSPITAL_BEDS - patientCount;
        cout << "\n--- Bed Availability ---\n";
        cout << "Total Beds: " << TOTAL_HOSPITAL_BEDS << "\n";
        cout << "Occupied Beds: " << patientCount << "\n";
        cout << "Available Beds: " << available << "\n";
    }

    void BillOfPatient() {
        int searchID;
        cout << "\nEnter Patient ID to generate bill: ";
        cin >> searchID;

        for (int i = 0; i < patientCount; i++) {
            if (patients[i].patientID == searchID) {
                int daysStayed;
                cout << "Patient Name: " << patients[i].name << "\n";
                cout << "Admission Date: " << patients[i].admissionDate << "\n";
                cout << "Enter number of days stayed so far: ";
                cin >> daysStayed;

                patients[i].totalBill = daysStayed * RATE_PER_DAY;
                savePatients();

                cout << "Total bill calculated: $" << patients[i].totalBill << "\n";
                return;
            }
        }
        cout << "Patient with ID " << searchID << " not found.\n";
    }
};

int patientModule() {
    PatientManager hospital;
    

    int choice;
    do {
        cout<<endl;
        cout << "    HOSPITAL MANAGEMENT SYSTEM    \n";
        cout << "\n==================================\n";
        cout << " 1. Admit Patient\n";
        cout << " 2. View Patient Info\n";
        cout << " 3. Check Available Beds\n";
        cout << " 4. Calculate Patient Bill\n";
        cout << " 5. Discharge Patient\n";
        cout << " 6. show all patients.\n ";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hospital.admitPatient();
                break;
            case 2:
                hospital.PateintInfo();
                break;
            case 3:
                hospital.availableBeds();
                break;
            case 4:
                hospital.BillOfPatient();
                break;
            case 5:
                hospital.dischargePatient();
                break;
            case 6:
                hospital.displayAllPatients();
                break;
            case 7:
                cout << " wapis na ana mareez \n";
                break;
            default:
                cout << "Invalid choice. stop being illiterate.\n";
        }
    } while (choice != 7);

    return 0;
}


  #include <sstream>
#include <cstdio>
   #include<limits>
   using namespace std;
        
const string patientDetails ="patientsinfo.csv";
const string schedule= "schedule.dat";
const string notes ="notes.dat";
const string doctorsFile= "doctors.csv";
const string appointment= "appointment.dat";
  
struct AdminPatient {
    string  patientID;
    string  age;
    string name;
    string gender;
    string contact;
    string bloodGroup;
    string disease;
    string admissionDate;
    string  assignedDoctorID;
    string totalBill;
};
   
struct AdminDoctor
{
string doctorid;
string doctorName;
string speciality;
string availableDates;//11-03-2026
string contact;
string password;   
string timing;
string availability;
string experience;
}  ; 

   
struct Notes   
{
string notesID;	
string patientID;
string assignedDoctorID;
string diagnosis;
string prescription;
string Date;
};   
   
struct Appointment
{
string appointmentID;
string patientID;
string assignedDoctorID;	
string Date;
string slot;
string status;//done, booked, pending		
};   

struct Slot
{
string date;	
string slot;
string status;// check if slot open, blocked	
string doctorid;	
}  ; 
   
  
   
// Utility Functions
void printLine(char ln='-',int len=45){
for (int i=0;i<len;i++)
cout<<ln;  
cout<<"\n"; 
}

void EnterPress(){
cout<<"Press Enter to continue............";
cin.ignore();
cin.get();
}
   
   bool adminLogin() {
    string id, pass;
    cout << "ADMIN LOGIN\n";
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;

    // simple static admin check (you can replace later with file)
    if (id == "admin" && pass == "1234") {
        return true;
    }
    return false;
}

   
   
////
////    view alll patients
////   
   
void patientProfile(){
	ifstream file(patientDetails);
	if(!file)
	{cout<<"Patient File not found"<<endl;
	return;
	}
string line;
	while(getline(file,line)){
	stringstream ss(line);
	AdminPatient d;
	getline(ss,d.patientID,',');
	getline(ss,d.age,',');
	getline(ss,d.name,',');
	getline(ss,d.gender,',');
	getline(ss,d.contact,',');
	getline(ss,d.bloodGroup,',');
	getline(ss,d.disease,',');
	getline(ss,d.admissionDate,',');
	getline(ss,d.assignedDoctorID,',');
	getline(ss,d.totalBill,',');
	///print patient data
{
	cout<<"The id of patient is: "<<d.patientID<<endl;
	cout<<"Patient's age is: " <<d.age<<endl;
	cout<< "Patient Nmae is: "<<d.name<<endl;
	cout<< "Patient's gender is: "<<d.gender<<endl;
	cout<< "Patient's Contact no is: "<<d.contact<<endl;
	cout<<" Patient's blood group is: "<<d. bloodGroup<<endl;	
    cout<<"Disease: "<<d.disease<<endl;
    cout<<"Admission Date: "<<d.admissionDate<<endl;
    cout<<"Total Bill: "<<d.totalBill<<endl;
	printLine();
	
	}	
}
				
}  
  

///////view doctors

void doctorsProfile(){
	ifstream file(doctorsFile);
	if(!file)
	{cout<<"Patient File not found"<<endl;
	return;
	}
string line;
	while(getline(file,line)){
	stringstream ss(line);
	AdminDoctor d;
   getline(ss, d.doctorid, ',');
        getline(ss, d.doctorName, ',');
        getline(ss, d.speciality, ',');
        getline(ss, d.availableDates, ',');
        getline(ss, d.contact, ',');
        getline(ss, d.password, ',');
        getline(ss, d.timing, ',');
        getline(ss, d.availability, ',');
        getline(ss, d.experience, ',');

        cout << "ID: " << d.doctorid << "\n";
        cout << "Name: " << d.doctorName << "\n";
        cout << "Speciality: " << d.speciality << "\n";
        cout << "Availability: " << d.availability << "\n";
	    printLine();	
	}					
}  
/////  
 ////Check appointments
 ////
void checkAppointment  (){
int id;
cout<<"Enter id of patient to see appointments"<<endl;
cin>>id;

	ifstream file(appointment);	
  if(!file)
{cout<<"Notes file not exist"<<endl;
	return;	}
	{cout<<"No file Exists"<<endl;
	return;
	}
	string line;
	bool found =false;
	 while(getline(file,line)){
	Appointment a;
        stringstream ss(line);


        getline(ss,a.appointmentID,',');

        getline(ss,a.patientID,',');

        getline(ss,a.assignedDoctorID,',');

        getline(ss,a.Date,',');

        getline(ss,a.slot,',');

        getline(ss,a.status,',');       
if (a.patientID == to_string(id)){

    cout<<"\nAppointment ID: "<<a.appointmentID<<endl;
    cout<<"Status: "<<a.status<<endl;
	cout<< "Booked slot is: "<<a.slot<<endl;
	cout<<" Appointment date is: "<<a.Date<<endl;
	cout<<"-------------------------------------------"<<endl;
	found=true;
	}
}
	
if(!found)
{cout<<"No appointment for you"<<endl;
}
file.close();		
}
///   
///  Assignment book
///
  
void AppointmentUpdate (){
string assId;
cout<<"Enter appointment ID: "<<endl;
cin>>assId;

	ifstream file(appointment);
    ofstream out("out.csv");
	if(!file)
{cout<<"Notes file not exist"<<endl;
	return;	}
	string line;
	bool found =false;
	 while(getline(file,line)){
        stringstream ss(line);

        Appointment a;

        getline(ss,a.appointmentID,',');

        getline(ss,a.patientID,',');

        getline(ss,a.assignedDoctorID,',');

        getline(ss,a.Date,',');

        getline(ss,a.slot,',');

        getline(ss,a.status,','); 

if (a.appointmentID==assId)	
{
a.status="confirmed";
found=true;
}


 out<<a.appointmentID<<","
    <<a.patientID<<","
    <<a.assignedDoctorID<<","
    <<a.Date<<","
    <<a.slot<<","
    <<a.status<<"\n";
}

file.close();
out.close();

remove("appointment.dat");
rename("out.csv","appointment.dat");
 
  if(found)
cout<<"No appointment booked";

else
cout<<"appointment booked";	
}
  
////
///Notes
/// 

 
 void addnotes(){
 Notes n;
 string ID;	
 cout<<"Enter Patient Id"<<endl;
 cin>>ID;
 n.patientID = ID;
 cout<<" Notes ID"<<endl;
 cin>>n.notesID;
 cin.ignore();
 cout<<"Disease diagnosis "<<endl; 
 cin>> n.diagnosis;
 cout<<"prescription is "<<endl;
 cin>>n.prescription;

  cout<<"Date is "<<  n.Date<<endl;
 cin>>n.Date;
	ofstream infile(notes,ios::app);
	 infile<<n.notesID<<","
        <<n.patientID<<","
        <<n.diagnosis<<","
        <<n.prescription<<","
        <<n.Date<<"\n";

    infile.close();

    cout<<"Notes Saved.\n";  
  if(!infile)
{cout<<"Notes file not exist"<<endl;
	return;	}
			infile.close();
cout<<"Notes saved"<<endl;
} 
  
  
 //
 /// view notes
 /// 
  
    
 
void viewNotes  (){
int id;
cout<<"Enter id of patient"<<endl;
cin>>id;
	ifstream file(notes);	
	if(!file)
	{cout<<"No notes exists"<<endl;
	return;
	}
	    string line;

    bool found=false;

    while(getline(file,line)){

        stringstream ss(line);

        Notes n;

        getline(ss,n.notesID,',');

        getline(ss,n.patientID,',');

        getline(ss,n.assignedDoctorID,',');

        getline(ss,n.diagnosis,',');

        getline(ss,n.prescription,',');

        getline(ss,n.Date,',');
if (n.patientID == to_string(id))	
{
	cout<< "Patient ID is: "<<n.patientID<<endl;
	cout<<"Disease diagnosis: "<< n.diagnosis <<endl; 
    cout<<"prescription is "<<n.prescription<<endl;
	cout<<" Appointment date is: "<<n.Date<<endl;
	printLine();
	found=true;
}
}
if(!found)
{cout<<"No saved notes here"<<endl;
}
file.close();		
}
  
  

 
     void adminModule  (){
     	printLine();
     	cout<<"----------Admin Module------------"<<endl;
     	printLine();
     	int choice;
     	
do{
cout<<"1: View Patients Profile"<<endl;
cout<<"2: Check Appointments"<<endl;
cout<<"3: Confirm Appointments"<<endl;
cout<<"4: Add Notes "<<endl;
cout<<"5: View notes"<<endl;

cout<<"choice==0  Logout"<<endl;
cout<<"Enter choice"<<endl;	
cin>>choice;     	     		
switch(choice){
	case 1:
    patientProfile();
	break;  	     	 		     		
    case 2:
	checkAppointment  () ;	     	
    break;  	
    case 3:
	AppointmentUpdate ();
	break; 	
    case 4:
	addnotes();
	break;
	case 5: 	
    viewNotes  ();
	break;
	case 0:
	cout<<"Exiting Module......" <<endl;
	break;
	default:
	cout<<"Invalid Choice!"<<endl;	
	 }
if (choice!=0){
	EnterPress();
}	 
	 
}while(choice!=0);
}



int choice;
int main(){
    cout<<"welcome to Malik Basheer hospital."<<endl;
    cout<<"enter your identity: "<<endl;
    cout<< "1. patient"<<endl;
    cout<< "2. doctor"<<endl;
    cout<< "3. admin staff"<<endl;
    cout<<"enter identity and actions accordingly:  ";

cin>>choice;
switch (choice){
    case 1:
        patientModule();
        break;
    case 2:
        doctorMenu();
        break;
    case 3:
        adminModule();
        break;
    default:
        cout<<"invalid response, stop being brainless";
}
}
