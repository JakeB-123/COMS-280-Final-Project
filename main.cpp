#include<iostream>
#include <list>
using namespace std;


//// Classes ////
class account 
{
	int accountNum;
	int accountName;
	char accountType;
	int accountBalance;
public:
	void create_account();
	void close_account();
	void edit_account();
	void display_account();
	void deposit_account();
	void withdrawl_account();
	void dislaylog_account();
	void recordlog_account();
}

class user 
{
	char userName;
	char password;
	list accounts;
	char firstname;
	char lastname;
public:
		void Create();
		void Delete();
		void Edit();
		void Login();
		void Logoff();
}



//// Functions ////
/// Bulk Account Actions ///
private void allAccounts::Display_accounts()
{

}

/// Single Account Actions ///
// Create the account
private void account::create_account()
{

} 

// Close the account
private void account::close_account()
{

}

// Edit account info
private void account::edit_account()
{

}

// Display account info
private void account::display_account() 
{

}

// Deposit to account
private void account::deposit_account()
{

}

// Withdrawl from account
private void account::withdrawl_account()   
{

}

// Display History
private void account::dislaylog_account()
{

}

// Record History
private void account::recordlog_account()
{

}

/// Seclection Page Actions ///

// Selection function for Login Page
int loginMenu(char username, char password)
{

}
// Selection function for User Page
int userMenu()
{

}

// Selection function for Single Account Page
int accountMenu() 
{

}


/// User Actions ///

// Create user account
private void User::Create()
{

}
// Delete user account
private void User::Delete()
{

}
// Edit user account
private void User::Edit()
{

}
// Attempt Login to account
int User::Login()
{

}

// Logoff user account
int User::Logoff()
{

}

//// Main ////
int main() 
{
	// Login Page
	if (loginMenu() == 1) 
	{
		//Login
		if (login(username, password) == 1) 
		{
			// Bulk account option
			// Single Account Options
				// Create
				// Delete
				// Edit
				// Display
				// Deposit
				// Withdrawl
				// Display Transaction Log
				// Go Back
			// Logoff
			// Edit User
			// Delete User 
		}
		else 
		{
			// Try Again
		}
	}
	else if (loginMenu() == 2) 
	{
		// Create User


	}
}