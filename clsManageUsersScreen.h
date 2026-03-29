#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include"clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include <iomanip>

using namespace std;
class clsManageUsersScreen:protected ClsScreen
{
private:
	enum enManageUsersMenueOptions {
		eListUser=1,eAddNewUser=2,eDeleteUser=3,eUpdateUser=4,
		eFindUser=5,eMainMeune=6
	 };
	static short _ReadManageUsersMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}
	static void _GoBackToManageUserMenue()
	{
		cout << "\n\nPress any key to go back to Manage Users Menue...";
		system("pause>0");
		ShowManageUsersMenue();
	}
	static void _ShowListUsersScreen()
	{
		clsUsersListScreen::_ShowUserList();

	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();

	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowAddNewUserScreen();

	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserscreen();
	}
	static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
	{
		switch (ManageUsersMenueOption)
		{
		case enManageUsersMenueOptions::eListUser:{
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUserMenue();
			break;
		}
		case enManageUsersMenueOptions::eAddNewUser:{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUserMenue();
			break;
		}
		case enManageUsersMenueOptions::eDeleteUser:{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUserMenue();
			break;
		}
		case enManageUsersMenueOptions::eUpdateUser:{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUserMenue();
			break;
		}
		case enManageUsersMenueOptions::eFindUser:{
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUserMenue();
			break;
		}
		case enManageUsersMenueOptions::eMainMeune:{
		
		}
		}

	}
public:

	static void ShowManageUsersMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;// this will exit the function and it will not continue
		}

		system("cls");
		
		_DrawScreenHeader("\t  Manage Usersss Screen");
		
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PerformManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersMenueOption());
	}

};

