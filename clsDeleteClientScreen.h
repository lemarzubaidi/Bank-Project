#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsScreen.h"
using namespace std;

class clsDeleteClientScreen:protected ClsScreen
{
private:
	static void _printClient(ClsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n_____________________";
		cout << "\nFirstName    :" << Client.FirstName;
		cout << "\nLastName     :" << Client.LastName;
		cout << "\nFullName     :" << Client.FullName();
		cout << "\nEmail        :" << Client.Email;
		cout << "\nPhone        :" << Client.Phone;
		cout << "\nAcc. Number  :" << Client.AccountNumber();
		cout << "\nPassword     :" << Client.PinCode;
		cout << "\nBalance      :" << Client.AccountBalance;
		cout << "\n_______________________\n";

	}

public:
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}
		
		_DrawScreenHeader("\tDelete Client Screen");
	
		string AccountNumber = "";
		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!ClsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		ClsBankClient Client1 = ClsBankClient::Find(AccountNumber);
		_printClient(Client1);

		cout << "\nAre You Sure you want to delete this client y/n?";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client1.Delete())
			{
				cout << "\nClient Deleted Successfully :)\n";
				_printClient(Client1);
			}

			else
			{
				cout << "\nError Client Was not Deleted\n ";
			}
		}



	}
};

