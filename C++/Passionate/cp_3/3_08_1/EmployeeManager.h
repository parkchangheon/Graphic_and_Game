#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class RISK_LEVEL
{
	RISK_A = 10,
	RISK_B = 20,
	RISK_C = 30

};



class ForeignSalesWorker
{
public:
	ForeignSalesWorker(string InEmployeename, int InSalary, float InIncentivePer, RISK_LEVEL InRisk_level);
	void AddSalesResult(double InSalesPerformance);
	void ShowInfo();

protected:
	string Employeename;
	int Salary;
	float IncentivePer;
	float RiskPer;

	int TempSalary;
	int RiskPay;
	int TotalSalary;
};


class EmplyeeHandler
{

public:
	void AddEmployee(ForeignSalesWorker* InFSWorker);
	void ShowSalaryinfo();

protected:
	vector<ForeignSalesWorker*> FSWorkers;
};