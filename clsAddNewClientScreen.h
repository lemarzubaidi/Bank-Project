#pragma once
#include<iostream>
#include "ClsBankClient.h"
#include "clsInputValidate.h"
#include "ClsScreen.h"
using namespace std;

class clsAddNewClientScreen :protected ClsScreen
{
private:
	static void _ReadClientInfo(ClsBankClient& Client)
	{
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();


	}


static void _printClient(ClsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n_____________________";
		cout << "\nFirstName    :"<<Client.FirstName;
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
	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}
		
		_DrawScreenHeader("\t Add New Client Screen");
		
		string AccountNumber = "";

		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (ClsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Already Used, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		ClsBankClient NewClient = ClsBankClient::GetAddNewClientObject(AccountNumber);
		_ReadClientInfo(NewClient);

		ClsBankClient::enSaveResult SaveResult;

		SaveResult = NewClient.Save();
		switch (SaveResult)
		{
		case ClsBankClient::svFaildEmptyObject:
			cout << "\nErrror account was not saved because its Empty";
			break;
		case ClsBankClient::svSucceeded:
			cout << "\nAccount Addeded Successfully :)\n";
			_printClient(NewClient);
			break;
		case ClsBankClient::svFaildAccountNumberExists:
			cout << "\nError account was not saved because account number is used!\n";
			break;
		}

	}

};

