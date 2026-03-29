#include <iostream>
#include"clsInputValidate.h"
#include"ClsBankClient.h"
#include<iomanip>
#include"ClsUtil.h"
#include "ClsMainScreen.h"
#include "clsLoginScreen.h"

using namespace std;
void ReadClientInfo(ClsBankClient& Client) 
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
    Client.PinCode= clsInputValidate::ReadString();

    cout << "\nEnter Account Balance: ";
    Client.AccountBalance= clsInputValidate::ReadFloatNumber();
}

void UpdateClient()
{
    string AccountNumber = "";
    cout << "\nPlease Enter Client Account Number: ";

    AccountNumber = clsInputValidate::ReadString();
    while (!ClsBankClient::IsClientExist(AccountNumber)) {
        cout << "\nAccount number is not found, choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }
    ClsBankClient Client1 = ClsBankClient::Find(AccountNumber);
    Client1.print();
    cout << "\n\nUpdate Client Info:";
    cout << "\n_____________________\n";
    ReadClientInfo(Client1);
    ClsBankClient::enSaveResult SaveResult;
    SaveResult = Client1.Save();
    switch (SaveResult) {
    case ClsBankClient::enSaveResult::svSucceeded:
        {
        cout << "\nAccount Updated Successfully :)\n";
        Client1.print();
        break;
        }
    case ClsBankClient::enSaveResult::svFaildEmptyObject:
    {
        cout << "\nEerror account was not saved because its Empty";
        break;
    }
    }

}

void AddNewClient()
{
    string AccountNumber = " ";
    cout << "\nPlease Enter Account Number: ";
    AccountNumber = clsInputValidate::ReadString();
    while (ClsBankClient::IsClientExist(AccountNumber)) {
        cout << "\nAccount Number Is Already Used,Choose anther one: ";
        AccountNumber = clsInputValidate::ReadString();
    }
    ClsBankClient NewClient = ClsBankClient::GetAddNewClientObject(AccountNumber);
    ReadClientInfo(NewClient);
     
    ClsBankClient::enSaveResult SaveResult;
    SaveResult = NewClient.Save();

    switch (SaveResult)
    {
    case ClsBankClient::enSaveResult::svSucceeded:
    {
        cout << "\nAccount Addeded Successfully :)\n";
        NewClient.print();
        break;
    }
    case ClsBankClient::enSaveResult::svFaildEmptyObject:
    {
        cout << "\nError account was not saved because its Empty";
        break;
    }
    case ClsBankClient::enSaveResult::svFaildAccountNumberExists:
    {
        cout << "\n Error account was not saved because its exisits";
        break;
    }
    }


}

void DeleteClient()
{
    string AccountNumber = " ";
    cout << "\nPlease Enter Client Account Number: ";

    AccountNumber = clsInputValidate::ReadString();
    while (!ClsBankClient::IsClientExist(AccountNumber)) {
        cout << "\nAccount number is not found, choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }
    ClsBankClient DClient = ClsBankClient::Find(AccountNumber);
    cout << "Are U sure U want to delete it? (y/n)" << endl;
    char Answer = 'n';
    cin >>Answer;
    if (Answer == 'y' || Answer == 'Y') {

        if (DClient.Delete()) {
            cout << "\nClient Deleted Successfully :-)\n";
            DClient.print();
        }
    }
    else {
        cout << "\nError Client Was Not Deleted\n";
    }

}

void PrintClientRecordLine(ClsBankClient Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber();
    cout << "| " << setw(20) << left << Client.FullName();
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(20) << left << Client.Email;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowClientsList()
{
    vector<ClsBankClient> VClient = ClsBankClient::GetClientsList();
    cout << "\n\t\t\t\t\tClient List (" << VClient.size() << ") Client(s).";
    cout << "\n_________________________________________________________";
    cout << "____________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(20) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(20) << "Email";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n__________________________________________________________";
    cout << "____________________________________________\n" << endl;
    if (VClient.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Avilable In The System!";
    }
    else
    {
        for (ClsBankClient Client : VClient)
        {
            PrintClientRecordLine(Client);
            cout << endl;
            
        }
        cout << "\n_________________________________________________________";
        cout << "____________________________________________\n" << endl;
    }

}

void PrintClientRecordBalanceLine(ClsBankClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber();
    cout << "| " << setw(40) << left << Client.FullName();
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowTotalBalances()
{

    vector<ClsBankClient> vClients = ClsBankClient::GetClientsList();
    cout << "\n\t\t\t\t\tBalance List (" << vClients.size() << ") Clients(s).";
    cout << "\n____________________________________________________________";
    cout << "_____________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n____________________________________________________________";
    cout << "_____________________________________________\n" << endl;

    double TotalBalance = ClsBankClient::GetTotalBalances();

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for (ClsBankClient c : vClients)
        {
            PrintClientRecordBalanceLine(c);
            cout << endl;
        }
    }
    cout << "\n____________________________________________________________";
    cout << "_____________________________________________\n" << endl;
    cout << "\t\t\t\t\t    Total Balences= " << TotalBalance << endl;
    cout << "\t\t\t\t\t       ( " << clsUtil::NumberToText(TotalBalance) << ")";


}

int main()
{
    while (true) {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
       
    }
   

}