#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "Global.h"
#include "clsUser.h"
#include "ClsMainScreen.h"
#include <fstream>
using namespace std;
class clsLoginScreen:protected ClsScreen
{
private:
	static bool _Login()
	{
		string UserName, Password;
		bool LoginFaild = false;
		int FaildLoginCount = 0;
		do 
		{
			if (LoginFaild)
			{
				FaildLoginCount++;
				cout << "\nInvlaid UserName/Password!\n\n";
				cout << "\nYouhave " << (3 - FaildLoginCount) << " Trial(s) to login.\n\n";
			}
			if (FaildLoginCount == 3)
			{
				cout << "\nYour are Locked after 3 faild trails \n\n";
				return false;
			}
			cout << "Enter UserName? ";
			cin >> UserName;

			cout << "\nEnter Password? ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild=CurrentUser.IsEmpty();
	
		} while (LoginFaild);
		CurrentUser.RegisterLogin();
		ClsMainScreen::ShowMainMenue();
		return true;

	}
public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}
};

