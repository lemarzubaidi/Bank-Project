#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsUpdateClientScreen:protected ClsScreen
{
private:

    static void _PrintClient(ClsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

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

public:

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient))
        {
            return;// this will exit the function and it will not continue
        }
        
        _DrawScreenHeader("\tUpdate Client Screen");
       
        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!ClsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        ClsBankClient Client1 = ClsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\nAre you sure you want to update this client y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";
            _ReadClientInfo(Client1);

            ClsBankClient::enSaveResult SaveResult;
            SaveResult = Client1.Save();
            switch (SaveResult)
            {
            case ClsBankClient::enSaveResult::svSucceeded:
                {
                    cout << "\nAccount Updated Successfully :-)\n";

                    _PrintClient(Client1);
                    break;
                }
            case ClsBankClient::enSaveResult::svFaildEmptyObject:
                {
                    cout << "\nError account was not saved because it's Empty";
                    break;

                }

            }

        }




	 }
};

