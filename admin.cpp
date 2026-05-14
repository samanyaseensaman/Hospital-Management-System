  #include<iostream>
   #include<fstream>
   #include<string>
   #include<cstring> 
   using namespace std;
        
const string patientDetails ="patient.dat";
const string schedule= "schedule.dat";
const string notes ="notes.dat";
const string doctorsFile= "doctors.dat";
const string appointment= "appointment.dat";
  
   
struct Patientdd
{
int patientID;
int patientAge;
char patientName[20];
char Gender[10];
char contact[15];
char bloodGroup[10];
int assignedDoctorID;
} ;  
   
struct Doctordd
{
int doctorid;
char doctorName[20];
char speciality[40];
char availableDates[20];//11-03-2026
char contact[15];
char password[20];   
}  ; 

   
struct Notes   
{
int notesID;	
int patientID;
int assignedDoctorID;
char diagnosis[500];
char prescription[500];
char Date[20];
};   
   
struct Appointment
{
int appointmentID;
int patientID;
int assignedDoctorID;	
char Date[20];
char slot[10];
char status[20];//done, booked, pending		
};   

struct Slot
{
char date[20];	
char slot[10];
char status[20];// check if slot open, blocked	
int doctorid;	
}  ; 
   
//Global Variables

Doctordd currentDoctor;
Doctordd *pDoctor=&currentDoctor;  
   
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
 
bool doctorLogin(){
	int ID;
	char password[20];
	int	attempts=0;
while (attempts<3){

cout<<"--------Doctor Module Login--------"<<endl;
cout<<"Enter your Doctor Id"<<endl;
cin>>ID;
cout<<"Enter your password"<<endl;
cin>>password;
ifstream file(doctorsFile .c_str(),ios::binary);
if(!file){
cout<<"Error!Doctor File not found"<<endl;
return false;
}
Doctordd d;
while(file.read((char*)&d, sizeof(Doctordd)))	{

if (ID==d.doctorid&&strcmp(password, d.password)==0){
		currentDoctor=d;
		file.close();
		return true;
	}	
}
attempts++;
 cout << "Invalid password! Attempts left: " << (3 - attempts) << "\n";
 
}  
cout<<"Too many failed attempts access denied!"<<endl; 
return false;   
}

void patientProfile(){
	ifstream file(patientDetails.c_str(), ios::binary);
	if(!file)
	{cout<<"There is no patient with such ID"<<endl;
	return;
	}
	Patientdd d;
	bool found=false;
while(	file.read((char*)&d, sizeof(Patientdd)))
if (d.assignedDoctorID==currentDoctor.doctorid)	
{
	cout<<"The id of patient is: "<<d.patientID<<endl;
	cout<<"Patient's age is: " <<d.patientAge<<endl;
	cout<< "Patient Nmae is: "<<d.patientName<<endl;
	cout<< "Patient's gender is: "<<d.Gender<<endl;
	cout<< "Patient's Contact no is: "<<d.contact<<endl;
	cout<<" Patient's blood group is: "<<d. bloodGroup<<endl;
	cout<<"-------------------------------------------"<<endl;
	found=true;
	}	
	
	
if(!found)
{cout<<"No patients assigned to you"<<endl;
	}
	file.close();			
}  
  

void searchPatients  (){
int patientid;
cout<<"Enter id of patient you want to search"<<endl;
cin>>patientid;

	ifstream file(patientDetails.c_str(), ios::binary);	
	if(!file)
	{cout<<"There is no patient with such ID"<<endl;
	return;
	}
	Patientdd q;
	bool found=false;
while(	file.read((char*)&q, sizeof(Patientdd)))
if (q.patientID==patientid&&q.assignedDoctorID==currentDoctor.doctorid)	
{
	cout<<"Patient's age is: " <<q.patientAge<<endl;
	cout<< "Patient Nmae is: "<<q.patientName<<endl;
	cout<< "Patient's gender is: "<<q.Gender<<endl;
	cout<< "Patient's Contact no is: "<<q.contact<<endl;
	cout<<" Patient's blood group is: "<<q. bloodGroup<<endl;
	cout<<"-------------------------------------------"<<endl;
	found=true;
	}	
if(!found)
{cout<<"No patients assigned to you"<<endl;
	}	
	file.close();		
}

void checkAppointment  (){
int id;
cout<<"Enter id of patient to see appointments"<<endl;
cin>>id;

	ifstream file(appointment.c_str(), ios::binary);	
	if(!file)
	{cout<<"No file Exists"<<endl;
	return;
	}
	Appointment q;
	bool found=false;
while(	file.read((char*)&q, sizeof(Appointment)))
if (q.patientID==id&&q.assignedDoctorID==currentDoctor.doctorid)	
{
	cout<< "Patient ID is: "<<q.patientID<<endl;
	cout<< "Booked slot is: "<<q.slot<<endl;
	cout<<" Appointment date is: "<<q.Date<<endl;
	cout<<"-------------------------------------------"<<endl;
	found=true;
	}	
		
	
if(!found)
{cout<<"No appointment for you"<<endl;
}
file.close();		
}

  
void AppointmentUpdate (){
int assId;
cout<<"Enter assignment ID: "<<endl;
cin>>assId;

	fstream file(appointment.c_str(), ios::binary|ios::in|ios::out );

	if(!file)
	{cout<<"There is no patient with such ID"<<endl;
	return;
	}
Appointment a;
bool found =false;
while(	file.read((char*)&a, sizeof(Appointment))){

if (a.appointmentID==assId&&a.assignedDoctorID==currentDoctor.doctorid)	
{
strcpy(a.status,"confirmed");
file.seekp(-(long) sizeof (Appointment),ios::cur);
	file.write((char*)&a, sizeof(Appointment));
found=true;
cout<<"Appointment is confirmed"<<endl;
break;
}
} 
  if(!found)
{cout<<"No appointment booked"<<endl;
}
file.close();		
}

 
 void addnotes(){
 	int patientid;
 	cout<<"Enter id of patient you want to add notes"<<endl;
cin>>patientid;
	ifstream file(patientDetails.c_str(), ios::binary);
	if(!file)
	{cout<<"There is no patient with such ID"<<endl;
	return;
	}
	bool found=false;
	Patientdd d;
while(	file.read((char*)&d, sizeof(Patientdd))){

if (d.patientID==patientid&&d.assignedDoctorID==currentDoctor.doctorid)	
{
found=true;
break;
}	
}
file.close();
if(!found)
{cout<<"No patients assigned to you"<<endl;
return;
}			
 Notes n;
  n.patientID = patientid;
 
 cin.ignore();
 
 n.assignedDoctorID=currentDoctor.doctorid;
 cout<<" Notes ID"<<endl;
 cin>>n.notesID;
 cout<<"Disease diagnosis "<<endl; 
 cin>> n.diagnosis;

  cout<<"prescription is "<<endl;
cin>>n.prescription;

  cout<<"Date is "<<  n.Date<<endl;
 cin>>n.Date;
 
 
	ofstream infile(notes.c_str(), ios::binary|ios::app);
  
  if(!infile)
{cout<<"notes file not exist"<<endl;
	return;	}
			infile.write((char*)&n, sizeof(Notes));
			infile.close();
cout<<"Notes saved successfuly"<<endl;
} 
  

void viewNotes  (){
int id;
cout<<"Enter id of patient to see appointments"<<endl;
cin>>id;

	ifstream file(notes.c_str(), ios::binary);	
	if(!file)
	{cout<<"No notes exists"<<endl;
	return;
	}
	Notes q;
	bool found=false;
while(	file.read((char*)&q, sizeof(Notes)))
if (q.patientID==id&&q.assignedDoctorID==currentDoctor.doctorid)	
{
	cout<< "Patient ID is: "<<q.patientID<<endl;
	cout<<"Disease diagnosis: "<< q.diagnosis <<endl; 
    cout<<"prescription is "<<q.prescription<<endl;
	cout<<" Appointment date is: "<<q.Date<<endl;
	cout<<"-------------------------------------------"<<endl;
	found=true;
}		
if(!found)
{cout<<"No saved notes here"<<endl;
}
file.close();		
}
  
  
 
 void availabilityCheck()
{
  Slot s; 
 cin.ignore();
 
 s.doctorid=currentDoctor.doctorid;
 cout<<"Enter time slot"<<endl;
 cin>>s.slot;
 cout<<"Enter status of slot booked or not"<<endl; 
 cin>> s.status;                                                           
  cout<<"Date is "<< s.date<<endl;
 cin>>s.date;
 
 
	ofstream file(schedule.c_str(), ios::app);
  
  if(!file)
{cout<<"schedule exist"<<endl;
	return;	}
				file.write((char*)&s, sizeof(Slot));
			file.close();
cout<<"Schedule saved successfuly"<<endl;
}  
 
 
 void checkShecdule  (){
	ifstream file(schedule.c_str(), ios::binary);	
	if(!file)
	{cout<<"No file Exists"<<endl;
	return;
	}
	Slot q;
	bool found=false;
while(	file.read((char*)&q, sizeof(Slot)))
if (q.doctorid==currentDoctor.doctorid)	
{
	cout<< "Booked slot is: "<<q.slot<<endl;
	cout<<" Appointment date is: "<<q.date<<endl;
	cout<<"Appointment Staus: "<<q.status<<endl;
	cout<<"-------------------------------------------"<<endl;
	found=true;
	}	
		
	
if(!found)
{cout<<"No appointment for you"<<endl;
}
file.close();		
}
 
void adminModule(){
     	printLine();
     	cout<<"----------Doctor Module------------"<<endl;
     	printLine();
     	int choice;
     	
do{
cout<<"choice==1: View Patients Profile"<<endl;
cout<<"choice==2: Search Patient by ID"<<endl;
cout<<"choice==3: Check Appointments"<<endl;
cout<<"choice==4: Confirm Appointments"<<endl;
cout<<"choice==5: Add Notes "<<endl;
cout<<"choice==6: View notes"<<endl;
cout<<"choice==7: Add availability"<<endl;
cout<<"choice==8: Check Shecdule"<<endl;
cout<<"choice==0  Logout"<<endl;
cout<<"Enter choice"<<endl;	
cin>>choice;     	     		
switch(choice){
	case 1:
    patientProfile();
	break;  	     	 	
    case 2:
    searchPatients  ();
	break;  	     		
    case 3:
	checkAppointment  () ;	     	
    break;  	
    case 4:
	AppointmentUpdate ();
	break; 	
    case 5:
	addnotes();
	break;
	case 6: 	
    viewNotes  ();
	break;
	case 7:
	availabilityCheck();
	break;	
	case 8:
	checkShecdule  ();
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



    
}
