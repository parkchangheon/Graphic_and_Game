#include "EmployeeManager.h"



void EmplyeeHandler::AddEmployee(ForeignSalesWorker* InFSWorker)
{
	FSWorkers.push_back(InFSWorker);
}
void EmplyeeHandler::ShowSalaryinfo()
{
	for (auto* FSWorker : FSWorkers)
	{
		FSWorker->ShowInfo();
	}
}



ForeignSalesWorker::ForeignSalesWorker(string InEmployeename, int InSalary, float InIncentivePer, RISK_LEVEL InRisk_level)
{
	Employeename = InEmployeename;
	Salary = InSalary;
	IncentivePer = InIncentivePer;

	switch (InRisk_level)
	{
	case RISK_LEVEL::RISK_A :
		RiskPer =  0.3;
		break;

	case RISK_LEVEL::RISK_B : 
		RiskPer =  0.2;
		break;

	case RISK_LEVEL::RISK_C :
		RiskPer =  0.1;
		break;
	}


}

void ForeignSalesWorker::AddSalesResult(double InSalesPerformance)
{
	TotalSalary = 0;
	RiskPay = 0;
	TempSalary = 0;

	TempSalary = Salary + (InSalesPerformance * IncentivePer);
	RiskPay = TempSalary * RiskPer;
	TotalSalary = TempSalary + RiskPay;
}

void ForeignSalesWorker::ShowInfo()
{
	cout << "name : " << Employeename << endl;
	cout << "salary : " << TempSalary << endl;
	cout << "risk pay : " << RiskPay << endl;
	cout << "sum : " << TotalSalary << endl;
}
