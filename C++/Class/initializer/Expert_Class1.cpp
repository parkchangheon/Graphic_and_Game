#include "Expert_Class1.h"

using namespace std;

int main()
{

}

spreadsheetCell::spreadsheetCell()
{
	m_value = 0;
}

spreadsheetCell::spreadsheetCell(double initialValue) : m_value{initialValue}
{

}

spreadsheetCell::spreadsheetCell(const spreadsheetCell& src)
{


}

void spreadsheetCell::setValue(double value)
{
	m_value = value;
}

double spreadsheetCell::getValue() const
{
	return m_value;
}

void spreadsheetCell::setString(string_view inString)
{
	m_value = StringToDouble(inString);
}

string spreadsheetCell::getString() const
{
	return doubleToString(m_value);
}

double spreadsheetCell::StringToDouble(string_view InString) const
{
	double number = 0;

	return number;
}

string spreadsheetCell::doubleToString(double value) const
{
	return to_string(m_value);
}


// ************ Foo && MyClass Class ************

Foo::Foo(double value) : m_value{value}
{
	cout << "Foo : m_value : " << m_value << endl;
}

MyClass::MyClass(double value) : m_value(value), m_foo{ m_value }
{
	cout << "MyClass::m_value = " << m_value << endl;
	// int main() { 1.2 }; 했을때,
	// 	Foo : 1.2
	// 	MyClass 1.2
	// 가 기대가 되나, 이건 생성자 초기자의 순서가 아닌, 클래스의 선언 순서.
	// 만약 순서가 달라진다면, 쓰레기 값이 나올 수 도 있다.

	// 일반적인 경우 값을 할당하는 시점에서 객체가 이미 생성된 값만을 바꿈.
	// 생성자 초기자의 경우, 데이터 멤버를 생성하는 과정에서 초기값을 설정 가능
	// ==> 값을 대입하는 방식보다 더 효율적.

}


