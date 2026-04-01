#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "ClsWidthDrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTranferScreen.h"
#include <iomanip>
using namespace std;
class clsTransactionsScreen:protected ClsScreen
{
private:
	enum enTransactionsMenueOptions {
		eDeposit=1,eWithdraw=2,eShowTotalBalance=3,eShowMainMenue=4,eShowTransfer=5
	};
	static void _showDepositScreen() {
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen()
	{
		ClsWidthDrawScreen::ShowWidthDrawScreen();
	}
	static void _ShowTotalBalanceScreen()
	{
		clsTotalBalanceScreen::ShowTotalBalance();

	}
	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Transactions Menue...";
		system("pause>0");
		ShowTransactionsMenue();

	}
	static void _ShowTransferScreen()
	{
		clsTranferScreen::ShowTransferScreen();
	}
	static short ReadTransactionsMenueOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 4]?";
		short choic=clsInputValidate::ReadShortNumberBetween(1, 4, "Enter NUmber Betwwen 1 and 4");
		return choic;
	}
	static void _performTransctionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
	{
		switch (TransactionMenueOption)
		{
		case enTransactionsMenueOptions::eDeposit: {
			system("cls");
			_showDepositScreen();
			_GoBackToTransactionsMenue();
				break;
		}
		case enTransactionsMenueOptions::eWithdraw: {
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case enTransactionsMenueOptions::eShowTotalBalance: {
			system("cls");
			_ShowTotalBalanceScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case enTransactionsMenueOptions::eShowMainMenue:
		{


		}
		case enTransactionsMenueOptions::eShowTransfer: {
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		
		}
	}

public:
	static void ShowTransactionsMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
		{
			return;// this will exit the function and it will not continue
		}

		system("cls");
		
		_DrawScreenHeader("\t   Transaction Screen");
		
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_performTransctionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
	}

};
