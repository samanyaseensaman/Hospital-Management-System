#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;


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

 void displayAllPatients() {
    if (patientCount == 0) {
        cout << "\nNo patients currently admitted.\n";
        return;
    }

    for (int i = 0; i < patientCount; i++) {
        cout <<"patients ID: "<< patients[i].patientID << "\n"
             <<"name: "<<patients[i].name<< "\n" 
             <<"age: "<< patients[i].age << "\n"
             <<"disease: "<< patients[i].disease << "\n"
             <<"blood group: "<< patients[i].bloodGroup << "\n"
             <<"date of admission: "<< patients[i].admissionDate << "\n"
             <<"total bill for stay: "<< "$" << patients[i].totalBill << "\n";
    }
    }

}
    
