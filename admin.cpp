   #include<iostream>
   #include<fstream>
   #include<string>
   #include<cstring> 
   #include <sstream>
#include <cstdio>
   #include<limits>
   using namespace std;
        
const string patientDetails ="patient.csv";
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

        Appointment a;

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

int main(){

	
if (adminLogin())
{
	adminModule  ();
}
 
else cout<<"Login Failed!";
    return 0;
    
}
