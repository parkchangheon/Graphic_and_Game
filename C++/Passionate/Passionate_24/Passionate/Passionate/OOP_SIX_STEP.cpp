#include "OOP_SIX_STEP.h"

Account::Account(int ID, int money, char* name) : accID(ID), balance(money)
{
	cusName = new char[strlen(name) + 1];
	strcpy(cusName, name);
}

Account::Account(const Account& ref) :accID(ref.accID), balance(ref.balance)
{
	cusName = new char[strlen(ref.cusName) + 1];
	strcpy(cusName, ref.cusName);
}

int Account::GetAccID() const
{
	return accID;
}

void Account::Deposit(int money)
{
	balance += money;
}

int Account::Withdraw(int money)
{
	if (balance < money)
		return 0;

	balance -= money;
	return money;
}

void Account::ShowAccInfo() const
{
	cout << "계좌ID : " << accID << endl;
	cout << "이  름 : " << cusName << endl;
	cout << "잔  액 : " << balance << endl;
}

Account::~Account()
{
	delete []cusName;
}


void NormalAccount::Deposit(int money)
{
	Account::Deposit(money);	// 원금 추가
	Account::Deposit(money * (interRate / 100.0));	//이자 추가.
}

void HighCreditAccount::Deposit(int money)
{
	NormalAccount::Deposit(money);
	Account::Deposit(money * (specialRate / 100.0));
}


