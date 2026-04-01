#pragma once
#include<iostream>
#include<string>
#include"ClsPerson.h"
#include "ClsString.h"
#include <vector>
#include<fstream>

using namespace std;
class ClsBankClient :public ClsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNew = 2 };

	enMode _Mode;

	string _AccountNumber;

	string _PinCode;

	float _AccountBalance;

	bool _MarkedForDelete = false;

	static ClsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);
		return ClsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1],
			vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static ClsBankClient _GetEmptyClientObject()
	{
		return ClsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<ClsBankClient> _LoadClientsDataFromFile() {
		vector<ClsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				ClsBankClient Client = _ConvertLinetoClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	static string _ConvertClientObjectToLine(ClsBankClient  Client, string Sep = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Sep;
		stClientRecord += Client.LastName + Sep;
		stClientRecord += Client.Email + Sep;
		stClientRecord += Client.Phone + Sep;
		stClientRecord += Client.AccountNumber() + Sep;
		stClientRecord += Client.PinCode + Sep;
		stClientRecord += to_string(Client.AccountBalance);
		return stClientRecord;
	}

	static void _SaveClientsDataToFile(vector<ClsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		string DataLine;
		if (MyFile.is_open()) {

			for (ClsBankClient C : vClients)
			{
				if (C._MarkedForDelete == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update() {
		vector<ClsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();
		for (ClsBankClient& C : _vClients) {
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			cout << "\nFile Opened Successfully!";
			MyFile << stDataLine << endl;
			MyFile.close();
		}
		else
			cout << "\nFailed To Open File!";
	}

public:

	ClsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance) :
		ClsPerson(FirstName, LastName, Email, Phone)
	{

		_Mode = Mode;
		_AccountBalance = AccountBalance;
		_PinCode = PinCode;
		_AccountNumber = AccountNumber;

	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	void print()
	{
		cout << "\nClient Card:";
		cout << "\n_____________________";
		cout << "\nFirstName    :" << FirstName;
		cout << "\nLastName     :" << LastName;
		cout << "\nFullName     :" << FullName();
		cout << "\nEmail        :" << Email;
		cout << "\nPhone        :" << Phone;
		cout << "\nAcc. Number  :" << _AccountNumber;
		cout << "\nPassword     :" << _PinCode;
		cout << "\nBalance      :" << _AccountBalance;
		cout << "\n_______________________\n";

	}

	static ClsBankClient Find(string AccountNumber)
	{
		vector<ClsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				ClsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return ClsBankClient::_GetEmptyClientObject();

	}

	static ClsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<ClsBankClient>vClient;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				ClsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				vClient.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		ClsBankClient Client1 = ClsBankClient::Find(AccountNumber);
		return(!Client1.IsEmpty());
	}


	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResult Save() {
		switch (_Mode)
		{
		case ClsBankClient::EmptyMode:
		{
			if (IsEmpty()) {
				return enSaveResult::svFaildEmptyObject;
			}
		}

		case ClsBankClient::UpdateMode: {
			_Update();
			return enSaveResult::svSucceeded;
			break;
		}

		case ClsBankClient::AddNew:
		{
			if (ClsBankClient::IsClientExist(_AccountNumber))
				return enSaveResult::svFaildAccountNumberExists;
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}
		}
		}
	}

	static ClsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return ClsBankClient(enMode::AddNew, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		vector<ClsBankClient> _VClients;
		_VClients = _LoadClientsDataFromFile();
		for (ClsBankClient& C : _VClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(_VClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector<ClsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector<ClsBankClient> vClients = ClsBankClient::GetClientsList();

		double TotalBalance = 0;
		for (ClsBankClient C : vClients)
		{
			TotalBalance += C.AccountBalance;

		}
		return TotalBalance;

	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}
	bool WidthDraw(double Amount) {
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
		}
	}
	bool Transfer(ClsBankClient& DestinationClient,float Amount)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}
		WidthDraw(Amount);
		DestinationClient.Deposit(Amount);
		return true;
	}

};

