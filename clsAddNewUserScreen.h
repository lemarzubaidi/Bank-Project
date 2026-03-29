#pragma once
#include<iostream>
#include "clsUser.h"
#include "ClsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsAddNewUserScreen:protected ClsScreen
{
private:

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Premission: ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}
	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Answer = 'n';
		cout << "\nDo you want to give full access?y/n ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to : \n ";
		cout << "\nShow Client List? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pListClient;
		}
		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}
		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}
		cout << "\nFind Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}
		cout << "\nTransactions? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}
		return Permissions;
	}



public:
	static void ShowAddNewUserScreen()
	{
		
		_DrawScreenHeader("\t  Add New User Screen");
		
		string UserName;
		cout << "\nPlease enter UserName: ";
		UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName Is Already Used, Choose anthor one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
		_ReadUserInfo(NewUser);
		clsUser::enSaveResult SaveResult;
		SaveResult = NewUser.Save();
		switch (SaveResult)
		{
		case clsUser::enSaveResult::svSucceeded:
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		case clsUser::enSaveResult::svFaildEmptyObject:
			cout << "\nError User was not saved because its Empty";
			break;
		case clsUser::enSaveResult::svFaildUserExists:
			cout << "\nError User was not saved because UserName is used!\n";
			break;
		}





	}
};

