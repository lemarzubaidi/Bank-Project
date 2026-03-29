#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

using namespace std;
class ClsWidthDrawScreen :protected ClsScreen
{
private:
	static void _PrintClient(ClsBankClient Client)
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

	static string _ReadAccountNumber()
	{
		string AccountNumber;
		cout << "\nPlease enter AccountNumber? ";
		cin >> AccountNumber;
		return AccountNumber;
	}
public:
	static void ShowWidthDrawScreen()
	{
		system("cls");
		
		_DrawScreenHeader("\t   Widthdraw Screen");
		
		string AccountNumber=_ReadAccountNumber();
		while (!ClsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with ["<<AccountNumber<<"] does not exist.\n";
			 AccountNumber=_ReadAccountNumber();
		}
			ClsBankClient Client1 = ClsBankClient::Find(AccountNumber);
			_PrintClient(Client1);
			double Amount = 0;
			cout << "\nPlease enter Withdraw amount?";
			Amount = clsInputValidate::ReadDblNumber();
			cout << "\nAre you sure you want to perform this transaction?";
			char Answer = 'n';
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y')
			{
				if (Client1.WidthDraw(Amount))
				{
					cout << "\nAmount Withdrew Successfully.\n";
					cout << "\nNew Balance is: " << Client1.AccountBalance;
				}
				else
				{
					cout << "\nCannot withdraw, Insuffecient Balance!\n";
					cout << "\nAmount to withdraw is: " << Amount;
					cout << "\nYour Balance is:" << Client1.AccountBalance;
				}	
			}
			else
			{
				cout << "\nOpraion was cancelled.\n";
			}



	}
};