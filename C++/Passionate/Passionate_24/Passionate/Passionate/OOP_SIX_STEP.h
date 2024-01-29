#include<iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

// 선택메뉴
enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

// 신용등급
enum { LEVEL_A = 7, LEVEL_B = 4, LEVEL_C = 2 };
enum { NORMAL = 1, CREDIT = 2 };	//계좌의 종류

class Account
{
private:
	int accID;
	int balance;
	char* cusName;

public:
	Account(int ID, int money, char* name);
	Account(const Account& ref);

	int GetAccID() const;
	virtual void Deposit(int money);
	int Withdraw(int money);
	void ShowAccInfo() const;
	~Account();
};


class NormalAccount : public Account
{
private: 
		int interRate;	//이자 %단위

public:
	NormalAccount(int ID, int money, char* name, int rate) : Account(ID, money, name), interRate(rate) {};
	virtual void Deposit(int money) override;
};


class HighCreditAccount : public NormalAccount
{
private:
	int specialRate;
public:
	HighCreditAccount(int ID, int money, char* name, int rate, int special) :NormalAccount(ID, money, name, rate), specialRate(special) {}
	virtual void Deposit(int money)override;
};


class AccountHandler
{
private:
	Account* accArr[100];
	int accNum;

public:
	AccountHandler();
	void ShowMenu(void) const;
	void MakeAccount(void);
	void DepositMoney(void);
	void WithdrawMoney(void);
	void ShowAllAccInfo(void) const;
	~AccountHandler();

protected:
	void MakeNormalAccount(void);
	void MakeCreditAccount(void);
};