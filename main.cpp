#include <iostream>
using namespace std;


#include "patientsMod.cpp"
#include "doctor.cpp"
#include "admin.cpp"

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
