#pragma once
#include<iostream>
#include "ClsScreen.h"
#include "ClsBankClient.h"
#include"clsInputValidate.h"
using namespace std;
class clsTranferScreen:protected ClsScreen
{
private:
	static void _PrintClient(ClsBankClient Clinet)
	{
		cout << "\nClient Card:";
		cout << "\n____________________";
		cout << "\nFull Name   :" << Clinet.FullName();
		cout << "\nAcc. Number :" << Clinet.AccountNumber();
		cout << "\nBalance     :" << Clinet.AccountBalance;
		cout << "\n____________________";
	}
	static string _ReadAccountNumber()
	{
		string AccountNumber;
		cout << "\nPlease Enter Account Number to Transfer From: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!ClsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}
	static float ReadAmount(ClsBankClient SourceClient)
	{
		float Amount;

		cout << "\nEnter Transfer Amount? ";

		Amount = clsInputValidate::ReadFloatNumber();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t\t\tTransfer Screen");
		ClsBankClient SourceClient = ClsBankClient::Find(_ReadAccountNumber());
		_PrintClient(SourceClient);
		ClsBankClient DestinationClient = ClsBankClient::Find(_ReadAccountNumber());
		_PrintClient(DestinationClient);

		float Amount = ReadAmount(SourceClient);
		cout << "\nAre you Sure you want to perform this operation? y/n? ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			if (SourceClient.Transfer( DestinationClient, Amount,CurrentUser.UserName))
			{
				cout << "\nTransfer Done Successfully\n";
			}
			else
			{
				cout << "\nTransfer Faild";
			}
		}

		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);

		
	}
};

