#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// hardcoded values and arrays defining
int patientID;
string patients[20]= {"alia","shazia","johnny","jugnu","basheer","ahmed talal","malik talal","shafia"};
int patientAge [20] = {23,17,10,34,45,78,34,5};
string diseases [20] = {"cholera","mad cow disease","malaria","cataract","anaemia","alzheimer's","diaorhhea","psychosis"};
string bloodGrp[20] = {"O+","O-","A+","A+","B+","AB+","O+","A+"};
int beds = 20;

//functions

// void PateintInfo();
// void dischargePatient();
// void admitPatient();
// void availableBeds();
// void BillOfPatient();

//starting with the functions now
void patientsInfo(){
    cout<<"enter the patient ID whose info you would like to see.\n";
    cin>>patientID;
    for (int p = 0; p<=20;p++){
        if (p == patientID-1){
        cout<< "patients name:"<<patients[p]<<endl;
        cout<< "patients age:"<<patientAge[p]<<endl;
        cout<< "patients disease:"<<diseases[p]<<endl;
        cout<<"patients blood group is: "<<bloodGrp[p]<<endl;
        cout<<"patients bed number: "<<patientID<<endl;
        }
        
        
    }



}

int main(){

    patientsInfo();
}