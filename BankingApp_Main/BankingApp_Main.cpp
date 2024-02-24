#include<iostream>
#include<list>
#include<string>
#include<cctype>
#include<fstream>
using namespace std;


//// Classes ////
class allAccounts
{
	int accountNum;
public:
	void Display_accounts();
};

class account
{
public:
	int accountNum;
	string accountName;
	string accountType;
	int accountBalance;
	void create_account();
	void close_account();
	void edit_account();
	void display_account(string accountnum);
	void deposit_account();
	void withdrawl_account();
	void dislaylog_account();
	void recordlog_account();
};

class savingsAccount: public account 
{
public:
	void display_account(string accountnum);
	void create_account();
	int intrestRate;
	string SavingsType;
};

class checkingAccount: public account
{
public:
	void display_account(string accountnum);
	void create_account();
	int monthlyFee;
	string checkingType;
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
class entry
{
	string description;
	string type;
	int amount;
};

//// Functions ////
/// Bulk Account Actions ///
void allAccounts::Display_accounts()
{
	cout << "Hello";
};

/// Single Account Actions ///
// Create the account
int generate_accountnum(){
	bool accountnuminUse;
	int generatedaccountnumber;
	do
	{
		accountnuminUse = false;

		// Rand seed
		srand((unsigned)time(NULL));
		generatedaccountnumber = 00000000 + (rand() % 99999999);

		ifstream accountfile_read;
		accountfile_read.open("accounts.txt");
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
void account::create_account()
{

};


// Create Checking Account
void checkingAccount::create_account()
{
	checkingAccount ca;
	ca.accountType = "checking";
	ca.accountNum = generate_accountnum();

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
		accountfile_write << to_string(ca.accountNum) + ", " + ca.accountType + ", " + ca.accountName + ", " + to_string(ca.accountBalance) + ", " + to_string(ca.monthlyFee) + ", " + ca.checkingType + "\n";
		accountfile_write.close();
		cout << "Checking Account (" + ca.accountName + ") Successfully Created";
	}
	else cout << "Unable to open accounts file";
}
// Create Savings Account
void savingsAccount::create_account()
{
	savingsAccount sa;
	sa.accountType = "savings";
	sa.accountNum = generate_accountnum();

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
		accountfile_write << to_string(sa.accountNum) + ", " + sa.accountType + ", " + sa.accountName + ", " + to_string(sa.accountBalance) + ", " + to_string(sa.intrestRate) + ", " + sa.SavingsType + "\n";
		accountfile_write.close();
		cout << "Savings Account (" + sa.accountName + ") Successfully Created";
	}
	else cout << "Unable to open accounts file";
}

// Close the account
void account::close_account()
{

};

// Edit account info
void account::edit_account()
{

};

// Display account info
void account::display_account(string accountnum)
{
	ifstream accountfile_read;
	accountfile_read.open("accounts.txt");
	if (accountfile_read.is_open())
	{
		unsigned int curLine = 0;
		string line;
		while (getline(accountfile_read, line))
		{
			curLine++;
			if (line.find(accountnum, 0) != string::npos) {
				cout << line + "\n";
			}
		}
		accountfile_read.close();
	}
};

// Deposit to account
void account::deposit_account()
{

};

// Withdrawl from account
void account::withdrawl_account()
{

};

// Display History
void account::dislaylog_account()
{

};

// Record History
void account::recordlog_account()
{

};

/// Seclection Page Actions ///

// Selection function for Login Page
int loginMenu()
{	
	int selectedoption = -1;
	while (selectedoption < 0 || selectedoption > 4) 
	{
		std::cout << "\nType 1 to Display All accounts ";
		std::cout << "\nType 2 to look at specifc account ";
		std::cout << "\nType 3 to edit current user ";
		std::cout << "\nType 4 to edit delete current user ";
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
		std::cout << "\nType 0 to Logoff: ";
		std::cin >> selectedoption;
	}
	return selectedoption;
}


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

//// Main ////
int main()
{
	// Call Classes
	User User;
	account account;
	allAccounts allAccounts;

	bool applicationrun = true;
	while(applicationrun)
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
								} 
								case 2: break;// Delete
								case 3: break;// Edit
								case 4: { // Display Account
									string accountnum;
									// Gather Account number Details
									std::cout << "\nEnter specify account number to display: ";
									std::cin >> accountnum;
									account.display_account(accountnum);
								}
								case 5: break;// Deposit
								case 6: break;// Withdrawl
								case 7: break;// Display Transaction Log
								case 0: accountmenu = false; break; // Go Back
								}
							}
						}
							break;
						case 3: 
							User.Edit_User(); // Edit User
							break;
						case 4: 
							User.Delete_User(); // Delete User 
							break;
						case 0: 
							std::cout << "Logged Off...\n";  
							login = false; 
							attemptinglogin = false; // Logoff
							break;
						}
					}
				}
				else { std::cout << "\nTry Again..."; }
			}
		}
	}
	return 0;
}