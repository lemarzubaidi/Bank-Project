# Banking System (C++)

A full-featured banking system built in C++ with clean architecture and real-world functionality.

## 🏦 Features

- 🔐 **Login System** — Secure authentication with account lockout after failed attempts
- 👥 **Client Management** — Add, update, delete, and find clients
- 👤 **User Management** — Role-based access control with permissions per user
- 💰 **Transactions** — Deposit, withdrawal, and transfer operations
- 📋 **Transaction History** — Full transaction log per client
- 💼 **Total Balance** — View total balance across all accounts
- 📁 **File Storage** — All data saved and loaded from files (Clients.txt, Users.txt, LoginRegister.txt)
- 🎭 **Separated UI** — Each screen is a separate class, fully separated from business logic

## 🏗️ Architecture

| Layer | Files |
|-------|-------|
| **Screens** | clsLoginScreen, ClsMainScreen, clsAddNewClientScreen, clsDepositScreen, ClsWidthDrawScreen, clsTransactionsScreen, clsTotalBalanceScreen, and more |
| **Business Logic** | ClsBankClient, clsUser, ClsPerson |
| **Utilities** | ClsString, ClsDate, ClsUtil, ClsPeriod, clsInputValidate |
| **Global Config** | Global.h |

## 🛠️ Language
![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=c%2B%2B&logoColor=white)
