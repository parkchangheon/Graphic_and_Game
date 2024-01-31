#include "OOP_SIX_STEP.h"
#define _CRT_SECURE_NO_WARNINGS

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

void Account::Deposit(double money)
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


void NormalAccount::Deposit(double money)
{
	Account::Deposit(money);	// 원금 추가
	Account::Deposit(money * (interRate / 100.0));	//이자 추가.
}

void HighCreditAccount::Deposit(double money)
{
	NormalAccount::Deposit(money);
	Account::Deposit(money * (specialRate / 100.0));
}

AccountHandler::AccountHandler() :accNum(0)
{
}

AccountHandler::~AccountHandler()
{
	for (int i = 0; i < accNum; i++)
		delete accArr[i];
}

void AccountHandler::ShowMenu(void) const
{
	cout << "----menu----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입    금" << endl;
	cout << "3. 출    금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void AccountHandler::MakeAccount(void)
{
	int sel;
	cout << "[계좌종류선택]" << endl;
	cout << "1. 보통예금계좌 " << endl;
	cout << "2. 신용신뢰계좌" << endl;
	cout << "선택:";
	cin >> sel;

	if (sel == NORMAL)
		MakeNormalAccount();
	else
		MakeCreditAccount();
}

void AccountHandler::MakeNormalAccount(void)
{
	int id;
	char name[NAME_LEN];
	int balance;
	int interRate;

	cout << "[보통예금계좌 개설]" << endl;
	cout << "계좌ID : "; cin >> id;
	cout << "이  름 : "; cin >> name;
	cout << "입금액 : "; cin >> balance;
	cout << "이자율 : "; cin >> interRate;
	cout << endl;

	accArr[accNum++] = new NormalAccount(id, balance, name, interRate);
}

void AccountHandler::MakeCreditAccount(void)
{
	int id;
	char name[NAME_LEN];
	int balance;
	int interRate;
	int creditlevel;

	cout << "[신용예금계좌 개설]" << endl;
	cout << "계좌ID : "; cin >> id;
	cout << "이  름 : "; cin >> name;
	cout << "입금액 : "; cin >> balance;
	cout << "이자율 : "; cin >> interRate;
	cout << "신용등급(1toA, 2toB, 3toC): "; cin >> creditlevel;

	cout << endl;

	switch (creditlevel)
	{
	case 1:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_A);
		break;
	case 2:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_B);
		break;
	case 3:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_C);
		break;

	}
}

void AccountHandler::DepositMoney(void)
{
	int money;
	int id;
	cout << "입금" << endl;
	cout << "계좌ID"; cin >> id;
	cout << "입금액"; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			accArr[i]->Deposit(money);
			cout << "입금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다" << endl << endl;
}

void AccountHandler::WithdrawMoney(void)
{
	int money;
	int id;
	cout << "출금" << endl;
	cout << "계좌ID : "; cin >> id;
	cout << "출금액 : "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			if (accArr[i]->Withdraw(money) == 0)
			{
				cout << "잔액부족" << endl << endl;
				return;
			}

			cout << "출금완료" << endl << endl;
			return;	
		}
	}
	cout << "유효하지 않은 ID 입니다" << endl << endl;
}

void AccountHandler::ShowAllAccInfo(void) const
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
		cout << endl;
	}
}

int main()
{
	AccountHandler manager;
	int choice;

	while (1)
	{
		manager.ShowMenu();
		cout << "선택 :";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case MAKE:
			manager.MakeAccount();
			break;

		case DEPOSIT:
			manager.DepositMoney();
			break;

		case WITHDRAW:
			manager.WithdrawMoney();
			break;

		case INQUIRE:
			manager.ShowAllAccInfo();
			break;

		case EXIT :
			return 0;

		default :
			cout << " Illegal selection" << endl;
		}
	}
	return 0;
}