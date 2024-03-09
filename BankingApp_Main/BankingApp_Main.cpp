#include<iostream>
#include<list>
#include<string>
#include<cctype>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;


//// ================================ Classes ================================ ////
class entry // Entry class for transactions
{
public:
	string accountnum;
	string description;
	string type;
	string direction;
	float amount;
	float beforebalance;
	float afterbalance;
};

class allAccounts // Bulk bank account options class
{
	string accountNum;
public:
	void Display_accounts();
	void Display_AllTranactions();
};

class account // bank account class
{
	friend account operator+(account ac, float entAmount);
	friend account operator-(account ac, float entAmount);
	friend account operator*(account ac, float intrest_rate);
public:
	string accountNum;
	string accountName;
	string accountType;
	float accountBalance;
	static float overdraft_account_fees;
	static float account_intrestrate;
	void create();
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
	void overdraft_account(string accountnum);
};

class savingsAccount : public account // bank savings type account class
{
	friend savingsAccount operator+(savingsAccount sa, float entAmount);
	friend savingsAccount operator-(savingsAccount sa, float entAmount);
	friend savingsAccount operator*(savingsAccount sa, float intrest_rate);
public:
	static float overdraft_saaccount_fees;
	static float saaccount_intrestrate;
	void overdraft_account(string accountnum, savingsAccount sa);
	void create();
	float intrestRate;
	string SavingsType;
	savingsAccount get_account(string accountnum);
	void update_account(savingsAccount sa);
};

class checkingAccount : public account // bank checking type account class
{  
	friend checkingAccount operator+(checkingAccount ca, float entAmount);
	friend checkingAccount operator-(checkingAccount ca, float entAmount);
	friend checkingAccount operator*(checkingAccount ca, float intrest_rate);
public:
	static float overdraft_caaccount_fees;
	static float caaccount_intrestrate;
	void overdraft_account(string accountnum, checkingAccount ca);
	void create();
	float monthlyFee;
	string checkingType;
	checkingAccount get_account(string accountnum);
	void update_account(checkingAccount ca);
};

class intrest
{
	float apr;
public:
	account calculate(account ac);
	checkingAccount calculate(checkingAccount ca);
	savingsAccount calculate(savingsAccount sa);
	void invoke_all();
};

class User
{
public:
	string userName;
	string password;
	string accounts;
	string firstName;
	string lastName;
	void Display_User(User u);
	void Create_User();
	void Delete_User();
	void Edit_User();
	int Login_User(string username, string password);
	int Logoff_User();
	void DisplayAll_User();
};

//// ================================ Linked Lists ================================ ////
// User Linked List
struct usernode
{
	User usr;
	usernode* next;
};

class User_List
{
	usernode* head, * tail;
public:
	User_List()
	{
		head = NULL;
		tail = NULL;
	}
	void add_node(User u);
	User_List load_list();
	void display();
};

// Transaction log List
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

// account List
struct accnode
{
	string account;
	accnode* next;
};

class acc_list
{
	accnode* head, * tail;
public:
	acc_list()
	{
		head = NULL;
		tail = NULL;
	}
	void add_node(string account);
	acc_list load_list();
	void display();
	void invoke_intrest();
};
//// ================================ Constants ================================ ////
float account::overdraft_account_fees = 30.00;
float savingsAccount::overdraft_saaccount_fees = 50.00;
float checkingAccount::overdraft_caaccount_fees = 25.00;
float account::account_intrestrate = .05;
float savingsAccount::saaccount_intrestrate = .12;
float checkingAccount::caaccount_intrestrate = .3;



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
				sa.accountBalance = stof(stracbal);
				string strsaintrestRate = to_string(sa.intrestRate);
				getline(lineparts, strsaintrestRate, ',');
				sa.intrestRate = stof(strsaintrestRate);
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
				ca.accountBalance = stof(stracbal);
				string strcaMonthlyFee = to_string(ca.monthlyFee);
				getline(lineparts, strcaMonthlyFee, ',');
				ca.monthlyFee = stof(strcaMonthlyFee);
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

void account::create()
{

};

// Create Checking Account
void checkingAccount::create()
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
void savingsAccount::create()
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
						string strcaMonthlyFee = to_string(ca.monthlyFee);
						getline(lineparts, strcaMonthlyFee, ',');
						getline(lineparts, ca.checkingType, ',');

						cout << "\nChecking Monthly Fee: " + strcaMonthlyFee;
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
// Generate account number that is unique
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
			ent.amount = stof(stramount);
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
			ent.amount = stof(stramount);
		}
		catch (const std::exception&)
		{
			"Please enter a valid number";
		}
	} while (ent.amount == NULL);

	// Get type (Cash or check)
	do {
		cout << "Please enter type of withdrawl (cash or check): ";
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
		else
		{
			string overdraft;
			do {
				cout << "\nCurrent balance: " + to_string(ca.accountBalance) + "\nRequested Amount: " + to_string(ent.amount) + +"\nOverdraft Fee: " + to_string(checkingAccount::overdraft_caaccount_fees) + "\nNot Enough funds in account to withdrawl..\n" + "Would you like to use Overdraft Protection (yes or no)? ";
				cin >> overdraft;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (overdraft != "yes" && overdraft != "no") { cout << "\nNot a valid response. Please try again... \n"; }
			} while (overdraft != "yes" && overdraft != "no");
			if (overdraft == "yes")
			{
				// Overdraft Entry & Fee calculated
				ca.overdraft_account(ca.accountNum, ca);
				ca = ca - checkingAccount::overdraft_caaccount_fees;

				// Transaction Balance before and after (after fees)
				ent.beforebalance = ca.accountBalance; // Account Balance before overdraft
				ca = ca - ent.amount;
				ent.afterbalance = ca.accountBalance; // Account Balance after Withdrawl

				// Update account, record transaction, display account
				ca.update_account(ca);
				ca.recordlog_account(ent);
				display_account(ca.accountNum);
			}
			else { "\nNo Transaction has been committed. \n"; }
		}
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
		else 
		{ 
			string overdraft;
			do {
				cout << "\nCurrent balance: " + to_string(sa.accountBalance) + "\nRequested Amount: " + to_string(ent.amount) + +"\nOverdraft Fee: " + to_string(savingsAccount::overdraft_saaccount_fees) + "\nNot Enough funds in account to withdrawl..\n" + "Would you like to use Overdraft Protection (yes or no)? ";
				cin >> overdraft;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (overdraft != "yes" && overdraft != "no") { cout << "\nNot a valid response. Please try again... \n"; }
			} while (overdraft != "yes" && overdraft != "no");
			if (overdraft == "yes") 
			{
				// Overdraft Entry & Fee calculated
				sa.overdraft_account(sa.accountNum, sa);
				sa = sa - savingsAccount::overdraft_saaccount_fees;

				// Transaction Balance before and after (after fees)
				ent.beforebalance = sa.accountBalance; // Account Balance before overdraft
				sa = sa - ent.amount;
				ent.afterbalance = sa.accountBalance; // Account Balance after Withdrawl

				// Update account, record transaction, display account
				sa.update_account(sa);
				sa.recordlog_account(ent);
				display_account(sa.accountNum);
			}
			else { "\nNo Transaction has been committed. \n"; }
		} 
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

// Update Accounts file with new account details
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

// Display transactionlog
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
					string strBeforeBal;
					getline(lineparts, strBeforeBal, ',');
					string strAfterBal;
					getline(lineparts, strAfterBal, ',');

					cout << "\nAccount Number: " + ent.accountnum;
					cout << "\nTransaction Amount: " + strentAmount;
					cout << "\nTransaction Description: " + ent.description;
					cout << "\nTransaction Type: " + ent.direction;
					cout << "\nTransaction Method: " + ent.type;
					cout << "\nPrior Balance: " + strBeforeBal;
					cout << "\nAfter Balance: " + strAfterBal + "\n";
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
		accountTransactionLog_write << ent.accountnum + "," + to_string(ent.amount) + "," + ent.description+ "," + ent.direction + "," + ent.type + "," + to_string(ent.beforebalance) + "," + to_string(ent.afterbalance) + "\n";
		accountTransactionLog_write.close();
	}
	else cout << "Unable to open accountTransactionLog_write file";
};

// Overdraft fee & Transaction recording for it
void account::overdraft_account(string accountnum)
{

}

void checkingAccount::overdraft_account(string accountnum, checkingAccount ca) 
{	
	entry overdraft_entry;
	overdraft_entry.accountnum = accountnum;
	overdraft_entry.amount = checkingAccount::overdraft_caaccount_fees;
	overdraft_entry.description = "Overdraft Fee";
	overdraft_entry.direction = "Withdrawl";
	overdraft_entry.type = "Digital";
	overdraft_entry.beforebalance = ca.accountBalance;
	overdraft_entry.afterbalance = ca.accountBalance - checkingAccount::overdraft_caaccount_fees;
	recordlog_account(overdraft_entry);
}

void savingsAccount::overdraft_account(string accountnum, savingsAccount sa)
{
	entry overdraft_entry;
	overdraft_entry.accountnum = accountnum;
	overdraft_entry.amount = savingsAccount::overdraft_saaccount_fees;
	overdraft_entry.description = "Overdraft Fee";
	overdraft_entry.direction = "Withdrawl";
	overdraft_entry.type = "Digital";
	overdraft_entry.beforebalance = sa.accountBalance;
	overdraft_entry.afterbalance = sa.accountBalance - savingsAccount::overdraft_saaccount_fees;

	recordlog_account(overdraft_entry);
}


//
account intrest::calculate(account ac)
{
	ac = ac * account::account_intrestrate;
	return ac;
}

savingsAccount intrest::calculate(savingsAccount sa)
{
	sa = sa * savingsAccount::saaccount_intrestrate;
	return sa;
}

checkingAccount intrest::calculate(checkingAccount ca)
{
	ca = ca * checkingAccount::caaccount_intrestrate;
	return ca;
}

void intrest::invoke_all() 
{
	try 
	{
		acc_list acclist;
		acclist = acclist.load_list();
		acclist.invoke_intrest();

		cout << "\nIntrest successfully calculated...\n";
	}
	catch (...) { cout << "Error calculating intrest"; }
}

/// User Actions ///
void User::Display_User(User u)
{
	cout << "\n Username: " + u.userName;
	cout << "\n Password: " + u.password;
	cout << "\n First Name: " + u.firstName;
	cout << "\n Last Name: " + u.lastName;
	cout << "\n Accounts: " + u.accounts + "\n";
}
// Create user account
void User::Create_User()
{
	User u;

	// Username
	cout << "\nPlease specify a Username: ";
	cin >> u.userName;

	// Password
	cout << "\nPlease specify a password: ";
	cin >> u.password;

	// Username
	cout << "\nPlease type your first name: ";
	cin >> u.firstName;

	// Password
	cout << "\nPlease type your last name: ";
	cin >> u.lastName;

	// Account numbers user should have access too
	account ac;
	string accountnum;
	string accontinue;
	do {
		cout << "\nPlease specify an account number you should have access to type 0 to skip: ";
		cin >> accountnum;

		if (accountnum == "0") { accontinue = "no"; }
		else if (!ac.verify_account(accountnum)) { cout << "\nThe account number does not exist.. try again..."; accontinue = "yes"; } // Verify account exists
		else { 
			u.accounts += accountnum + "|";   // If exists, add to list with | as delimiter

			cout << "\nDo you have another accountnumber to add? (yes or no): ";
			cin >> accontinue;
		}
	} while (accontinue == "yes");

	// Write Account to file
	ofstream users_write;
	users_write.open("users.txt", std::ios_base::app);
	if (users_write.is_open())
	{
		users_write << u.userName + "," + u.password + "," + u.firstName + "," + u.lastName + "," + u.accounts + "\n";
		users_write.close();
		cout << "\nAccount Successfully Created!!!\n";
	}
	else cout << "Unable to open Users_write file";
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
	User_List userdir;
	userdir.load_list();

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
	User_List ulist;
	ulist = ulist.load_list();
	ulist.display();
}

//// ================================ Operators ================================ ////

// Deposit operator
account operator+(account ac, float entAmount)
{
	ac.accountBalance = ac.accountBalance + entAmount;
	return ac;
}

checkingAccount operator+(checkingAccount ca, float entAmount)
{
	ca.accountBalance = ca.accountBalance + entAmount;
	return ca;
}

savingsAccount operator+(savingsAccount sa, float entAmount)
{
	sa.accountBalance = sa.accountBalance + entAmount;
	return sa;
}

// Withdrawl operator
account operator-(account ac, float entAmount)
{
	ac.accountBalance = ac.accountBalance - entAmount;
	return ac;
}

checkingAccount operator-(checkingAccount ca, float entAmount)
{
	ca.accountBalance = ca.accountBalance - entAmount;
	return ca;
}

savingsAccount operator-(savingsAccount sa, float entAmount)
{
	sa.accountBalance = sa.accountBalance - entAmount;
	return sa;
}

// Intrest Operator
account operator*(account ac, float intrest_rate)
{
	ac.accountBalance = ac.accountBalance * (1 + intrest_rate);
	return ac;
}

checkingAccount operator*(checkingAccount ca, float intrest_rate)
{
	ca.accountBalance = ca.accountBalance * (1 + intrest_rate);
	return ca;
}

savingsAccount operator*(savingsAccount sa, float intrest_rate)
{
	sa.accountBalance = sa.accountBalance * (1 + intrest_rate);
	return sa;
}


//// ================================ Linked Lists ================================ ////
/// User List ///
// Add Nodes to Linked List
void User_List::add_node(User u)
{
	usernode* tmp = new usernode;
	tmp->usr = u;
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
// Load Linked list from File Save
User_List User_List::load_list()
{
	User_List ulist;
	ifstream users_read("users.txt");
	User u;

	if (users_read.is_open())
	{
		string line;
		while (getline(users_read, line))
		{
			istringstream lineparts(line);
			getline(lineparts, u.userName, ',');
			getline(lineparts, u.password, ',');
			getline(lineparts, u.firstName, ',');
			getline(lineparts, u.lastName, ',');
			getline(lineparts, u.accounts, ',');
			ulist.add_node(u);
		}
		users_read.close();
	}
	else { cout << "\nUnable to open User file\n"; }
	return ulist;
}
// Display contents of linked list
void User_List::display()
{
	usernode* tmp;
	tmp = head;
	while (tmp != NULL)
	{
		User u;
		u.Display_User(tmp->usr);
		tmp = tmp->next;
	}
}


///  Tranaction Log ///
// Add Nodes to Linked List
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
// Load Linked list from File Save
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
// Display contents of linked list
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

///  Accounts List ///
// Add Nodes to Linked List
void acc_list::add_node(string account)
{
	accnode* tmp = new accnode;
	tmp->account = account;
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
// Load Linked list from File Save
acc_list acc_list::load_list()
{
	acc_list acclist;
	ifstream accountfile_read("accounts.txt");

	if (accountfile_read.is_open())
	{
		string line;
		while (getline(accountfile_read, line))
		{
			acclist.add_node(line);
		}
		accountfile_read.close();
	}
	else { cout << "\nUnable to open accounts list\n"; }
	return acclist;
}
// Display contents of linked list
void acc_list::display()
{
	accnode* tmp;
	tmp = head;
	while (tmp != NULL)
	{
		account ac;
		ac.display_account((tmp->account).substr(0, 8));
		tmp = tmp->next;
	}
}

// Display contents of linked list
void acc_list::invoke_intrest()
{
	accnode* tmp;
	tmp = head;
	while (tmp != NULL)
	{
		intrest intrest;
		account ac;
		string accountnum;
		accountnum = ((tmp->account).substr(0, 8));
		if (ac.get_accounttype(accountnum) == "savings")
		{
			savingsAccount sa = sa.get_account(accountnum);
			sa = intrest.calculate(sa);
			sa.update_account(sa);
		}
		else if (ac.get_accounttype(accountnum) == "checking")
		{
			checkingAccount ca = ca.get_account(accountnum);
			ca = intrest.calculate(ca);
			ca.update_account(ca);
		}

		tmp = tmp->next;
	}
}

//// ================================ Menus ================================ ////
/// Seclection Page Actions ///
int loginMenu()
{
	int selectedoption = -1;
	while (selectedoption < 0 || selectedoption > 6)
	{
		std::cout << "\nType 1 to display all accounts ";
		std::cout << "\nType 2 for singular account operations ";
		std::cout << "\nType 3 to edit current user ";
		std::cout << "\nType 4 to delete current user ";
		std::cout << "\nType 5 to display transaction log for all accounts ";
		std::cout << "\nType 6 to invoke intrest on all accounts ";
		std::cout << "\nType 0 to logoff: ";
		std::cin >> selectedoption;
	}
	return selectedoption;
}
// Selection function for User Page
int adminMenu()
{
	int selectedoption = -1;
	while (selectedoption < 0 || selectedoption > 3)
	{
		std::cout << "\nType 1 to create an new user ";
		std::cout << "\nType 2 to delete a user";
		std::cout << "\nType 3 to display all users ";
		std::cout << "\nType 0 to go back: ";
		std::cin >> selectedoption;
	}
	return selectedoption;
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
	intrest intrest;


	bool applicationrun = true;
	while (applicationrun)
	{

		std::cout << "\nEnter Username to login ";
		std::cout << "\nOr Type 1 for admin operations ";
		std::cout << "\nOr Type 0 to leave\n";

		string username;
		std::cin >> username;
		// Login Page
		if (username == "1")
		{
			bool adminops = true;
			while (adminops)
			{
				int adminoptionselected = adminMenu();
				switch (adminoptionselected)
				{
				case 1: { // Create User
					User.Create_User();
					break;
				}
				case 2: { // Delete User
					User.Delete_User();
					break;
				}
				case 3: { // Display All Users User
					User.DisplayAll_User();
					break;
				}
				case 0: { // Create User
					adminops = false;
					break;
				}
					  // Clear Input Buffer 
					  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
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

				//string success;
				//success = User.Login_User(username, password);
				//cout << success;

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
									if (accountType == "checking") { checkingAccount ca;  ca.create(); }
									else if (accountType == "savings") { savingsAccount sa;  sa.create(); }
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
						case 6:
							intrest.invoke_all(); // Invoke intrest on all accounts
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