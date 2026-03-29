#pragma once
#include <iostream>
#include "ClsScreen.h"
using namespace std;
class clsDeleteUserScreen:protected ClsScreen
{
private:
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

public:
	static void ShowAddNewUserScreen()
	{
		
		_DrawScreenHeader("\t Delete User Sceen");
		
		string UserName;
		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();

		}
		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);
		char Answer = 'n';
		cout << "\nAre you sure you want to delete this User y/n?";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			if (User1.Delete())
			{
				cout << "\nUser Deleted Successfully :-)";
				_PrintUser(User1);
			}
			else
			{
				cout << "\nError User Was not Deleted\n";
			}
		}
	}
};

