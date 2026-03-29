#pragma once
#include <iostream>
#include "clsTransactionsScreen.h"
#include "ClsScreen.h"
#include "ClsBankClient.h"
#include "clsInputValidate.h"
using namespace std;
class clsDepositScreen:protected ClsScreen
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
		string AccountNumber = "";
		cout << "\nPlease enter AccountNumber?";
		cin >> AccountNumber;
		return AccountNumber;
		
	}
public:
	static void ShowDepositScreen()
	{
		system("cls");
		
		_DrawScreenHeader("\t  Deposit Screen");
		
		string AccountNumber = _ReadAccountNumber();
		while (!ClsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}
		ClsBankClient Client1 = ClsBankClient::Find(AccountNumber);
		_PrintClient(Client1);
		double Amount=0;
		cout << "\nPlease enter deposit amount?";
		Amount=clsInputValidate::ReadDblNumber();
		cout << "\nAre you sure want to perform this transaction?";
		char Answer = 'n';
		cin >> Answer;
		float total=0;
		if (Answer == 'Y' || Answer == 'y')
		{
			Client1.Deposit(Amount);
			cout << "Amount Deposited Successfully.";
			cout << "\nNew Balance Is: " << Client1.AccountBalance;
		}
		else
		{
			cout << "\nOpration was cancelled.\n";
		}
	}
};

