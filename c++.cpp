#include "DeitleTeam.h";
#include <fstream>
using namespace DeitleTeam;

enum enpar {
	eall = -1, plistclients = 1, paddnewclient = 2, pdeleteclient = 4,
	pupdateclient = 8, pfindclient = 16, ptransactions = 32, pmanageusers = 64
};

void MainMuneTable();

bool checkaccesspar(enpar par);

void Continue();

string FileName = "hamzaaaa.txt";
string FileNameUser = "user.txt";

struct cilent

{
	string accountnumbe="";
	string pincode="";
	string name="";
	string phone="";
	int ab = 0;

};

cilent Empty;

struct StUser
{
	string UserName = "";
	string Password = "";
	int premissions;
};

StUser e;

vector <string>split(string s, string delim)
{
	vector <string> vstring;
	int p = 0;
	string word;
	while ((p = s.find(delim)) != std::string::npos)
	{
		word = s.substr(0, p);
		if (word != "") {
			vstring.push_back(word);
		}
		s.erase(0, p + delim.length());
	}
	if (s != "") {
		vstring.push_back(s);
	}
	return vstring;

}

StUser onvertUserLienToRecord(string l, string sp = "&$")
{
	StUser User;
	vector<string>Vuser = split(l, sp);
	User.UserName = Vuser[0];
	User.Password = Vuser[1];
	User.premissions = stoi(Vuser[2]);
	return User;
}

cilent counvert(string l, string sep = "&$")
{
	cilent c;
	vector <string>vc= split(l, sep);
	c.accountnumbe = vc[0];
	c.pincode = vc[1];
	c.name = vc[2];
	c.phone = vc[3];
	c.ab = stod(vc[4]);
	return c;

}

vector<cilent>loadclient()
{
	vector<cilent>vc;
	fstream Myfile;
	Myfile.open(FileName, ios::in);
	if (Myfile.is_open())
	{
		string line;
		cilent c;
		while (getline(Myfile, line))
		{
			c = counvert(line);
			vc.push_back(c);
		}
		Myfile.close();
	}
	return vc;
}

vector<StUser>LoadUser()
{
	vector<StUser>vc;
	fstream Myfile;
	Myfile.open(FileNameUser, ios::in);
	if (Myfile.is_open())
	{
		string line;
		StUser c;
		while (getline(Myfile, line))
		{
			c = onvertUserLienToRecord(line);
			vc.push_back(c);
		}
		Myfile.close();
	}
	return vc;
}

void printc(cilent c)
{
	cout << "| " << left << setw(15) << c.accountnumbe;
	cout << "| " << left << setw(10) << c.pincode;
	cout << "| " << left << setw(30) << c.name;
	cout << "| " << left << setw(12) << c.phone;
	cout << "| " << left << setw(12) << c.ab;
}

void printUser(StUser user)
{

	cout << "| " << left << setw(15) << user.UserName;
	cout << "| " << left << setw(30) << user.Password;
	cout << "| " << left << setw(12) << user.premissions;
}

void showmassage()
{
	cout << "\n-------------------------------------\n";
	cout << "Access Denied, \nyou dont have permission to do this, \nplease conact your admin\n";
	cout << "\n-------------------------------------\n";

}

void PrintClientsList (vector <cilent>vc)
{
	
	cout << "\n\t\t\t\t\t client list (" << vc.size() << ")  client(s).";
	cout << "\n-----------------------------------------------------------";
	cout << "------------------------------------------------------\n" << endl;

	cout << "| " << left << setw(15) << "account number";
	cout << "| " << left << setw(10) << "pin code";
	cout << "| " << left << setw(30) << "name";
	cout << "| " << left << setw(12) << "phone";
	cout << "| " << left << setw(12) << "ab";
	cout << "\n-----------------------------------------------------------";
	cout << "------------------------------------------------------\n" << endl;
	for (cilent c : vc)
	{
		printc(c);
		cout << endl;
	}
	cout << "\n-----------------------------------------------------------";
	cout << "------------------------------------------------------\n" << endl;
}

void PrintUsersList(vector <StUser>vc)
{

	cout << "\n\t\t\t\t\t client list (" << vc.size() << ")  client(s).";
	cout << "\n-----------------------------------------------------------";
	cout << "------------------------------------------------------\n" << endl;
	cout << "| " << left << setw(15) << "user name";
	cout << "| " << left << setw(10) << "password";
	cout << "| " << left << setw(30) << "premissions";
	cout << "\n-----------------------------------------------------------";
	cout << "------------------------------------------------------\n" << endl;

	if (vc.size() == 0)
		cout <<"\t\tno user available in the system";
	else
	for (StUser c : vc)
	{
		printUser(c);
		cout << endl;
	}
	cout << "\n-----------------------------------------------------------";
	cout << "------------------------------------------------------\n" << endl;
}

void ShowClientList()
{


	if (!checkaccesspar(enpar::plistclients))
	{
		showmassage();

		return;
	}
	system("cls");
	PrintClientsList(loadclient());

	 
}

int Readpremissions()
{
	int par = 0;
	char Anser = 'n';
	cout << "do you want to give full accese y/n";
	cin >> Anser;
	if (Anser == 'y')
		return -1;
	cout << "\nShow Client List y/n";
	cin >> Anser;
	if (Anser == 'y')
		par += enpar::plistclients;
	cout << "\nadd new client y/n";
	cin >> Anser;
	if (Anser == 'y')
		par += enpar::paddnewclient;
	cout << "delete clients y/n";
	cin >> Anser;
	if (Anser == 'y')
		par += enpar::pdeleteclient;
	cout << "\nupdate client y/n";
	cin >> Anser;
	if (Anser == 'y')
		par += enpar::pupdateclient;
	cout << "\nfind client y/n";
	cin >> Anser;
	if (Anser == 'y')
		par += enpar::pfindclient;
	cout << "\ntransactions y/n";
	cin >> Anser;
	if (Anser == 'y')
		par += enpar::ptransactions;
	cout << "\nmanage users y/n";
	cin >> Anser;
	if (Anser == 'y')
		par += enpar::pmanageusers;


	return par;



}

void showuserlist()
{
	system("cls");
	PrintUsersList(LoadUser());

}

bool IsAccountNumberhere(string AccountNumber,cilent& Client1=Empty)

{
	vector <cilent> Client = loadclient();
	
	for (cilent& i : Client)
	{
		
		if (i.accountnumbe == AccountNumber)
		{
			Client1 = i;
			return true;
		}
	}
	return false;
}

bool IsUserName(string Name, StUser& User1= e)
{

	vector <StUser> User = LoadUser();

	for (StUser& i : User)
	{

		if (i.UserName == Name)
		{
			cout << i.UserName << " is found.\n";
			User1 = i;
			return true;
		}
	}
	return false;
}

StUser InPutUser()
{
	StUser User;
	do 
	{
		User.UserName= ReadString("User Name : ");


	} while (IsUserName(User.UserName));
	User.Password = ReadString("Password: ");
	User.premissions = Readpremissions();

	return User;
}

cilent InputClient()
{
	cilent Client;
	do
	{
		Client.accountnumbe = ReadString("Account Number : ");

	} while (IsAccountNumberhere(Client.accountnumbe));
	Client.pincode = ReadString("Pin Code : ");
	Client.name = ReadString("Name : ");
	Client.phone = ReadString("Phone : ");
	Client.ab = ReadPostiveNumber("Account Balance : ");

	return Client;
}

string ConvertUserToLine(StUser User)
{
	return User.UserName + "&$" + User.Password + "&$" + to_string(User.premissions);

}

string ConvertClientToLine(cilent Client)
{
	return Client.accountnumbe + "&$" + Client.pincode + "&$" + Client.name + "&$" + Client.phone + "&$" + to_string(Client.ab);
}

void AddUserToFile(string user)
{

	vector<StUser>vc;
	fstream Myfile;
	Myfile.open(FileNameUser, ios::out | ios::app);
	if (Myfile.is_open())
	{
		Myfile << user << endl;
		Myfile.close();
	}
}

void AddClientToFile(string Client)
{
	vector<cilent>vc;
	fstream Myfile;
	Myfile.open(FileName, ios::out|ios::app);
	if (Myfile.is_open())
	{
		Myfile << Client << endl;
		Myfile.close();
	}
}

void printDeleteClientScreenTaple()
{

	cout << "---------------------------------------------" << endl;
	cout << "             Delete Clients Screen          " << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl;
}

vector<StUser> DeleteUserFromFile(vector<StUser>vc, StUser acc)
{

	fstream Myfile;
	Myfile.open(FileNameUser, ios::out);
	if (Myfile.is_open())
	{
		for (StUser& i : vc) {
			if (i.UserName == acc.UserName) {
				continue;
			}
			else
				Myfile << ConvertUserToLine(i) << endl;

		}
		Myfile.close();
	}
	return vc;
}

vector<cilent> DeleteFromFile(vector<cilent>vc,cilent acc)
{
	
	fstream Myfile;
	Myfile.open(FileName, ios::out);
	if (Myfile.is_open())
	{
		cilent c;
		for(cilent&i:vc){
			if (i.accountnumbe == acc.accountnumbe) {
				continue;
			}
			else
				Myfile << ConvertClientToLine(i);
		
		}
		Myfile.close();
	}
	return vc;
}

void DeleteClientsScreen()
{
	if (!checkaccesspar(enpar::pdeleteclient))
	{
		showmassage(); 

		return;
	}
	system("cls");
	cilent d;
	printDeleteClientScreenTaple();
	vector<cilent>vs=loadclient();

	d.accountnumbe = ReadString("Please Enter Account Number : ");
	if (IsAccountNumberhere(d.accountnumbe)) {
		string choos = "";

		for (cilent& i : vs)
		{
			if (i.accountnumbe == d.accountnumbe) {
				cout << "------------------------------------------------------\n";

				cout << "account number :" << i.accountnumbe << endl;
				cout << "pin code :" << i.pincode << endl;
				cout << "name :"<<i.name<<endl;
				cout << "phone :"<<i.phone<<endl;
				cout << "ab :"<<i.ab<<endl;

				cout << "-----------------------------------------------------------\n";

				cout << "Are You Suer Delete This Client y/n :";
				cin >> choos;
				if (choos == "y") {
					DeleteFromFile(vs,d);
					cout << "Client Delete Succesfully\n";
					
				}
			}
		}
	}
	else {
		cout << "not found  " << d.accountnumbe;
	}
}

void PrintAddNewClientTaple()
{
	cout << "---------------------------------------------" << endl;
	cout << "             Add New Clients Screen          " << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Add New Client : " << endl;
}

void AddNewClient()
{
	if (!checkaccesspar(enpar::paddnewclient))
	{
		showmassage(); 

		return;
	}

	system("cls");

	PrintAddNewClientTaple();
	char YesOrNo;
	do
	{
		AddClientToFile(ConvertClientToLine(InputClient()));
		cout << endl << "Do you want add more clients ? (Y/N) : ";
		cin >> YesOrNo;
	} while (toupper(YesOrNo)=='Y');
	


}

void UpDateClientScrrenTable()
{
	cout << "---------------------------------------------" << endl;
	cout << "             UpDate Clients Screen          " << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl;

}

StUser UPDateUserInfo(string name)
{
	 StUser s;
	 
	 s.UserName = name;
	
	 cout << "please Enter password:";
	
	 getline(cin >> ws, s.Password);
	
	 s.premissions = Readpremissions();
	
	return s;
}

cilent UPDateInfo(string AccountNumber)
{
	cilent s;
	s.accountnumbe = AccountNumber;
	cout << "please Enter PinCode :";
	getline(cin >> ws, s.pincode);

	cout << "Please Enter Name :";
	getline(cin, s.name);

	cout << "Please Enter PHone :";
	getline(cin, s.phone);

	cout << "Please Enter ab :";
	cin >> s.ab;
	return s;
}

void PutINUserFile(vector<StUser>vc, StUser acc)
{
	string line;
	fstream Myfile;
	Myfile.open(FileNameUser, ios::out);
	if (Myfile.is_open())
	{
		for (StUser& i : vc) {
			if (i.UserName == acc.UserName) {

				Myfile << ConvertUserToLine(acc) << endl;
			}
			else
			{
				Myfile << ConvertUserToLine(i) << endl;
			}


		}
		Myfile.close();
	}

}

void PutINFile(vector<cilent>vc, cilent acc)
{
	string line;
	fstream Myfile;
	Myfile.open(FileName, ios::out);
	if (Myfile.is_open())
	{
		for (cilent& i : vc) {
			if (i.accountnumbe == acc.accountnumbe) {
				
				Myfile << ConvertClientToLine(acc)<<endl;
			}
			else
			{
				Myfile << ConvertClientToLine(i)<<endl;
			}
			

		}
		Myfile.close();
	}
	
}

void UpDateClientInfo()
{
	if (!checkaccesspar(enpar::pupdateclient))
	{
		showmassage(); 

		return;
	}

	system("cls");

	UpDateClientScrrenTable();

	vector<cilent>vc = loadclient();
	cilent d;
	d.accountnumbe = ReadString("please Enter Account Number:");
	if (IsAccountNumberhere(d.accountnumbe, d))
	{
		string choos = "";

		cout << "------------------------------------------------------\n";

		cout << "account number :" << d.accountnumbe << endl;
		cout << "pin code :" << d.pincode << endl;
		cout << "name :" << d.name << endl;
		cout << "phone :" << d.phone << endl;
		cout << "ab :" << d.ab << endl;

		cout << "-----------------------------------------------------------\n";

		cout << "Are You Sure Update This Client y/n :";
		cin >> choos;
		if (choos == "y")
		{

			d = UPDateInfo(d.accountnumbe);
			PutINFile(vc, d);
			cout << "Client Update Successfully\n";

		}
	}
	else
		cout << "THE Account Number " << d.accountnumbe << " not Found.";




}

void FindClientScrrenTable()
{

	cout << "---------------------------------------------" << endl;
	cout << "             Find Clients Screen          " << endl;
	cout << "---------------------------------------------" << endl;
}

void FindClient()
{
	if (!checkaccesspar(enpar::pfindclient))
	{
		showmassage(); 

		return;
	}

	system("cls");

	FindClientScrrenTable();
	vector<cilent>vs = loadclient();

	string Account = ReadString("Please Enter Account Number : ");
	if (IsAccountNumberhere(Account)) {
		for (cilent& i : vs)
		{
			if (i.accountnumbe == Account) {
				cout << "------------------------------------------------------\n";

				cout << "account number :" << i.accountnumbe << endl;
				cout << "pin code :" << i.pincode << endl;
				cout << "name :" << i.name << endl;
				cout << "phone :" << i.phone << endl;
				cout << "ab :" << i.ab << endl;

				cout << "-----------------------------------------------------------\n";
			}
			else
				cout << "The Account Number not found : " <<"("<< Account<<")";
				
		}
	}
}

void DepoistTable()
{
	cout << "---------------------------------------------" << endl;
	cout << "             Deposit Screen          " << endl;
	cout << "---------------------------------------------" << endl;

}

void AddValue(int value, cilent d, vector<cilent>vc)
{
	cout << "\nare you sure you want perfron this transaction (yes/no)\n";
	char a;
	cin >> a;
	if (toupper(a) == 'Y')
	{
		for (cilent& c : vc)
		{
			if (c.accountnumbe == d.accountnumbe)
			{
				c.ab = c.ab + value;
				PutINFile(vc, c);
				cout << "\ndone successfly. new balance is : " << c.ab;

				

			}
			
		}
	}
}

void Deposit()
{
	system("cls");
	DepoistTable();
	cilent c;
	vector <cilent> vc = loadclient();
	c.accountnumbe = ReadString("please Enter Account Number:");
	while (!IsAccountNumberhere(c.accountnumbe,c))
	{
		cout << "This Account[" << c.accountnumbe << "]" << "not found\n";
		c.accountnumbe = ReadString("please Enter Account Number:");
	}
	cout << "------------------------------------------------------\n";

	cout << "account number :" << c.accountnumbe << endl;
	cout << "pin code :" << c.pincode << endl;
	cout << "name :" << c.name << endl;
	cout << "phone :" << c.phone << endl;
	cout << "ab :" << c.ab << endl;

	cout << "-----------------------------------------------------------\n";

	int value = 0;
	cout << "please Enter Amount :\n";
	cin >> value;
	AddValue(value, c, vc);
}

void WithDrawTable()
{

	cout << "---------------------------------------------" << endl;
	cout << "           WithDraw Screen          " << endl;
	cout << "---------------------------------------------" << endl;

}

void DecreaseValue(int value, cilent d, vector<cilent>vc)
{

	cout << "\nare you sure you want perfron this transaction (yes/no)\n";
	char a;
	cin >> a;
	if (a == 'y')
	{
		for (cilent& c : vc)
		{
			if (c.accountnumbe == d.accountnumbe)
			{
				c.ab = c.ab - value;
				PutINFile(vc, c);
				cout << "\ndone successfly. new balance is : " << c.ab;

				
			}
		}
		
	}
}

void WithDraw()
{
	system("cls");

	WithDrawTable();
	
	cilent c;
	vector <cilent> vc = loadclient();
	c.accountnumbe = ReadString("please Enter Account Number:");
	while (!IsAccountNumberhere(c.accountnumbe,c))
	{
		cout << "This Account[" << c.accountnumbe << "]" << "not found\n";
		c.accountnumbe = ReadString("please Enter Account Number:");
	}
	cout << "------------------------------------------------------\n";

	cout << "account number :" << c.accountnumbe << endl;
	cout << "pin code :" << c.pincode << endl;
	cout << "name :" << c.name << endl;
	cout << "phone :" << c.phone << endl;
	cout << "ab :" << c.ab << endl;

	cout << "-----------------------------------------------------------\n";

	int value = 0;
	cout << "please Enter Amount :\n";
	cin >> value;
	while (value > c.ab)
	{
		cout << "\nAmount Exceeds The Balance. you can withdraw up to :" << c.ab<<endl;
		cout << "please enter another amount:";
		cin >> value;
	}
	DecreaseValue(value, c, vc);
}

void printInfo(cilent c)
{
	cout << "| " << left << setw(15) << c.accountnumbe;
	cout << "| " << left << setw(30) << c.name;
	cout << "| " << left << setw(12) << c.ab;
}

void ShowTotalBalances()
{
	system("cls");
	vector<cilent>vc = loadclient();


	cout << "\n\t\t\t\t\t client list (" << vc.size() << ")  client(s).";
	cout << "\n-----------------------------------------------------------";
	cout << "------------------------------------------------------\n" << endl;
	cout << "| " << left << setw(15) << "account number";
	cout << "| " << left << setw(30) << "name";
	cout << "| " << left << setw(12) << "ab";
	cout << "\n-----------------------------------------------------------";
	cout << "------------------------------------------------------\n" << endl;
	int total = 0;
	if (vc.size() == 0)
	{
		cout << " no client available in the system!";
	}
	else
		for (cilent& i : vc)
		{
			printInfo(i);
			total = total + i.ab;
			cout << endl;
		}
	cout << "\n-----------------------------------------------------------";
	cout << "------------------------------------------------------\n" << endl;
	cout << "\t\t\t\t  total balances = " << total;
}      

void ReturnMainMenue()
{
	system("cls");
	MainMuneTable();
}

void TransactionsMenueScreen()
{
	if (!checkaccesspar(enpar::ptransactions))
	{
		showmassage(); Continue();	MainMuneTable();

		return;
	}

	system("cls");

	cout << "_____________________________________________\n";
	cout << "\t\tTransactionsMenueScreen\n";
	cout << "_____________________________________________\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "_____________________________________________\n";
	cout << "choose what do you want to do [1 to 4]:";
}

void CountinueTransactionsmenu()
{

	cout << "\n\n\n\n        Press any key to return Transactions menu ....";
	system("pause>0");
	

}

void AddUserTable()
{

	cout << "---------------------------------------------" << endl;
	cout << "           Add User Screen          " << endl;
	cout << "---------------------------------------------" << endl;

}

void AddUser()
{
	system("cls");

	AddUserTable();


	char YesorNo{};
	do
	{
		AddUserToFile(ConvertUserToLine(InPutUser()));
		cout << endl << "Do you want add more Users ? (Y/N) : ";
		cin >> YesorNo;


	} while (toupper(YesorNo) == 'Y');
}

void printDeleteUserScreenTaple()
{

	cout << "---------------------------------------------" << endl;
	cout << "             Delete Users Screen          " << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl;
}

void DeleteUser()
{

	system("cls");
	StUser d;
	printDeleteUserScreenTaple();
	vector<StUser>vs = LoadUser();

	d.UserName = ReadString("Please Enter user name: ");
	if (IsUserName(d.UserName)) {
		char choos;

		for (StUser& i : vs)
		{
			if (i.UserName == d.UserName) {
				cout << "------------------------------------------------------\n";
				cout << "User Name :" << i.UserName<<endl;
				cout << "password :" << i.Password << endl;
				cout << "par :" << i.premissions << endl;
				cout << "-----------------------------------------------------------\n";

				cout << "Are You Suer Delete This User y/n :";
				cin >> choos;
				if (choos == 'y') {
					DeleteUserFromFile(vs, d);
					cout << "User Delete Succesfully\n";

				}
			}
		}
	}
	else {
		cout << "not found  " << d.UserName;
	}
}

void UpDateUserScrrenTable()
{
	cout << "---------------------------------------------" << endl;
	cout << "             UpDate Users Screen          " << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl;

}

void UpDateUser()
{
	system("cls");
	UpDateUserScrrenTable();

	vector<StUser>vc = LoadUser();
	StUser d;
	d.UserName= ReadString("please Enter User Name:");
	if (IsUserName(d.UserName, d))
	{
		string choos = "";

		cout << "------------------------------------------------------\n";
		cout << "User Name :" << d.UserName << endl;
		cout << "password :" << d.Password << endl;
		cout << "par :" << d.premissions << endl;
		cout << "-----------------------------------------------------------\n";

		cout << "Are You Sure Update This Client y/n :";
		cin >> choos;
		if (choos == "y")
		{

			d = UPDateUserInfo(d.UserName);
			PutINUserFile(vc, d);
			cout << "User Update Successfully\n";

		}
	}
	else
		cout << "the User Name  " << d.UserName << " not Found.";

}

void FindUserScrrenTable()
{

	cout << "---------------------------------------------" << endl;
	cout << "             Find Users Screen          " << endl;
	cout << "---------------------------------------------" << endl;
}

void FindUser()
{
	system("cls");

	FindUserScrrenTable();
	vector<StUser>vs = LoadUser();

	string Name = ReadString("Please Enter Name : ");
	if (IsUserName(Name)) {
		for (StUser& i : vs)
		{
			if (i.UserName == Name) {
				cout << "------------------------------------------------------\n";
				cout << "User Name :" << i.UserName << endl;
				cout << "password :" << i.Password << endl;
				cout << "par :" << i.premissions << endl;
				cout << "-----------------------------------------------------------\n";
			}
			else
				cout << "The User Name not found : " << "(" << Name << ")";

		}
	}
}

bool checkaccesspar(enpar par)
{
	if (e.premissions == enpar::eall)
		return true;
	if ((par & e.premissions) == par)
		return true;
	else
		return false;

}

void StartTransactions()
{
	TransactionsMenueScreen();
	int choos;
	cin >> choos;
	switch(choos)
	{
	case 1:Deposit(); CountinueTransactionsmenu(); StartTransactions(); break;
	case 2:WithDraw(); CountinueTransactionsmenu(); StartTransactions(); break;
	case 3:ShowTotalBalances(); CountinueTransactionsmenu(); StartTransactions(); break;
	case 4:ReturnMainMenue(); break;

	default:
		break;
	}
}

void ManageuserMenueScreen()
{
	if (!checkaccesspar(enpar::pmanageusers))
	{
		showmassage(); Continue();	MainMuneTable();
	
		return;
	}

	system("cls");
	cout << "==========================================================\n";
	cout << "\t\tManage User Menue Scrren\n";
	cout << "==========================================================\n";
	cout << "    [1] List Users.\n";
	cout << "    [2] Add New User.\n";
	cout << "    [3] Delete User.\n";
	cout << "    [4] UPdate User.\n";
	cout << "    [5] Find User.\n";
	cout << "    [6] Main Menue.\n";
	cout << "==========================================================\n";
	cout << "Enter Number [1 : 6} :";
}

void CountinueManage()
{

	cout << "\n\n\n\n        Press any key to return Manage menu ....";
	system("pause>0");

}

void StartManage()
{
	ManageuserMenueScreen();
	int choic;
	cin >> choic;
	switch (choic)
	{
	case 1:showuserlist(); CountinueManage(); StartManage(); break;
	case 2:AddUser(); CountinueManage(); StartManage(); break;
	case 3:DeleteUser(); CountinueManage(); StartManage(); break;
	case 4:UpDateUser(); CountinueManage(); StartManage(); break;
	case 5:FindUser(); CountinueManage(); StartManage(); break;
	case 6:ReturnMainMenue(); break;
	}
}

void ExitScrrenTable()
{

	cout << "---------------------------------------------" << endl;
	cout << "             Program Ends :-)                " << endl;
	cout << "---------------------------------------------" << endl;
	
}

void Exit()
{
	system("cls");

	ExitScrrenTable();

}

void MainMuneTable() {

	cout << "==============================================\n";
	cout << "                Main Menue Screen\n";
	cout << "==============================================\n";
	cout << "             [1] show client list.\n";
	cout << "             [2] add new client.\n";
	cout << "             [3] Delete Client.\n";
	cout << "             [4] update client Info.\n";
	cout << "             [5] Find client.\n";
	cout << "             [6] Transactions.\n";
	cout << "             [7] Manage user.\n";
	cout << "             [8] Exit.\n";
	cout << "==============================================\n";
	cout << "choose what do you want to do? [1 to 8]?\n";

}

void Continue()
{
	cout << "\n\n\n\n        Press any key to return main menu ....";
	system("pause>0");
	
}

bool isfound(string name ,string pass,StUser &user)
{
	vector<StUser>vc = LoadUser();
	for (StUser i : vc)
	{
		if (i.UserName == name && i.Password == pass) {
			user = i;
			return true;
		}
		else
		
			return false;
		
	}       
}

void LogInScreen() 
{
	string name, pass;

	bool Fales=false; 
	do {
		system("cls");

		cout << "---------------------------------------------" << endl;
		cout << "\t\t LogIn Screen                            " << endl;
		cout << "---------------------------------------------" << endl;
		
		if (Fales) {
			cout << "invalid name or password\n";
		}
		cout << "Enter Name :";
		cin >> name;
		cout << "Enter pass :";
		cin >> pass;

	

		if (Fales)
		{
			MainMuneTable();
		}
		Fales = !isfound(name, pass, e);
		
	} while (!Fales);
	


}

void StartBank()
{
	system("cls");
	int num;
	MainMuneTable();
	cin >> num;
	switch(num)
	{
	case 1: ShowClientList(); Continue(); StartBank(); break;
	case 2: AddNewClient(); Continue(); StartBank(); break;
	case 3:DeleteClientsScreen(); Continue(); StartBank(); break;
	case 4:UpDateClientInfo(); Continue(); StartBank(); break;
	case 5:FindClient(); Continue(); StartBank(); break;
	case 6:StartTransactions(); StartBank(); break;
	case 7:StartManage(); StartBank(); break;
	case 8:Exit();break;
	default:
		break;
	}
}

int main()
{
	//LogInScreen();
	StartBank();
}

