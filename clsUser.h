#pragma once
#include "ClsPerson.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "ClsString.h"
#include "ClsDate.h"
#include "ClsString.h"
using namespace std;
class clsUser:public ClsPerson
{
private:
	enum enMode{EmptyMode=0,UpdateMode=1,AddNewMode=2};
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Premissions;

	bool _MarkedForDelete = false;
	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line,string Seperator="#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;
		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = LoginRegisterDataLine[2];
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);
		return LoginRegisterRecord;

	}
	string _PrepareLogInRecord(string Seperator ="#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString()+Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += Password + Seperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}
	static clsUser _ConvertLinetoUserObject(string line, string Seperator = "#//#")
	{
		vector<string>vUserData;
		vUserData = clsString::Split(line, Seperator);
		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));
	}
	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.UserName + Seperator;
		UserRecord += User.Password + Seperator;
		UserRecord += to_string(User.Permissions);
		return UserRecord;
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector<clsUser> vUsers;
		fstream MyFile;
		MyFile.open("Users.txt",ios::in);

		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsUser User = _ConvertLinetoUserObject(line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}
	static void _SaveUsersDataToFile(vector<clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		string DataLine;
		if (MyFile.is_open())
		{
			for (clsUser U : vUsers)
			{
				if (U.MarkedForDelete() == false)
				{
					DataLine = _ConvertUserObjectToLine(U);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}

	}
	
	 void _Update()
	{
		 vector<clsUser>_vUsers;
		 _vUsers = _LoadUsersDataFromFile();
		 for (clsUser& U : _vUsers)
		 {
			 if (U.UserName == UserName)
			 {
				 U = *this;
				 break;
			 }
		 }
		 _SaveUsersDataToFile(_vUsers);
	}

	 void _AddNew()
	 {

		 _AddDataLineToFile(_ConvertUserObjectToLine(*this));
	 }
	 void _AddDataLineToFile(string stDataLine)
	 {
		 fstream Myfile;
		 Myfile.open("Users.txt",ios::out|ios::app);
		 if (Myfile.is_open())
		 {
			 Myfile << stDataLine << endl;
			 Myfile.close();
		 }
	 }
public:
	enum enPermissions {
		eAll=-1,pListClient=1,pAddNewClient=2,pDeleteClient=4,
		pUpdateClient=8,pFindClient=16,pTranactions=32,pManageUsers=64,pLoginRegister=128
	};

	struct stLoginRegisterRecord
	{
		string UserName;
		string DateTime;
		string Password;
		int Permissions;
	};
	clsUser(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string UserName, string Password,
		int Premissions) :ClsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Premissions = Premissions;
	}
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	string GetUserName()
	{
		return _UserName;
	}
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;
	void SetPermissions(int Permissions)
	{
		_Premissions = Permissions;
	}

	int GetPermissions()
	{
		return _Premissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt",ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile,line))
			{
				clsUser user = _ConvertLinetoUserObject(line);
				if (user.UserName == UserName)
				{
					MyFile.close();
					return user;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();

	}
	static clsUser Find(string UserName, string Password)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();

		}
		return _GetEmptyUserObject();
	}

	enum enSaveResult{svFaildEmptyObject=0,svSucceeded=1,svFaildUserExists=2};

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResult::svFaildEmptyObject;
			}
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResult::svSucceeded;
			break;
		}
		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResult::svFaildUserExists;
			}
			else
			{
				_AddNew();
				_Mode=enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}
			break;
		}

		}
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}
	bool Delete()
	{
		vector<clsUser>_vUsers;
		_vUsers = _LoadUsersDataFromFile();
		for (clsUser& U : _vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkedForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}
	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "",UserName, "", 0);
	}

	static vector<clsUser> GetUserList()
	{
		return _LoadUsersDataFromFile();
	}


	 bool CheckAccessPremission(enPermissions Permissions)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;
		if ((this->Permissions & Permissions) == Permissions)
			return true;
		else
			return false;
	}

	 void RegisterLogin()
	 {
		 string stDataLine = _PrepareLogInRecord();
		 fstream MyFile;
		 MyFile.open("LoginRegister.txt", ios::out | ios::app);
		if (MyFile.is_open())
		 {
			 MyFile << stDataLine << endl;
			 MyFile.close();
		 }

	 }

	 static vector<stLoginRegisterRecord> GetLoginRegisterList()
	 {
		 vector <stLoginRegisterRecord> vLoginRegisterRecord;
		 fstream MyFile;
		 MyFile.open("LoginRegister.txt", ios::in);
		 if (MyFile.is_open())
		 {
			 string Line;
			 stLoginRegisterRecord LoginRegisterRecord;
			 while (getline(MyFile, Line))
			 {
				 LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				 vLoginRegisterRecord.push_back(LoginRegisterRecord);

			 }
			 MyFile.close();

		 }
		 return vLoginRegisterRecord;
	 }
};
