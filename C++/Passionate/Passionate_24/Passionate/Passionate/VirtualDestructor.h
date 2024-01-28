#include <iostream>

using namespace std;

class VDFirst
{
private:
	char* strOne;

public:
	VDFirst(const char* str);
	virtual ~VDFirst();
};

class VDSecond : public VDFirst
{
private:
	char* strTwo;

public:
	VDSecond(const char* str1, const char* str2);
	virtual ~VDSecond();

};