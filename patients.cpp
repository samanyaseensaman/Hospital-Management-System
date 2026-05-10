#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream> // had to add this for csv handling
using namespace std;
// some bugs are left to fix, and the csv accessing problem still persists, thora time or lagay ga
// everyone can check and tell me whatevers wrong

//functions

// void PateintInfo();
// void dischargePatient();
// void admitPatient();
// void availableBeds();
// void BillOfPatient();
//void displayAllPatients();

// changes made because structs are allowed now  ~~~~~~~~~~~~~~~~~~

struct Patient {
    int patientID;
    string name;
    int age;
    string disease;
    string bloodGroup;
    string admissionDate;
    double totalBill;
};

// Struct to manage the hospital operations
struct PatientManager {
    int TOTAL_HOSPITAL_BEDS = 20;
    Patient patients[20]; 
    int patientCount = 0; 
    
    double RATE_PER_DAY = 500.0;
    string FILENAME = "patientsinfo.csv";
// had to change the function and use sstream for easier and better execution.
  int displayAllPatients() {
        // Load patients from CSV aahhhhhg ajeeb kam. done anyways
        ifstream file(FILENAME);
        if (!file.is_open()) {
            cout << "Error opening file\n";
            return 1;
        }

        patientCount = 0; // reset before loading

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            if (patientCount >= TOTAL_HOSPITAL_BEDS) break;

            string token;
            stringstream ss(line);
            Patient p{};

           
            if (!getline(ss, token, ',')) continue;
            p.patientID = stoi(token);

           
            if (!getline(ss, token, ',')) token = "";
            p.name = token;

            
            if (!getline(ss, token, ',')) token = "0";
            p.age = stoi(token);

         
            if (!getline(ss, token, ',')) token = "";
            p.disease = token;

            if (!getline(ss, token, ',')) token = "";
            p.bloodGroup = token;

            // 6) admissionDate
            if (!getline(ss, token, ',')) token = "";
            p.admissionDate = token;

            
            if (getline(ss, token, ',')) {
                p.totalBill = token.empty() ? 0.0 : stod(token);
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
        for (int i = 0; i < patientCount; i++) {
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
                
                
                for (int j = i; j < patientCount - 1; j++) {
                    patients[j] = patients[j + 1];
                }
                patientCount--;
                savePatients(); // Update CSV
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

        cin.ignore(1000,'\n');
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
        cout<<endl;
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
    hospital.displayAllPatients(); 

    int choice;
    do {
        
        cout << "    HOSPITAL MANAGEMENT SYSTEM    \n";
        cout << "==================================\n";
        cout << " 1. Admit Patient\n";
        cout << " 2. View Patient Info\n";
        cout << " 3. Check Available Beds\n";
        cout << " 4. Calculate Patient Bill\n";
        cout << " 5. Discharge Patient\n";
        cout << " 6. show all patients.\n ";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout<<endl;

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
                cout << " wapis na ana \n";
                break;
            default:
                cout << "Invalid choice. stop being illiterate.\n";
        }
    } while (choice != 7);


    return 0;
}
    
