#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
#include <sstream>
using namespace std;

// ============================================================
//   STRUCTURES
// ============================================================

struct Doctor {
    string id;
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
    int age;
    string disease;
    string bloodGroup;
    string admissionDate;
    double totalBill;
};

// Notes are written by doctors only
struct Notes {
    string notesID;
    string doctorID;
    string patientID;
    string diagnosis;
    string prescription;
    string date;
};

struct Appointment {
    string appointmentID;
    string patientID;
    string doctorID;
    string date;
    string slot;
    string status;  // "pending" | "confirmed"
};

// ============================================================
//   FILE CONSTANTS
// ============================================================

const string PATIENTS_FILE    = "patientsinfo.csv";
const string NOTES_FILE       = "notes.dat";
const string DOCTORS_FILE     = "doctors.csv";
const string APPOINTMENT_FILE = "appointment.dat";

// ============================================================
//   SHARED DOCTOR ARRAY  (loaded once, used by all modules)
// ============================================================

Doctor* doctors   = nullptr;
int     doctorCount = 0;

// ============================================================
//   UTILITY
// ============================================================

void printLine(char c = '-', int len = 50) {
    for (int i = 0; i < len; i++) cout << c;
    cout << "\n";
}

void EnterPress() {
    cout << "\nPress Enter to continue...";
    if (cin.peek() == '\n') cin.ignore();
    cin.get();
}

// Reads an integer strictly within [min, max]
int getValidChoice(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid! Enter a number " << min << "-" << max << ": ";
        } else if (choice < min || choice > max) {
            cout << "Out of range! Enter " << min << "-" << max << ": ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

bool validName(const string& name) {
    if (name.empty()) return false;
    if (name.front() == ' ' || name.back() == ' ') return false;
    for (int i = 0; i < (int)name.size(); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') return false; // alphabets and space 
        if (i + 1 < (int)name.size() && name[i] == ' ' && name[i+1] == ' ') return false; // prevents double spaces
    }
    return true;
}

string generateID(const string& prefix, const string& filename) {
    ifstream f(filename);
    int count = 0;
    string line;
    while (getline(f, line)) if (!line.empty()) count++;
    f.close();
    string id = prefix;
    int num = count + 1;
    if (num < 10)        id += "00" + to_string(num);
    else if (num < 100)  id += "0"  + to_string(num);
    else                 id +=         to_string(num);
    return id;
}

// ============================================================
//   SHARED: LOAD / SAVE DOCTORS
// ============================================================

void loadDoctors() {
    delete[] doctors;
    doctors = nullptr; //not pointing to anything
    doctorCount = 0;

    ifstream file(DOCTORS_FILE);
    if (!file) return;  // no file yet

    // Count non-empty lines
    string line;
    int lineCount = 0;
    while (getline(file, line)) if (!line.empty()) lineCount++;
    if (lineCount == 0) { file.close(); return; }

    doctors = new Doctor[lineCount];
    file.clear();
    file.seekg(0);

    for (int i = 0; i < lineCount; i++) {
        getline(file, doctors[i].id,             ',');
        getline(file, doctors[i].name,           ',');
        getline(file, doctors[i].specialization, ',');
        getline(file, doctors[i].department,     ',');
        getline(file, doctors[i].timing,         ',');
        getline(file, doctors[i].availability,   ',');
        getline(file, doctors[i].experience);
        doctorCount++;
    }
    file.close();
}

void saveDoctors() {
    ofstream file(DOCTORS_FILE);
    if (!file) { cout << "Error saving doctors!\n"; return; }
    for (int i = 0; i < doctorCount; i++) {
        file << doctors[i].id             << ","
             << doctors[i].name           << ","
             << doctors[i].specialization << ","
             << doctors[i].department     << ","
             << doctors[i].timing         << ","
             << doctors[i].availability   << ","
             << doctors[i].experience     << "\n";
    }
    file.close();
}

// ============================================================
//   PATIENT LOOKUP
//   Used by doctor module (notes) to validate patient exists.
// ============================================================

bool patientExists(const string& pid) {
    ifstream file(PATIENTS_FILE);
    if (!file) return false;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id;
        getline(ss, id, ','); //read from ss until u reach a coma then add to id
        if (id == pid) { file.close(); return true; }
    }
    file.close();
    return false;
}

// ============================================================
//   DOCTOR MODULE — selection helpers
// ============================================================

string selectSpecialization() {
    cout << "\n--- Specialization ---\n"
         << "1.Cardiologist\n2.Neurologist\n3.Dermatologist\n4.Orthopedic Surgeon\n"
         << "5.Pediatrician\n6.General Physician\n7.ENT Specialist\n8.Gynecologist\n"
         << "9.Psychiatrist\n10.Radiologist\nChoice: ";
    switch (getValidChoice(1, 10)) {
        case 1:  return "Cardiologist";
        case 2:  return "Neurologist";
        case 3:  return "Dermatologist";
        case 4:  return "Orthopedic Surgeon";
        case 5:  return "Pediatrician";
        case 6:  return "General Physician";
        case 7:  return "ENT Specialist";
        case 8:  return "Gynecologist";
        case 9:  return "Psychiatrist";
        case 10: return "Radiologist";
        default: return "Invalid";
    }
}

string selectDepartment() {
    cout << "\n--- Department ---\n"
         << "1.Cardiology\n2.Neurology\n3.Orthopedics\n4.Pediatrics\n5.Emergency\n"
         << "6.Surgery\n7.Radiology\n8.OPD\n9.ICU\n10.Administration\nChoice: ";
    switch (getValidChoice(1, 10)) {
        case 1:  return "Cardiology";
        case 2:  return "Neurology";
        case 3:  return "Orthopedics";
        case 4:  return "Pediatrics";
        case 5:  return "Emergency";
        case 6:  return "Surgery";
        case 7:  return "Radiology";
        case 8:  return "OPD";
        case 9:  return "ICU";
        case 10: return "Administration";
        default: return "Invalid";
    }
}

string selectAvailability() {
    cout << "\n1.Available  2.Busy\nChoice: ";
    switch (getValidChoice(1, 2)) {
        case 1: return "Available";
        case 2: return "Busy";
        default: return "Invalid";
    }
}

string selectExperience() {
    cout << "\n1.1-2 Years\n2.3-5 Years\n3.5-10 Years\n4.10+ Years\nChoice: ";
    switch (getValidChoice(1, 4)) {
        case 1: return "1-2 Years";
        case 2: return "3-5 Years";
        case 3: return "5-10 Years";
        case 4: return "10+ Years";
        default: return "Invalid";
    }
}

string selectTiming() {
    cout << "\n1. 08:00 AM - 12:00 PM\n2. 12:00 PM - 04:00 PM\n"
         << "3. 04:00 PM - 08:00 PM\n4. 08:00 PM - 12:00 AM\n5. 24 Hours\nChoice: ";
    switch (getValidChoice(1, 5)) {
        case 1: return "08:00 AM - 12:00 PM";
        case 2: return "12:00 PM - 04:00 PM";
        case 3: return "04:00 PM - 08:00 PM";
        case 4: return "08:00 PM - 12:00 AM";
        case 5: return "24 Hours";
        default: return "Invalid";
    }
}

// ============================================================
//   DOCTOR MODULE
// ============================================================

string getValidDoctorID() {
    string id;
    while (true) {
        cout << "Doctor ID (letters/numbers only): ";
        getline(cin, id);
        if (id.empty()) { cout << "ID cannot be empty.\n"; continue; }
        bool ok = true;
        for (char c : id) if (!isalnum(c)) { ok = false; break; }
        if (!ok) { cout << "Only letters and numbers allowed.\n"; continue; }
        bool exists = false;
        for (int i = 0; i < doctorCount; i++) if (doctors[i].id == id) { exists = true; break; }
        if (exists) { cout << "ID already taken.\n"; continue; }
        return id;
    }
}

void addDoctor() {
    cout << "\n===== ADD DOCTOR =====\n";
    Doctor d;
    d.id = getValidDoctorID();

    cout << "Name: ";
    getline(cin, d.name);
    if (!validName(d.name)) { cout << "Invalid name.\n"; return; }

    d.specialization = selectSpecialization(); 
    if (d.specialization == "Invalid") return;
    d.department     = selectDepartment();
    if (d.department     == "Invalid") return;
    d.timing         = selectTiming();
    if (d.timing         == "Invalid") return;
    d.availability   = selectAvailability();  
    if (d.availability   == "Invalid") return;
    d.experience     = selectExperience();    
    if (d.experience     == "Invalid") return;

    Doctor* temp = new Doctor[doctorCount + 1]; //dynamic memory allocation
    for (int i = 0; i < doctorCount; i++) temp[i] = doctors[i];
    temp[doctorCount] = d;
    delete[] doctors; //remove preivous array data
    doctors = temp;
    doctorCount++;
    saveDoctors();
    cout << "Doctor added.\n";
}

void viewDoctors() {
    if (doctorCount == 0) { cout << "No doctors in system.\n"; return; }
    cout << "\n===== DOCTORS (" << doctorCount << ") =====\n";
    for (int i = 0; i < doctorCount; i++) {
        cout << "\n[" << (i+1) << "] ID: " << doctors[i].id
             << "  Name: "           << doctors[i].name
             << " \nSpecialization: "           << doctors[i].specialization
             << " \nDepartment: "           << doctors[i].department
             << " \nTiming: "         << doctors[i].timing
             << " \nStatus: "         << doctors[i].availability
             << " \nExperience: "            << doctors[i].experience << "\n";
    }
}

void searchDoctor() {
    if (doctorCount == 0) { cout << "No doctors in system.\n"; return; }
    cout << "Enter Doctor ID: ";
    string id; getline(cin, id);
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == id) {
            printLine();
            cout << "ID: "             << doctors[i].id
                 << "\nName: "         << doctors[i].name
                 << "\nSpecialization: " << doctors[i].specialization
                 << "\nDepartment: "   << doctors[i].department
                 << "\nTiming: "       << doctors[i].timing
                 << "\nAvailability: " << doctors[i].availability
                 << "\nExperience: "   << doctors[i].experience << "\n";
            printLine();
            return;
        }
    }
    cout << "Doctor '" << id << "' not found.\n";
}

void updateDoctor() {
    if (doctorCount == 0) { cout << "No doctors in system.\n"; return; }
    cout << "Enter Doctor ID to update: ";
    string id; getline(cin, id);
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == id) {
            char c;
            cout << "\nCurrent: " << doctors[i].name << " | " << doctors[i].specialization
                 << " | " << doctors[i].availability << "\n";

            cout << "Change Name? (y/n): "; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c=='y'||c=='Y') {
                string t; cout << "New name: "; getline(cin, t);
                if (validName(t)) doctors[i].name = t; else cout << "Invalid, skipped.\n";
            }
            cout << "Change Specialization? (y/n): "; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c=='y'||c=='Y') { string t=selectSpecialization(); if(t!="Invalid") doctors[i].specialization=t; }

            cout << "Change Department? (y/n): "; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c=='y'||c=='Y') { string t=selectDepartment(); if(t!="Invalid") doctors[i].department=t; }

            cout << "Change Timing? (y/n): "; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c=='y'||c=='Y') { string t=selectTiming(); if(t!="Invalid") doctors[i].timing=t; }

            cout << "Change Availability? (y/n): "; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c=='y'||c=='Y') { string t=selectAvailability(); if(t!="Invalid") doctors[i].availability=t; }

            cout << "Change Experience? (y/n): "; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c=='y'||c=='Y') { string t=selectExperience(); if(t!="Invalid") doctors[i].experience=t; }

            saveDoctors();
            cout << "Doctor updated.\n";
            return;
        }
    }
    cout << "Doctor '" << id << "' not found.\n";
}

void deleteDoctor() {
    if (doctorCount == 0) { cout << "No doctors in system.\n"; return; }
    cout << "Enter Doctor ID to delete: ";
    string id; getline(cin, id);
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == id) {
            cout << "Delete " << doctors[i].name << "? (y/n): ";
            char c; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c=='y'||c=='Y') {
                for (int j = i; j < doctorCount-1; j++) doctors[j] = doctors[j+1];
                doctorCount--;
                saveDoctors();
                cout << "Doctor deleted.\n";
            } else {
                cout << "Cancelled.\n";
            }
            return;
        }
    }
    cout << "Doctor '" << id << "' not found.\n";
}

// ------------------------------------------------------------------
//   DOCTOR NOTES
// ------------------------------------------------------------------
void addPatientNotes(const string& loggedDoctorID) {
    cout << "\n===== ADD PATIENT NOTES =====\n";

    // Validate patient exists before writing anything
    cout << "Enter Patient ID: ";
    string pid; getline(cin, pid);

    if (!patientExists(pid)) {
        cout << "Patient ID '" << pid << "' not found in system. Notes not saved.\n";
        return;
    }

    Notes n;
    n.notesID   = generateID("NOTE", NOTES_FILE);
    n.doctorID  = loggedDoctorID;
    n.patientID = pid;

    cout << "Diagnosis: ";
    getline(cin, n.diagnosis);
    if (n.diagnosis.empty()) { cout << "Diagnosis cannot be empty.\n"; return; }

    cout << "Prescription: ";
    getline(cin, n.prescription);
    if (n.prescription.empty()) { cout << "Prescription cannot be empty.\n"; return; }

    cout << "Date (DD-MM-YYYY): ";
    getline(cin, n.date);

    ofstream file(NOTES_FILE, ios::app);
    if (!file) { cout << "Error: Could not open notes file.\n"; return; }

    file << n.notesID      << ","
         << n.doctorID     << ","
         << n.patientID    << ","
         << n.diagnosis    << ","
         << n.prescription << ","
         << n.date         << "\n";
    file.close();

    cout << "Notes saved (ID: " << n.notesID << ").\n";
}

void viewPatientNotes(const string& filterDoctorID = "") {
    // If filterDoctorID is empty, shows all notes (admin use). // removed admin viewnotes option 
    cout << "Enter Patient ID to view notes: ";
    string pid; getline(cin, pid);

    ifstream file(NOTES_FILE);
    if (!file) { cout << "No notes on file.\n"; return; }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Notes n;
        stringstream ss(line);
        getline(ss, n.notesID,      ',');
        getline(ss, n.doctorID,     ',');
        getline(ss, n.patientID,    ',');
        getline(ss, n.diagnosis,    ',');
        getline(ss, n.prescription, ',');
        getline(ss, n.date,         ',');

        if (n.patientID != pid) continue;
        if (!filterDoctorID.empty() && n.doctorID != filterDoctorID) continue;

        printLine();
        cout << "Notes ID:     " << n.notesID      << "\n"
             << "Doctor ID:    " << n.doctorID      << "\n"
             << "Patient ID:   " << n.patientID     << "\n"
             << "Diagnosis:    " << n.diagnosis     << "\n"
             << "Prescription: " << n.prescription  << "\n"
             << "Date:         " << n.date          << "\n";
        found = true;
    }
    file.close();
    if (!found) cout << "No notes found for patient '" << pid << "'.\n";
}


void viewMyPatients(const string& doctorID) {
    ifstream file(APPOINTMENT_FILE);
    if (!file) {
        cout << "No appointments found.\n";
        return;
    }

    cout << "\n===== MY PATIENTS =====\n";

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        Appointment a;
        stringstream ss(line);

        getline(ss, a.appointmentID, ',');
        getline(ss, a.patientID, ',');
        getline(ss, a.doctorID, ',');
        getline(ss, a.date, ',');
        getline(ss, a.slot, ',');
        getline(ss, a.status, ',');

        if (a.doctorID != doctorID) continue;

        cout << "Patient ID: " << a.patientID
             << " | Date: " << a.date
             << " | Slot: " << a.slot
             << " | Status: " << a.status << "\n";

        found = true;
    }

    file.close();

    if (!found)
        cout << "No patients found for you.\n";
}

// ------------------------------------------------------------------
//   DOCTOR MENU  (As Doctor Ya Doctor Manager if no id selected)
// ------------------------------------------------------------------
void doctorMenu() {
    loadDoctors();

    // Ask which doctor is logging in
    cout << "\n===== DOCTOR LOGIN =====\n";
    cout << "Enter your Doctor ID: ";
    string myID; getline(cin, myID);

    bool found = false;
    string myName;
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == myID) { found = true; myName = doctors[i].name; break; }
    }

    // If ID not found, offer to continue as admin/manager who can still manage records
    if (!found) {
        cout << "Doctor ID not found. Continue as doctor manager (no notes)? (y/n): ";
        char c; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (c != 'y' && c != 'Y') return;
        myID = "";  // blank = no notes allowed
    } else {
        cout << "Welcome, Dr. " << myName << ".\n";
    }

    int choice;
    do {
        cout << "\n===== DOCTOR MENU =====\n"
             << "1. Add Doctor Record\n"
             << "2. View All Doctors\n"
             << "3. Search Doctor\n"
             << "4. Update Doctor\n"
             << "5. Delete Doctor\n";
        if (!myID.empty()) {
            cout << "6. Add Patient Notes\n"
                << "7. View My Patient Notes\n"
                << "8. View My Patients\n";
        }       
        cout << "0. Back\nChoice: ";

        int maxChoice = myID.empty() ? 5 : 8;
        choice = getValidChoice(0, maxChoice);

        switch (choice) {
            case 1: addDoctor();   break;
            case 2: viewDoctors(); break;
            case 3: searchDoctor(); break;
            case 4: updateDoctor(); break;
            case 5: deleteDoctor(); break;
            case 6: if (!myID.empty()) addPatientNotes(myID);   break;
            case 7: if (!myID.empty()) viewPatientNotes(myID);  break;
            case 8: if (!myID.empty()) viewMyPatients(myID);  break;
            case 0: cout << "Returning...\n"; break;
        }if (choice != 0) EnterPress();
    } while (choice != 0);
}



// ============================================================
//   PATIENT MODULE
// ============================================================

struct PatientManager {
  int TOTAL_HOSPITAL_BEDS = 20;
    Patient patients[20];

    double RATE_PER_DAY = 500.0;
    int patientCount = 0;

    int loadPatients() {
        // Load patients from CSV 
        ifstream file(PATIENTS_FILE);
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
        return 0;

    }


    void savePatients() {
        ofstream file(PATIENTS_FILE);
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

    void displayAllPatients() {
        loadPatients();
        if (patientCount == 0) { cout << "No patients admitted.\n"; return; }
        cout << "\n===== PATIENTS (" << patientCount << "/" << TOTAL_HOSPITAL_BEDS << " beds) =====\n";
        for (int i = 0; i < patientCount; i++) {
            cout << "ID:"       << patients[i].patientID
                 << " \n Name:"  << patients[i].name
                 << " \n Age:"   << patients[i].age
                 << " \n Disease:" << patients[i].disease
                 << " \n Blood:" << patients[i].bloodGroup
                 << " \n Admitted:" << patients[i].admissionDate
                 << " \n Bill:$" << patients[i].totalBill << "\n";
        }
    }

    void showMyInfo(int myID) {
    loadPatients();

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].patientID == myID) {
            cout << "\n--- Patient Details ---\n";
            cout << "ID: " << patients[i].patientID << "\n";
            cout << "Name: " << patients[i].name << "\n";
            cout << "Age: " << patients[i].age << "\n";
            cout << "Disease: " << patients[i].disease << "\n";
            cout << "Blood Group: " << patients[i].bloodGroup << "\n";
            cout << "Admission Date: " << patients[i].admissionDate << "\n";
            cout << "Current Bill: $" << patients[i].totalBill << "\n";
            return;
        }
    }

    cout << "Patient not found.\n";
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

    void billOfPatient() {
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


    void dischargePatient() {
        loadPatients();
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

    // ------------------------------------------------------------------
    //   BOOK APPOINTMENT
    // ------------------------------------------------------------------
    void bookAppointment(int myPatientID) {
        // Always pull fresh doctor data
        loadDoctors();

        int availIdx[100];
        int availCount = 0;
        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i].availability == "Available") availIdx[availCount++] = i;
        }

        if (availCount == 0) {
            cout << "No available doctors right now. Please check back later.\n";
            return;
        }

        cout << "\n===== AVAILABLE DOCTORS =====\n";
        for (int i = 0; i < availCount; i++) {
            int idx = availIdx[i];
            cout << "[" << (i+1) << "] "
                 << doctors[idx].name << " — "
                 << doctors[idx].specialization << " | "
                 << doctors[idx].department     << " | "
                 << doctors[idx].timing         << "\n";
        }

        cout << "\nSelect doctor (1-" << availCount << "): ";
        int pick = getValidChoice(1, availCount);
        string chosenDoctorID = doctors[availIdx[pick-1]].id;
        string chosenDoctorName = doctors[availIdx[pick-1]].name;

        cout << "Enter appointment date (DD-MM-YYYY): ";
        string date; getline(cin, date);

        cout << "\nSelect time slot:\n"
             << "1. 08:00 AM - 10:00 AM\n"
             << "2. 10:00 AM - 12:00 PM\n"
             << "3. 12:00 PM - 02:00 PM\n"
             << "4. 02:00 PM - 04:00 PM\n"
             << "5. 04:00 PM - 06:00 PM\n"
             << "Choice: ";
        string slot;
        switch (getValidChoice(1, 5)) {
            case 1: slot = "08:00-10:00"; break;
            case 2: slot = "10:00-12:00"; break;
            case 3: slot = "12:00-14:00"; break;
            case 4: slot = "14:00-16:00"; break;
            case 5: slot = "16:00-18:00"; break;
        }

        Appointment a;
        a.appointmentID = generateID("APT", APPOINTMENT_FILE);
        a.patientID     = to_string(myPatientID);
        a.doctorID      = chosenDoctorID;
        a.date          = date;
        a.slot          = slot;
        a.status        = "Pending";

        ofstream file(APPOINTMENT_FILE, ios::app);
        if (!file) { cout << "Error saving appointment.\n"; return; }
        file << a.appointmentID << ","
             << a.patientID     << ","
             << a.doctorID      << ","
             << a.date          << ","
             << a.slot          << ","
             << a.status        << "\n";
        file.close();

        cout << "\nAppointment booked!\n"
             << "  ID:     " << a.appointmentID   << "\n"
             << "  Doctor: Dr. " << chosenDoctorName << "\n"
             << "  Date:   " << a.date             << "\n"
             << "  Slot:   " << a.slot             << "\n"
             << "  Status: Pending (awaiting admin confirmation)\n";
    }

    void viewMyAppointments(int myPatientID) {
        ifstream file(APPOINTMENT_FILE);
        if (!file) { cout << "No appointments on file.\n"; return; }
        string pid = to_string(myPatientID);
        string line;
        bool found = false;
        cout << "\n===== YOUR APPOINTMENTS =====\n";
        while (getline(file, line)) {
            if (line.empty()) continue;
            Appointment a;
            stringstream ss(line);
            getline(ss, a.appointmentID, ',');
            getline(ss, a.patientID,     ',');
            getline(ss, a.doctorID,      ',');
            getline(ss, a.date,          ',');
            getline(ss, a.slot,          ',');
            getline(ss, a.status,        ',');
            if (a.patientID != pid) continue;

            // Look up doctor name from loaded array
            string docName = a.doctorID;
            for (int i = 0; i < doctorCount; i++) {
                if (doctors[i].id == a.doctorID) { docName = doctors[i].name; break; }
            }

            cout << "Appt ID: " << a.appointmentID
                 << " | Doctor: Dr." << docName
                 << " | Date: " << a.date
                 << " | Slot: " << a.slot
                 << " | Status: " << a.status << "\n";
            found = true;
        }
        file.close();
        if (!found) cout << "No appointments found.\n";
    }
};

PatientManager hospital;

void patientModule() {
    // Patient identifies themselves by ID first
    hospital.loadPatients();
    cout << "\n===== PATIENT LOGIN =====\n";
    cout << "Enter your Patient ID (or 0 to go back): ";
    int myID; cin >> myID; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (myID == 0) return;

    // Verify patient exists
    bool found = false;
    string myName;
    for (int i = 0; i < hospital.patientCount; i++) {
        if (hospital.patients[i].patientID == myID) {
            found = true;
            myName = hospital.patients[i].name;
            break;
        }
    }
    if (!found) {
        cout << "Patient ID not found. Please ask admin to register you first.\n";
        return;
    }
    cout << "Welcome, " << myName << ".\n";

    int choice;
    do {
        cout << "\n===== PATIENT MENU =====\n"
             << "1. View My Info\n"
             << "2. Book Appointment\n"
             << "3. View My Appointments\n"
             << "0. Back\nChoice: ";
        choice = getValidChoice(0, 3);
        switch (choice) {
            case 1: hospital.showMyInfo(myID);                        break;
            case 2: hospital.bookAppointment(myID);       break;
            case 3: hospital.viewMyAppointments(myID);    break;
            case 0: cout << "Goodbye, " << myName << ".\n"; break;
        }if (choice != 0) EnterPress();
    } while (choice != 0);
}

// ============================================================
//   ADMIN MODULE
// ============================================================

void adminViewAllPatients()     { hospital.displayAllPatients(); }

void adminAdmitPatient()        { hospital.admitPatient(); }
void adminDischargePatient()    { hospital.dischargePatient(); }
void adminCalculateBill()       { hospital.billOfPatient(); }

void adminCheckAppointments() {
    cout << "Filter by Patient ID (0 = show all): ";
    int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ifstream file(APPOINTMENT_FILE);
    if (!file) { cout << "No appointments on file.\n"; return; }

    loadDoctors();  // need doctor names
    string line;
    bool found = false;
    cout << "\n===== APPOINTMENTS =====\n";
    while (getline(file, line)) {
        if (line.empty()) continue;
        Appointment a;
        stringstream ss(line);
        getline(ss, a.appointmentID, ',');
        getline(ss, a.patientID,     ',');
        getline(ss, a.doctorID,      ',');
        getline(ss, a.date,          ',');
        getline(ss, a.slot,          ',');
        getline(ss, a.status,        ',');

        if (id != 0 && a.patientID != to_string(id)) continue;

        string docName = a.doctorID;
        for (int i = 0; i < doctorCount; i++)
            if (doctors[i].id == a.doctorID) { docName = doctors[i].name; break; }

        cout << "ID:" << a.appointmentID
             << " | Patient:" << a.patientID
             << " | Doctor:Dr." << docName
             << " | Date:" << a.date
             << " | Slot:" << a.slot
             << " | Status:" << a.status << "\n";
        found = true;
    }
    file.close();
    if (!found) cout << "No appointments found.\n";
}

void adminConfirmAppointment() {
    cout << "Enter Appointment ID to confirm: ";
    string assId; getline(cin, assId);

    ifstream file(APPOINTMENT_FILE);
    if (!file) { cout << "Appointment file not found.\n"; return; }
    ofstream out("temp_apt.csv"); //can't edit middle of csv file thats why temp used

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Appointment a;
        stringstream ss(line);
        getline(ss, a.appointmentID, ',');
        getline(ss, a.patientID,     ',');
        getline(ss, a.doctorID,      ',');
        getline(ss, a.date,          ',');
        getline(ss, a.slot,          ',');
        getline(ss, a.status,        ',');

        if (a.appointmentID == assId) {
            if (a.status == "confirmed") {
                cout << "Already confirmed.\n";
            } else {
                a.status = "confirmed";
                found = true;
            }
        }
        out << a.appointmentID << "," << a.patientID << ","
            << a.doctorID      << "," << a.date       << ","
            << a.slot          << "," << a.status      << "\n";
    }
    file.close(); out.close();
    remove(APPOINTMENT_FILE.c_str());
    rename("temp_apt.csv", APPOINTMENT_FILE.c_str());

    if (found) cout << "Appointment " << assId << " confirmed.\n";
    else       cout << "Appointment '" << assId << "' not found.\n";
}


void adminCheckBeds() {
    hospital.availableBeds();
}

void adminModule() {
    printLine('=');
    cout << "          ADMIN MODULE\n";
    printLine('=');
    int choice;
    do {
        cout << "\n--- Patient Management ---\n"
             << "1. View All Patients\n"
             << "2. Admit Patient\n"
             << "3. Discharge Patient\n"
             << "4. Calculate Bill\n"
             << "5. Bed Availability\n"
             << "--- Appointments ---\n"
             << "6. View All Appointments\n"
             << "7. Confirm Appointment\n"
             << "--- Notes ---\n"
             << "8. View Patient Notes\n"
             << "0. Logout\nChoice: ";
             
        choice = getValidChoice(0, 8);
        switch (choice) {
            case 1: adminViewAllPatients();      break;
            case 2: adminAdmitPatient();         break;
            case 3: adminDischargePatient();     break;
            case 4: adminCalculateBill();        break;
            case 5: adminCheckBeds();            break;
            case 6: adminCheckAppointments();    break;
            case 7: adminConfirmAppointment();   break;
            case 8: viewPatientNotes("");        break;  // empty = show all doctors' notes
            case 0: cout << "Logged out.\n";    break;
        }
        if (choice != 0) EnterPress();
    } while (choice != 0);
}



// ============================================================
//   MAIN
// ============================================================

int main() {
    printLine('=');
    cout << "    MALIK BASHEER HOSPITAL MANAGEMENT SYSTEM\n";

    int choice;

    while (true) {
        printLine('=');
        cout << "\nSelect role:\n"
             << "1. Patient\n"
             << "2. Doctor\n"
             << "3. Admin Staff\n"
             << "0. Exit\n"
             << "Choice: ";

        choice = getValidChoice(0, 3);

        switch (choice) {
            case 1: patientModule(); break;
            case 2: doctorMenu(); break;
            case 3: adminModule(); break;
            case 0:
                cout << "Exiting system...\n";
                delete[] doctors;
                return 0;
        }
    }
}
