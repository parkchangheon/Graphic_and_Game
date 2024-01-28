#include "EmployeeManager.h"

int main()
{
	EmplyeeHandler handler;

	ForeignSalesWorker* fseller1 = new ForeignSalesWorker("Hong", 1000, 0.1, RISK_LEVEL::RISK_A);
	fseller1->AddSalesResult(7000);
	handler.AddEmployee(fseller1);

	handler.ShowSalaryinfo();
	return 0;
}