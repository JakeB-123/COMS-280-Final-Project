#include<iostream>
#include<list>
#include<string>
#include<cctype>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;


//// ================================ Classes ================================ ////
class entry
{
public:
	string accountnum;
	string description;
	string type;
	string direction;
	int amount;
};

class allAccounts
{
	int accountNum;
public:
	void Display_accounts();
	void Display_AllTranactions();
};

class account
{
	friend account operator+(account ac, int entAmount);
	friend account operator-(account ac, int entAmount);
public:
	string accountNum;
	string accountName;
	string accountType;
	int accountBalance;
	void create_account();
	void close_account(string accountnum);
	void edit_account(string accountnum);
	void display_account(string accountnum);
	void deposit_account(string accountnum);
	void withdrawl_account(string accountnum);
	void dislaylog_account(string accountnum);
	void recordlog_account(entry ent);
	bool verify_account(string accountnum);
	account get_account(string accountnum);
	string get_accounttype(string accountnum);
	int generate_accountnum();
};

class savingsAccount : public account
{
	friend savingsAccount operator+(savingsAccount sa, int entAmount);
	friend savingsAccount operator-(savingsAccount sa, int entAmount);
public:
	void create_account();
	int intrestRate;
	string SavingsType;
	savingsAccount get_account(string accountnum);
	void update_account(savingsAccount sa);
};

class checkingAccount : public account
{  
	friend checkingAccount operator+(checkingAccount ca, int entAmount);
	friend checkingAccount operator-(checkingAccount ca, int entAmount);
public:
	void create_account();
	int monthlyFee;
	string checkingType;
	checkingAccount get_account(string accountnum);
	void update_account(checkingAccount ca);
};

class User
{
	string userName;
	string password;
	list<int> accounts;
	string firstname;
	string lastname;
public:
	void Create_User();
	void Delete_User();
	void Edit_User();
	int Login_User(string username, string password);
	int Logoff_User();
	void DisplayAll_User();
};
struct node
{
	string transaction;
	node* next;
};

class ll_transaction_log
{
	node* head, * tail;
public:
	ll_transaction_log()
	{
		head = NULL;
		tail = NULL;
	}
	void add_node(string trans);
	ll_transaction_log load_list();
	void display();
};

//// ================================ Classes Methods ================================ ////
/// Bulk Account Actions ///
void allAccounts::Display_accounts()
{
	ifstream accountfile_read;
	accountfile_read.open("accounts.txt");
	if (accountfile_read.is_open())
	{
		string line;
		while (getline(accountfile_read, line))
		{
			account ac;
			istringstream lineparts(line);
			getline(lineparts, ac.accountNum, ',');
			ac.display_account(ac.accountNum);
		}
		accountfile_read.close();
	}
};

void allAccounts::Display_AllTranactions()
{
	ll_transaction_log translog = translog.load_list();
	translog.display();
}

/// Single Account Actions ///
account account::get_account(string accountnum)
{
	account ac;
	if (!verify_account(accountnum)) { cout << "Account Not found\n"; return ac; }

	ifstream accountfile_read;
	accountfile_read.open("accounts.txt");
	if (accountfile_read.is_open())
	{
		string line;
		while (getline(accountfile_read, line))
		{
			if (line.find(accountnum, 0) != string::npos) {
				istringstream lineparts(line);


				getline(lineparts, ac.accountNum, ',');
				getline(lineparts, ac.accountType, ',');
				getline(lineparts, ac.accountName, ',');
				string stracbal = to_string(ac.accountBalance);
				getline(lineparts, stracbal, ',');
			}
		}
	}
	return ac;
}

savingsAccount savingsAccount::get_account(string accountnum)
{
	savingsAccount sa;
	if (!verify_account(accountnum)) { cout << "Account Not found\n"; return sa; }

	ifstream accountfile_read("accounts.txt");
	if (accountfile_read.is_open())
	{
		string line;
		while (getline(accountfile_read, line))
		{
			if (line.find(accountnum, 0) != string::npos) {
				istringstream lineparts(line);

				getline(lineparts, sa.accountNum, ',');
				getline(lineparts, sa.accountType, ',');
				getline(lineparts, sa.accountName, ',');
				string stracbal = to_string(sa.accountBalance);
				getline(lineparts, stracbal, ',');
				sa.accountBalance = stoi(stracbal);
				string strsaintrestRate = to_string(sa.intrestRate);
				getline(lineparts, strsaintrestRate, ',');
				sa.intrestRate = stoi(strsaintrestRate);
				getline(lineparts, sa.SavingsType, ',');
			}
		}
	}
	accountfile_read.close();
	return sa;
}

checkingAccount checkingAccount::get_account(string accountnum)
{
	checkingAccount ca;
	if (!verify_account(accountnum)) { cout << "Account Not found\n"; return ca; }

	ifstream accountfile_read("accounts.txt");
	if (accountfile_read.is_open())
	{
		string line;
		while (getline(accountfile_read, line))
		{
			if (line.find(accountnum, 0) != string::npos) {
				istringstream lineparts(line);

				getline(lineparts, ca.accountNum, ',');
				getline(lineparts, ca.accountType, ',');
				getline(lineparts, ca.accountName, ',');
				string stracbal = to_string(ca.accountBalance);
				getline(lineparts, stracbal, ',');
				ca.accountBalance = stoi(stracbal);
				string strcaMonthlyFee = to_string(ca.monthlyFee);
				getline(lineparts, strcaMonthlyFee, ',');
				ca.monthlyFee = stoi(strcaMonthlyFee);
				getline(lineparts, ca.checkingType, ',');
			}
		}
	}
	accountfile_read.close();
	return ca;
}


string account::get_accounttype(string accountnum)
{
	string accounttype;
	if (!verify_account(accountnum)) { cout << "Account Not found\n"; return accounttype; }

	ifstream accountfile_read;
	accountfile_read.open("accounts.txt");
	if (accountfile_read.is_open())
	{
		string line;
		string trash;
		while (getline(accountfile_read, line))
		{
			if (line.find(accountnum, 0) != string::npos) {
				istringstream lineparts(line);

				getline(lineparts, trash, ',');
				getline(lineparts, accounttype, ',');
			}
		}
	}
	accountfile_read.close();
	if (accounttype != "checking" || accounttype != "savings") { "Error: accounttype is unknown"; }
	return accounttype;
}

void account::create_account()
{

};

// Create Checking Account
void checkingAccount::create_account()
{
	checkingAccount ca;
	ca.accountType = "checking";
	ca.accountNum = to_string(generate_accountnum());

	cout << "Specify Account Name: ";
	cin >> ca.accountName;

	ca.accountBalance = 0;
	ca.checkingType = "Maximum Checking";
	ca.monthlyFee = 50;

	// Write Account to file
	ofstream accountfile_write;
	accountfile_write.open("accounts.txt", std::ios_base::app);
	if (accountfile_write.is_open())
	{
		accountfile_write << ca.accountNum + "," + ca.accountType + "," + ca.accountName + "," + to_string(ca.accountBalance) + "," + to_string(ca.monthlyFee) + "," + ca.checkingType + "\n";
		accountfile_write.close();
		cout << "Checking Account (" + ca.accountName + ") Successfully Created\n";
		ca.display_account(ca.accountNum);
	}
	else cout << "Unable to open accounts file";
}
// Create Savings Account
void savingsAccount::create_account()
{
	savingsAccount sa;
	sa.accountType = "savings";
	sa.accountNum = to_string(generate_accountnum());

	cout << "Specify Account Name: ";
	cin >> sa.accountName;

	sa.accountBalance = 5;
	sa.intrestRate = 5;
	sa.SavingsType = "UtraSavers";

	// Write Account to file
	ofstream accountfile_write;
	accountfile_write.open("accounts.txt", std::ios_base::app);
	if (accountfile_write.is_open())
	{
		accountfile_write << sa.accountNum + "," + sa.accountType + "," + sa.accountName + "," + to_string(sa.accountBalance) + "," + to_string(sa.intrestRate) + "," + sa.SavingsType + "\n";
		accountfile_write.close();
		cout << "Savings Account (" + sa.accountName + ") Successfully Created\n";
		sa.display_account(sa.accountNum);
	}

	else cout << "Unable to open accounts file";
}
bool account::verify_account(string accountnum) {

	if (accountnum.size() != 8)
	{
		cout << "Please make sure to enter a valid 8 digit account number\n";
		return false;
	}
	// Open Accounts File
	ifstream accountfile_read("accounts.txt");

	// Search through accounts file for accountnum
	bool accountFound = false;
	if (accountfile_read.is_open())
	{
		unsigned int curLine = 0;
		string line;
		while (getline(accountfile_read, line))
		{
			curLine++;
			if (line.find(accountnum, 0) != string::npos) {
				accountFound = true;
			}
		}
		accountfile_read.close();
	}

	// If found, return true
	if (accountFound == true) { return true; }
	// If not found return false
	else { return false; }
}

// Close the account
void account::close_account(string accountnum)
{
	// Verify Account is found
	if (!verify_account(accountnum)) { cout << "Account Not found\n"; return; }

	// Open Accounts File
	ifstream accountfile_read("accounts.txt");

	//Create & open Temp File
	ofstream temp("accounts_temp.txt");

	if (temp.is_open())
	{
		if (accountfile_read.is_open())
		{
			string line;
			while (getline(accountfile_read, line))
			{
				// Set line to empty if matches account number to close
				if (line.find(accountnum, 0) != string::npos) {
					line = "";
				}
				//If not the empty line
				if (!line.empty())
					temp << line << endl;
			}
			accountfile_read.close();
		}
		else { cout << "Unable to Open Accounts Folder\n"; }
		
		temp.close();

		// Replace accounts txt with updated version
		try { remove("accounts.txt"); }
		catch (...) { cout << "Error removing old accounts.txt file\n"; }
		if (rename("accounts_temp.txt", "accounts.txt")) {}
		else { cout << "Error renaming temp file to accounts.txt file"; }
	} else { cout << "Unable to Open accountstemp.txt file\n"; }
};

// Edit account info
void account::edit_account(string accountnum)
{

};

// Display account info
void account::display_account(string accountnum)
{
	if (!verify_account(accountnum)) { cout << "Account Not found\n"; return; }

	ifstream accountfile_read("accounts.txt");
	if (accountfile_read.is_open())
	{
		string line;
		while (getline(accountfile_read, line))
		{
			if (line.find(accountnum, 0) != string::npos) {
				istringstream lineparts(line);

				if (!line.empty()) 
				{
					account ac;
					getline(lineparts, ac.accountNum, ',');
					getline(lineparts, ac.accountType, ',');
					getline(lineparts, ac.accountName, ',');
					string stracbal = to_string(ac.accountBalance);
					getline(lineparts, stracbal, ',');

					cout << "\nAccount Number: " + ac.accountNum;
					cout << "\nAccount Type: " + ac.accountType;
					cout << "\nAccount Name: " + ac.accountName;
					cout << "\nAccount Balance: " + stracbal;

					if (ac.accountType == "checking")
					{
						checkingAccount ca;
						string strcaMonthlyFree = to_string(ca.monthlyFee);
						getline(lineparts, strcaMonthlyFree, ',');
						getline(lineparts, ca.checkingType, ',');

						cout << "\nChecking Monthly Fee: " + stracbal;
						cout << "\nChecking Type: " + ca.checkingType + "\n";
					}
					else if (ac.accountType == "savings")
					{
						savingsAccount sa;
						string strsaintrestRate = to_string(sa.intrestRate);
						getline(lineparts, strsaintrestRate, ',');
						getline(lineparts, sa.SavingsType, ',');

						cout << "\nSavings Intrest Rate: " + strsaintrestRate;
						cout << "\nSavings Type: " + sa.SavingsType + "\n";
					}
				}
			}
		}
		accountfile_read.close();
	}
};

int account::generate_accountnum() {
	bool accountnuminUse;
	int generatedaccountnumber;
	do
	{
		accountnuminUse = false;

		// Rand seed
		srand((unsigned)time(NULL));
		generatedaccountnumber = 10000000 + (rand() % 89999999);

		ifstream accountfile_read("accounts.txt");
		if (accountfile_read.is_open())
		{
			unsigned int curLine = 0;
			string line;
			while (getline(accountfile_read, line))
			{
				curLine++;
				if (line.find(generatedaccountnumber, 0) != string::npos) {
					accountnuminUse = true;
				}
			}
			accountfile_read.close();
		}
		else cout << "Unable to open accounts file";
	} while (accountnuminUse);

	return generatedaccountnumber;
}

// Deposit to account
void account::deposit_account(string accountnum)
{
	if (!verify_account(accountnum)) { cout << "Account Not found\n"; return; }

	entry ent;
	ent.accountnum = accountnum;
	ent.amount = NULL;
	// Get amount to deposit
	do {
		string stramount;
		cout << "Please enter the amount to deposit: ";
		cin >> stramount;

		try
		{
			ent.amount = stoi(stramount);
		}
		catch (const std::exception&)
		{
			"Please enter a valid number";
		}
	} while (ent.amount == NULL);

	// Get type (Cash or check)
	do {
		cout << "Please enter type of deposit (cash or check): ";
		cin >> ent.type;
		if (ent.type != "cash" && ent.type != "check") { cout << "Please try again"; }
	} while (ent.type != "cash" && ent.type != "check");

	ent.direction = "Deposit";

	cout << "Please enter a description for your deposit: ";
	cin >> ent.description;

	account ac;
	if (ac.get_accounttype(accountnum) == "checking") 
	{
		checkingAccount ca = ca.get_account(accountnum);
		ca = ca + ent.amount;
		ca.update_account(ca);
		ca.recordlog_account(ent);
		display_account(ca.accountNum);
	}
	else if (ac.get_accounttype(accountnum) == "savings")
	{
		savingsAccount sa = sa.get_account(accountnum);
		sa = sa + ent.amount;
		sa.update_account(sa);
		sa.recordlog_account(ent);
		display_account(sa.accountNum);
	}
	else { cout << "Unable deposit: Unknown account type"; }
};

// Withdrawl from account
void account::withdrawl_account(string accountnum)
{
	if (!verify_account(accountnum)) { cout << "Account Not found\n"; return; }

	entry ent;
	ent.accountnum = accountnum;
	ent.amount = NULL;
	// Get amount to deposit
	do {
		string stramount;
		cout << "Please enter the amount to withdrawl: ";
		cin >> stramount;

		try
		{
			ent.amount = stoi(stramount);
		}
		catch (const std::exception&)
		{
			"Please enter a valid number";
		}
	} while (ent.amount == NULL);

	// Get type (Cash or check)
	do {
		cout << "Please enter type of wi (cash or check): ";
		cin >> ent.type;
		if (ent.type != "cash" && ent.type != "check") { cout << "Please try again"; }
	} while (ent.type != "cash" && ent.type != "check");

	ent.direction = "Withdrawl";

	cout << "Please enter a description for your Withdrawl: ";
	cin >> ent.description;

	account ac;
	if (ac.get_accounttype(accountnum) == "checking")
	{
		checkingAccount ca = ca.get_account(accountnum);
		if (ca.accountBalance >= ent.amount)
		{
			ca = ca - ent.amount;
			ca.update_account(ca);
			ca.recordlog_account(ent);
			display_account(ca.accountNum);
		}
		else { cout << "\nNot Enough funds in account to withdrawl\n Current balance: " + to_string(ca.accountBalance) + "\nRequested Amount: " + to_string(ent.amount) + "\n"; }
	}
	else if (ac.get_accounttype(accountnum) == "savings")
	{
		savingsAccount sa = sa.get_account(accountnum);
		if (sa.accountBalance >= ent.amount) 
		{
			sa = sa - ent.amount;
			sa.update_account(sa);
			sa.recordlog_account(ent);
			display_account(sa.accountNum);
		}
		else { cout << "\nNot Enough funds in account to withdrawl\n Current balance: " + to_string(sa.accountBalance) + "\nRequested Amount: " + to_string(ent.amount) + "\n"; }
	}
	else { cout << "Unable deposit: Unknown account type"; }
};

void checkingAccount::update_account(checkingAccount ca)
{
	// Verify Account is found
	if (!verify_account(ca.accountNum)) { cout << "Account Not found\n"; return; }

	// Open Accounts File
	ifstream accountfile_read("accounts.txt");

	//Create & open Temp File
	ofstream temp("accounts_temp.txt");

	if (temp.is_open())
	{
		if (accountfile_read.is_open())
		{
			string line;
			while (getline(accountfile_read, line))
			{
				// Set line to empty if matches account number to close
				if (line.find(ca.accountNum, 0) != string::npos) {
					line = ca.accountNum + "," + ca.accountType + "," + ca.accountName + "," + to_string(ca.accountBalance) + "," + to_string(ca.monthlyFee) + "," + ca.checkingType + "\n";
				}
				//If not the empty line
				if (!line.empty())
					temp << line << endl;
			}
			accountfile_read.close();
		}
		else { cout << "Unable to Open Accounts Folder\n"; }

		temp.close();

		// Replace accounts txt with updated version
		try { remove("accounts.txt"); }
		catch (...) { cout << "Error removing old accounts.txt file\n"; }
		if (rename("accounts_temp.txt", "accounts.txt") != 0) { cout << "Error renaming temp file to accounts.txt file\n"; }
	}
	else { cout << "Unable to Open accountstemp.txt file\n"; }
}

void savingsAccount::update_account(savingsAccount sa)
{
	// Verify Account is found
	if (!verify_account(sa.accountNum)) { cout << "Account Not found\n"; return; }

	// Open Accounts File
	ifstream accountfile_read("accounts.txt");

	//Create & open Temp File
	ofstream temp("accounts_temp.txt");

	if (temp.is_open())
	{
		if (accountfile_read.is_open())
		{
			string line;
			while (getline(accountfile_read, line))
			{
				// Set line to empty if matches account number to close
				if (line.find(sa.accountNum, 0) != string::npos) {
					line = sa.accountNum + "," + sa.accountType + "," + sa.accountName + "," + to_string(sa.accountBalance) + "," + to_string(sa.intrestRate) + "," + sa.SavingsType + "\n";
				}
				//If not the empty line
				if (!line.empty())
					temp << line << endl;
			}
			accountfile_read.close();
		}
		else { cout << "Unable to Open Accounts Folder\n"; }

		temp.close();

		// Replace accounts txt with updated version
		try { remove("accounts.txt"); }
		catch (...) { cout << "Error removing old accounts.txt file\n"; }
		if (rename("accounts_temp.txt", "accounts.txt") != 0) { cout << "Error renaming temp file to accounts.txt file\n"; }
	}
	else { cout << "Unable to Open accountstemp.txt file\n"; }
}


// Display History
void account::dislaylog_account(string accountnum)
{
	// Make sure account number has 8 digits (Doesnt have to be existing account, could be deprecated)
	if (accountnum.size() != 8)
	{
		cout << "Please make sure to enter a valid 8 digit account number\n";
		return;
	}

	ifstream accountTransactionLog_read("accountTransactionLog.log");
	if (accountTransactionLog_read.is_open())
	{
		string line;
		while (getline(accountTransactionLog_read, line))
		{
			if (line.find(accountnum, 0) != string::npos) {
				istringstream lineparts(line);

				if (!line.empty())
				{
					entry ent;
					getline(lineparts, ent.accountnum, ',');
					string strentAmount;
					getline(lineparts, strentAmount, ',');
					getline(lineparts, ent.description, ',');
					getline(lineparts, ent.direction, ',');
					getline(lineparts, ent.type, ',');

					cout << "\nAccount Number: " + ent.accountnum;
					cout << "\nTransaction Amount: " + strentAmount;
					cout << "\nTransaction Description: " + ent.description;
					cout << "\nTransaction Type: " + ent.direction;
					cout << "\nTransaction Method: " + ent.type + "\n";
				}
			}
		}
		accountTransactionLog_read.close();
	}
};

// Record History
void account::recordlog_account(entry ent)
{
	// Write Account to file
	ofstream accountTransactionLog_write;
	accountTransactionLog_write.open("accountTransactionLog.log", std::ios_base::app);
	if (accountTransactionLog_write.is_open())
	{
		accountTransactionLog_write << ent.accountnum + "," + to_string(ent.amount) + "," + ent.description+ "," + ent.direction + "," + ent.type + "\n";
		accountTransactionLog_write.close();
	}
	else cout << "Unable to open accountTransactionLog_write file";
};

/// User Actions ///

// Create user account
void User::Create_User()
{

}
// Delete user account
void User::Delete_User()
{

}
// Edit user account
void User::Edit_User()
{

}
// Attempt Login to user account
int User::Login_User(string username, string password)
{
	int loginatloginresult = 0;
	if (username == "Jake" && password == "Pass123") {
		loginatloginresult = 1;
	}
	return loginatloginresult;
}

// Logoff user account
int User::Logoff_User()
{
	return 0;
}

void User::DisplayAll_User()
{


}

//// ================================ Operators ================================ ////

account operator+(account ac, int entAmount)
{
	ac.accountBalance = ac.accountBalance + entAmount;
	return ac;
}

checkingAccount operator+(checkingAccount ca, int entAmount)
{
	ca.accountBalance = ca.accountBalance + entAmount;
	return ca;
}

savingsAccount operator+(savingsAccount sa, int entAmount)
{
	sa.accountBalance = sa.accountBalance + entAmount;
	return sa;
}

account operator-(account ac, int entAmount)
{
	ac.accountBalance = ac.accountBalance - entAmount;
	return ac;
}

checkingAccount operator-(checkingAccount ca, int entAmount)
{
	ca.accountBalance = ca.accountBalance - entAmount;
	return ca;
}

savingsAccount operator-(savingsAccount sa, int entAmount)
{
	sa.accountBalance = sa.accountBalance - entAmount;
	return sa;
}


//// ================================ Other Methods ================================ ////
///  Tranaction Log ///
void ll_transaction_log::add_node(string trans)
{
	node* tmp = new node;
	tmp->transaction = trans;
	tmp->next = NULL;

	if (head == NULL)
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		tail->next = tmp;
		tail = tail->next;
	}
}

ll_transaction_log ll_transaction_log::load_list()
{
	ll_transaction_log translog;
	ifstream accountTransactionLog_read("accountTransactionLog.log");
	
	if (accountTransactionLog_read.is_open())
	{
		string line;
		while (getline(accountTransactionLog_read, line))
		{
			translog.add_node(line);
		}
		accountTransactionLog_read.close();
	}
	else { cout << "\nUnable to open Transaction Log\n"; }
	return translog;
}

void ll_transaction_log::display()
{
	node* tmp;
	tmp = head;
	while (tmp != NULL)
	{
		account ac;
		ac.dislaylog_account((tmp->transaction).substr(0, 8));
		tmp = tmp->next;
	}
}

/// Seclection Page Actions ///
int loginMenu()
{
	int selectedoption = -1;
	while (selectedoption < 0 || selectedoption > 5)
	{
		std::cout << "\nType 1 to Display All accounts ";
		std::cout << "\nType 2 to look at specifc account ";
		std::cout << "\nType 3 to edit current user ";
		std::cout << "\nType 4 to edit delete current user ";
		std::cout << "\nType 5 to Display Transaction Log for All Accounts ";
		std::cout << "\nType 0 to Logoff: ";
		std::cin >> selectedoption;
	}
	return selectedoption;
}
// Selection function for User Page
int userMenu()
{
	return 0;
}

// Selection function for Single Account Page
int accountMenu()
{
	int selectedoption = -1;
	while (selectedoption < 0 || selectedoption > 7)
	{
		std::cout << "\nType 1 to create an new account ";
		std::cout << "\nType 2 to delete an account ";
		std::cout << "\nType 3 to edit an account ";
		std::cout << "\nType 4 to display an account";
		std::cout << "\nType 5 to deposit to an account ";
		std::cout << "\nType 6 to withdrawl from an account ";
		std::cout << "\nType 7 to display transaction log";
		std::cout << "\nType 0 to go back: ";
		std::cin >> selectedoption;
	}
	return selectedoption;
}

//// ================================ Main ================================ ////
int main()
{
	// Call Classes
	User User;
	account account;
	allAccounts allAccounts;

	bool applicationrun = true;
	while (applicationrun)
	{
		std::cout << "\nEnter Login Name ";
		std::cout << "\nOr Type 1 for account creation";
		std::cout << "\nOr Type 0 to leave\n";

		string username;
		std::cin >> username;
		// Login Page
		if (username == "1")
		{
			// Create User
			User.Create_User();

		}
		else if (username == "0")
		{
			// Leave App
			applicationrun = false;
		}
		else
		{
			bool attemptinglogin = true;
			while (attemptinglogin)
			{
				// Attempting login
				std::cout << "\nEnter your password or type 0 to go back: ";
				string password;
				std::cin >> password;

				//Login
				if (password == "0") { attemptinglogin = false; }
				else if (User.Login_User(username, password) == 1)
				{
					bool login = true;
					std::cout << "\nSuccessfully Logged in!\n";
					while (login)
					{
						int optionselected = loginMenu();
						switch (optionselected)
						{
						case 1:
							allAccounts.Display_accounts();  // Bulk account option
							break;
						case 2:
						{
							bool accountmenu = true;
							while (accountmenu)
							{
								int accountoptionselected = accountMenu();
								switch (accountoptionselected)
								{
								case 1: { // Create account
									string accountType;
									// Gather Account number Details
									std::cout << "\nEnter specify account type (checking or savings): ";
									std::cin >> accountType;
									if (accountType == "checking") { checkingAccount ca;  ca.create_account(); }
									else if (accountType == "savings") { savingsAccount sa;  sa.create_account(); }
									break;
								}
								case 2: { // Delete Account
									string accountnum;
									// Gather Account number Details
									std::cout << "\nEnter specify account number to close: ";
									std::cin >> accountnum;
									account.close_account(accountnum);
									break;
								}
								case 3: break;// Edit
								case 4: { // Display Account
									string accountnum;
									// Gather Account number Details
									std::cout << "\nEnter specify account number to display: ";
									std::cin >> accountnum;
									account.display_account(accountnum);
									break;
								}
								case 5: { // Deposit
									string accountnum;
									// Gather Account number Details
									std::cout << "\nEnter specify account number to Deposit into: ";
									std::cin >> accountnum;
									account.deposit_account(accountnum);
									break;
								}
								case 6: { // Withdrawl
									string accountnum;
									// Gather Account number Details
									std::cout << "\nEnter specify account number to Withdrawl from: ";
									std::cin >> accountnum;
									account.withdrawl_account(accountnum);
									break;
								}
								case 7: { // Display Transaction Log
									string accountnum;
									// Gather Account number Details
									std::cout << "\nEnter specify account number to check for transactions: ";
									std::cin >> accountnum;
									account.dislaylog_account(accountnum);
									break;
								}
								case 0: accountmenu = false; break; // Go Back
								}
							// Clear Input Buffer 
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							}
						}
						break;
						case 3:
							User.Edit_User(); // Edit User
							break;
						case 4:
							User.Delete_User(); // Delete User 
							break;
						case 5:
							allAccounts.Display_AllTranactions(); // Display Transaction Log for all entries
							break;
						case 0:
							std::cout << "Logged Off...\n";
							login = false;
							attemptinglogin = false; // Logoff
							break;
						}
						// Clear Input Buffer 
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
				}
				else { std::cout << "\nTry Again..."; }
				// Clear Input Buffer 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		// Clear Input Buffer 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return 0;
}