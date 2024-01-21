#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>

using namespace std;

struct staffLogin
{
	int idS;
	char pass[10], question[3][10];
};

struct staffInfo
{
	int idS, ageS;
	char nameS[40];
}staff[20];

struct patientInfo
{
	int idP, ageP;
	char nameP[100], genderP[10], blood[7];
	char symptom[500], diagnosis[500], medicine[500], history[500];
};

int firstMenu();
void registerPage(ofstream&);
void loginPage();
int secondMenu();
void menu1(staffInfo staff[]);
void menu2(patientInfo patient[], ifstream&, ofstream&);
void addRecord(ofstream&);
void calcPage(struct patientInfo patient[], ifstream&);
void menu3(patientInfo patient[], int c);
void menu4(patientInfo patient[]);
void exitMenu();

int main()
{
	int a = 0;
	char lineS[100];
	ifstream inLine;
	inLine.open("staffLogin.txt");
	while (!inLine.eof())
	{
		inLine.getline(lineS, 100);
		a++;
	}
	staffLogin login[a];
	inLine.close();

	int choice;
	choice = firstMenu();
	switch(choice)
	{
		case 1:
		{
			ofstream ofrgstr;
			ofrgstr.open("staffInfo.txt", ios::app);
			registerPage(ofrgstr);
			main();
			break;
		}
		case 2:
		{
			loginPage();
			break;
		}
		default:
		{
			cout << "Wrong choice.\n";
			main();
			break;
		}
	}
	
	//secondMenu();
}

int firstMenu()
{
	int choice;
	cout << "\n--------------------------------------------------------\n";	
	cout << "\tWARD 11 HOSPITAL SERDANG\n\n";
	cout << "1. Register\n";
	cout << "2. Login\n";
	cout << "--------------------------------------------------------\n";
	cout << "Please choose : ";
	cin >> choice;
	return choice;
}

void registerPage(ofstream& ofrgstr)
{
	int id, age;
	char name[100], pw[10], security[3][50];
	cout << "\nSTAFF ID : ";
	cin >> id;
	cin.ignore();
	cout << "NAME : ";
	cin.getline(name, 100);
	cout << "AGE : ";
	cin >> age;
	cout << "\nCreate a password (must be less than 10 words) : ";
	cin >> pw;
	cin.ignore();
	cout << "\nSECURITY QUESTION\n";
	cout << "What high school did you attend? : ";
	cin.getline(security[0], 10);
	cout << "What is your favourite food? : ";
	cin.getline(security[1], 10);
	cout << "In what city are you born? : ";
	cin.getline(security[2], 10);
		
	ofrgstr << "\n" << id << " ";
	ofrgstr << name << "; ";
	ofrgstr << age;
	ofrgstr.close();
	
	ofstream outlogin;
	outlogin.open("staffLogin.txt", ios::app);
	outlogin << "\n" << id << " ";
	outlogin << pw << " ";
	outlogin << security[0] << " ";
	outlogin << security[1] << " ";;
	outlogin << security[2];
	outlogin.close();
	
	cout << "\nYour account has been registered successfully.\n\n";
}

void loginPage()
{
	string id, pw;
	int offset;
	string line;
	
	ifstream inlogin;
	inlogin.open("staffLogin.txt");
	cout << "\nSTAFF ID: ";
	cin >> id;
	cout << "PASSWORD: ";
	cin >> pw;
	
	if(inlogin.is_open())
	{
		int *m, n, p;
		while(!inlogin.eof())
		{
			getline(inlogin, line);
			if((offset=line.find(id, 0))!=string::npos && (offset=line.find(pw,0))!=string::npos)
			{
				p = 1;
				m = &p;
				n = *m;
			}
			else
			{
				p = 2;
			}
		}
	inlogin.close();
		
		switch(n)
		{
			case 1:
			{
				cout << "Login successful."<<endl;
				break;
			}
			default:
			{
				cout << "Not found. Wrong ID or PASSWORD."<<endl;
				main();
				break;
			}
		}
	}
	
	secondMenu();
}

int secondMenu()
{
	char line[100];
	int c = 0;
	ifstream inP;
	inP.open("patientRecord.txt");
	while (!inP.eof())
	{
		inP.getline(line, 100);
		c++;
	}
	inP.close();
	patientInfo patient[c];

	int k;
	cout << "\n--------------------------------------------------------\n";	
	cout << "\tMENU\n\n";
	cout << "1. Staff Information" << endl;
	cout << "2. Patient Information" << endl;
	cout << "3. Patient Diagnosis Information" << endl;
	cout << "4. Patient History" << endl;
	cout << "5. Back" << endl;
	cout << "--------------------------------------------------------\n";	
	cout << "Please choose : " ;
	cin >> k;
	
	switch(k)
	{
		case 1:
		{
			menu1(staff);
			break;
		}
		case 2:
		{
			inP.open("patientRecord.txt");
			ofstream outP;
			outP.open("patientRecord.txt", ios::app);
			menu2(patient, inP, outP);
			break;
		}
		case 3:
		{
			menu3(patient, c);	
			break;
		}
		case 4:
		{
			menu4(patient);
			break;
		}
		case 5:
		{
			main();
		}
		default:
		{
			cout << "Wrong choice. Please choose again."<<endl;
			secondMenu();
			break;
		}
	}
}

void menu1(struct staffInfo staff[])
{	
	ifstream infoS;
	infoS.open("staffInfo.txt");
	cout << "\n--------------------------------------------------------\n";	
	cout << "\tSTAFF INFORMATION\n" <<endl;
	cout << setw(10) << "ID" << setw(30) << " NAME" << setw(15) << "AGE" <<endl;
	
	int i = 0;
	while (!infoS.eof())
	{
		infoS >> staff[i].idS;
		infoS.getline(staff[i].nameS, 40, ';');
		infoS >> staff[i].ageS;
		cout << setw(10) << staff[i].idS
			 << setw(30) << staff[i].nameS
			 << setw(15) << staff[i].ageS << endl;
		i++;
	}
	infoS.close();
	
	cout << "--------------------------------------------------------\n";	
	
	int q;
	cout << "\n1. Menu"<<endl;
	cout << "2. Exit"<<endl;
	cout << "Please choose: ";
	cin >> q;
	
	if(q==1)
	{
		secondMenu();
	}
	else
	{ 
		exitMenu();
	}	
}

void menu2(struct patientInfo patient[], ifstream& inP, ofstream& outP)
{
	int q2;	
	cout << "\n1. Add a new record"<<endl;
	cout << "2. Calculate patient's stay"<<endl;
	cout << "3. Back" << endl;
	cout << "Please choose : " ;
	cin >> q2;
	
	if (q2==1)
	{
		addRecord(outP);
	}
	else if(q2==2)
	{
		calcPage(patient, inP);
	}
	else if(q2==3)
	{
		secondMenu();
	}
	else
	{
		cout << "Wrong choice. Please try again." <<endl;
		menu2(patient, inP, outP);
	}
}

void addRecord(ofstream& outP)
{	
	int newID, newAge;
	char newName[100], newGender[10], newBlood[7];
	char newSymptom[500], newDiagnosis[500], newMedicine[500], newHistory[500];
	char q='y';
	ofstream outD;
	outD.open("patientDiagnosis.txt", ios::app);
	ofstream outH;
	outH.open("patientHistory.txt", ios::app);
	while(q=='y' || q=='Y')
	{
		cout << "\nPatient ID : ";
		cin >> newID;
		cout <<"Patient name : ";
		cin.getline(newName, 100);
		cin.getline(newName, 100);
		cout << "Age : ";
		cin >> newAge;
		cout << "Gender : ";
		cin >> newGender;
		cout << "Blood type : ";
		cin >> newBlood;
		cout << "Symptom : ";
		cin.getline(newSymptom, 500);
		cin.getline(newSymptom, 500);
		cout << "Diagnosis : ";
		cin.getline(newDiagnosis, 500);
		cout << "Medicine assign : ";
		cin.getline(newMedicine, 500);
		cout << "Patient history : ";
		cin.getline(newHistory, 500);
		
		outP << newID << " " << newName << "; " 
			 << newAge << " " << newGender << " " 
			 << newBlood << endl;
			 
		outD << newID << " " << newSymptom << "; " 
		  	 << newDiagnosis << "; " << newMedicine << endl;
		  	 
		outH << newID << " " << newHistory << endl;
		
		cout << "Do you want to add another record? (y/n) : ";
		cin >> q;
	}
	outP.close();
	outD.close();	
	outH.close();
	
	int t;
	cout << "\n1. Menu"<<endl;
	cout << "2. Exit"<<endl;
	cout << "Please choose: ";
	cin >> t;
	
	if(t==1)
	{
		secondMenu();
	}
	else
	{ 
		exitMenu();
	}	
}

void calcPage(struct patientInfo patient[], ifstream& inCalc)
{
	int id, days, payment;
	char name[100];
	int offset;
	string line;
	
	cin.ignore();
	cout << "\nEnter the patient's name which you want to calculate the ward fee."<<endl;
	cout << "Patient name : ";
	cin.getline(name, 100);

	if (inCalc.is_open())
	{
		int *x, y, z;
		while(!inCalc.eof())
		{
			getline(inCalc, line);
			if((offset=line.find(name, 0))!=string::npos)
			{
				z = 1;
				x = &z;
				y = *x;
			}
			else
			{
				z = 2;
			}
		}
		
		switch(y)
		{
			case 1:
			{
				cout << "\nPatient found. How many days does this patient stay? : ";
				cin >> days;
				
				if(days<=10)
				{
					payment = days*3;
				}
				else if(days<=60)
				{
					payment = (days-10)*5+30;
				}
				else
				{
					payment = (days-60)*7+275;
				}
				
				cout << "\nPayment for patient " << name << " is RM" << payment << "." <<endl;
				secondMenu();
				break;
			}
			
			default:
			{
				cout << "\nPatient not found."<<endl;;
				secondMenu();
				break;
			}
		}
	}
	inCalc.close();
}

void menu3(struct patientInfo patient[], int c)
{	
	int id;
	cout << "Patient ID : ";
	cin >> id;
	
	cout << "--------------------------------------------------------\n";
	cout << "\tPATIENT DIAGNOSIS INFORMATION\n\n";
	
	ifstream inD;
	inD.open("patientDiagnosis.txt");
	int s = 0;
	int *x, y, z, r, *t, u;
	while (!inD.eof())
	{
		inD >> patient[s].idP;
		inD.getline(patient[s].symptom, 500, ';');
		inD.getline(patient[s].diagnosis, 500, ';');
		inD.getline(patient[s].medicine, 500);
		
		if(patient[s].idP==id)
		{
			z = 1;
			x = &z;
			y = *x;
			r = s;
			t = &r;
			u = *t;	
		}
		s++;
	}
	inD.close();
	
	switch(y){
		case 1:
		{
			cout << "Patient ID        :  " << patient[u].idP;
			cout << "\nSymptom           : " << patient[u].symptom;
			cout << "\nDiagnosis         : " << patient[u].diagnosis;
			cout << "\nMedicine assigned : " << patient[u].medicine;
			cout << "\n--------------------------------------------------------\n";
			
			int q;
			cout << "\n1. Menu" << endl;
			cout << "2. Exit" << endl;
			cout << "Please choose: ";
			cin >> q;
	
			if(q==1)
			{
				secondMenu();
			}
			else
			{ 
				exitMenu();
			}	
			
			break;
		}
		default:
		{
			cout << "Patient ID not found. Going back to MENU."<<endl;
			secondMenu();
			break;
		}
	}	
}

void menu4(struct patientInfo patient[])
{
	int id;
	cout << "Patient ID : ";
	cin >> id;
	cout << "--------------------------------------------------------\n";
	cout << "\tPATIENT HISTORY\n\n";
	
	ifstream inD;
	inD.open("patientHistory.txt");
	int s = 0;
	int *x, y, z, r, *t, u;
	while (!inD.eof())
	{
		inD >> patient[s].idP;
		inD.getline(patient[s].history, 500);
		
		if(patient[s].idP==id)
		{
			z = 1;
			x = &z;
			y = *x;
			r = s;
			t = &r;
			u = *t;
		}
		s++;
	}
	inD.close();
	
	switch(y){
		case 1:
		{
			cout << "Patient ID        :  " << patient[u].idP;
			cout << "\nMedical history   : " << patient[u].history;
			cout << "\n--------------------------------------------------------\n";		
			
			int q;
			cout << "\n1. Menu" << endl;
			cout << "2. Exit" << endl;
			cout << "Please choose: ";
			cin >> q;
	
			if(q==1)
			{
				secondMenu();
			}
			else
			{ 
				exitMenu();
			}	
			
			break;
		}
		default:
		{
			cout << "Patient ID not found. Going back to MENU."<<endl;
			secondMenu();
			break;
		}
	}	
}

void exitMenu()
{
	cout << "\nYou have been logged out successfully. Thank you for your hard work!"<<endl;
}
