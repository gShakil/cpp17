// stdMove.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

//참조 사이트: https://jungwoong.tistory.com/53
/*

Rvalue, 우측값은 대입 시에 항상 오른쪽에만 오는 식을 말한다.
예제로 이해하는 것이 쉽다.

int doSomething()
{
  ...
  return z;
}

int x = 10;		// x 는 Lvalue, 10은 Rvalue
int y = 20;		// y 는 Lvalue, 20은 Rvalue

x = y; 				// x 와 y 모두 Lvalue
x = (x + y);		// x 는 Lvalue, x + y 는 Rvalue

x + y = 30;		// 잘 못된 코드, Rvalue 인 x + y 에 대입하고 있다.

x = doSomething()		// doSomething() 은 Rvalue
x, y 처럼 이름을 가지고 있고, 그 이름으로 접근할 수 있는 것이 Lvalue 이다.
그와 반대로 (x + y) 나 상수 10, 20 등은 이름을 가지고 있지 않고 식이 끝난 후 다음 라인에서 그 값에 접근할 수 없다.

Rvalue 를 함수의 매개변수로 받고 싶으면 A&& 로 선언한다.
참고로 doSomethingWithRvalue 안에서 rhs 를 다시 사용할 때는 rhs 가 Lvalue 라는 것을 주의하자. Rvalue 로 사용하고 싶으면 다시 std::move(rhs) 와 같이 사용해주어야 한다.

class A;
// class A의 instance를 Rvalue 로 받고 싶을 때
void doSomethingWithRvalue(A&& rhs)
{

}
std::move 를 사용해서 성능을 개선해보자
std::move 는 이름 때문에 부르는 것과 동시에 어떤 이동 작업이 이뤄질 것 같지만, 실제로 Lvalue 를 Rvalue 로 casting 해줄 뿐이다.

*/




#include <iostream>
#include <vector>

using namespace std;

// 암시적으로 생성되는 move constructors의 형태는 아래와 같다.
// 기본적으로 클래스 멤버변수를 std::move해서 Rvalue로 캐스팅하여 초기화 한다.
// struct DUMMY_STRUCT
// {
// 	char szSite[256];
// 	int nInt;
// 	float fFloat;
// 	double dDouble;
// };
// 
// class myClass
// {
// public:
// 	myClass(){}
// 	myClass(myClass&& rhs)
// 		: stDummy(std::move(rhs.stDummy))
// 		//: A(std::move(rhs.A))
// 		//, B(std::move(rhs.B))
// 	{
// 		cout << "Move Construct" << endl;
// 	}
// 
// 	DUMMY_STRUCT stDummy;
// 	//std::string A;
// 	//std::string B;
// };


///////////////////////////std::move를 사용하는 swap의 예
template <class T>
void swap1(T& a, T& b) {
	T tmp(a);   // a의 copy가 2개가 됨.
	a = b;      // b의 copy가 2개가 됨 (+ a의 copy 중 하나가 사라짐)
	b = tmp;    // tmp의 copy가 2개가 됨 (+b의 copy 중 하나가 사라짐)
}

//move를 쓰면 copy하지 않고 swap이 가능해 짐
template <class T>
void swap2(T& a, T& b) {
	T tmp(std::move(a));
	a = std::move(b);
	b = std::move(tmp);
}

////////////////////////////////////////////////

///////////////////////////std::move를 사용하는 클래스의 예
struct Person
{
	string name;
	int* year = nullptr;

	Person()
	{}

	Person(string p_name, const int p_year) : name(move(p_name)), year(new int(p_year))
	{
		cout << "constructed" << endl;
	}

	Person(const Person& other) noexcept :
		name(move(other.name)), year(new int(*other.year))
	{
		cout << "copy constructed" << endl;
	}

 	Person(Person&& other) noexcept :
 		name(move(other.name)), year(nullptr)
 	{
 		// Rvalue의 힙에서 할당된 year를 이동시킵니다.
 		year = other.year;
 		// Rvalue의 year를 nullptr 초기화 시킵니다.
 		other.year = nullptr;
 
 		cout << "move constructed" << endl;
 	}

	Person& operator=(const Person& other) noexcept
	{
		if (this != &other)
		{
			this->name = other.name;
			this->year = new int(*other.year);
		}
		cout << "copy Assignment operator" << endl;
		return *this;
	}

	Person& operator=(Person&& other) noexcept
	{
		if (this != &other)
		{
			this->name = std::move(other.name);

			if (this->year) delete this->year;

			this->year = other.year;
			other.year = nullptr;
		}
		cout << "move Assignment operator" << endl;
		return *this;
	}

	virtual ~Person()
	{
		if (nullptr != year)
		{
			delete year;
		}
		cout << "destructed " << endl;
	}
};




class Base
{
public:
	// 소멸자 가상으로 명시적 선언
	// 이동 연산자를 명시하지 않으면, 자동 생성되지 않는다.
	Base() {};
	virtual ~Base() = default;

	// 이제 이동 연산자 명시 선언
	// 이동 연산자의 C++ 기본 행동으로 선언 (굳이 자체 이동 처리를 할 게 없다, 기본으로 충분)
	// 이동 연산자가 선언되어 있으므로, 복사 연산자는 삭제된다.
	Base(Base&&) = default;
	Base& operator = (Base&&) = default;

	// 이제 복사 연산자까지 명시 선언
	// 복사 연산자의 C++기본 행동으로 선언 (굳이 자체 복사 처리를 할 게 없다, 기본으로 충분) 
 	Base(const Base&) = default;
 	Base& operator = (const Base&) = default;

	// ... 하략 ...

	int a, b, c, d, e;
	void Test1(){ a = 1; b = 2; c = 3; d = 4; e = 5; }
	void Test2() { a = 6; b = 7; c = 8; d = 9; e = 10; }
	void Test3() { a = 11; b = 12; c = 13; d = 14; e = 15; }
};





int main()
{
	std::vector

	Base a, b, c;
	a.Test1();
	b.Test2();
	c.Test3();

	a = std::move(b);

	// 예제 - 1
	//std::move가 이루어지지 않고, 복사 생성자가 호출되는 경우
    string str = "For Move";
    vector<string> vstr;
    vstr.push_back(str);

	//std::move 함수로 이동 연산자가 호출되는 경우.
	//std::string의 경우 기본적으로 이동 연산자가 구현되어 있다.
	//하지만 사용자가 만든 클래스의 경우 명시적으로 선언해주지 않는 이상 암시적으로 이동 연산자가 호출되지 않는다.
	string str2 = "For Move";
	vector<string> vstr2;
	vstr2.push_back(move(str2));


	// 예제 - 2
	int N1 = 50, N2 = 100, N3 = 150;
	swap1(N1, N2);
	swap2(N2, N3);

	// 예제 - 3

	Person p1("ahn", 1985);
	// p1을 std::move를 통해서 이동연산이 가능하도록 캐스팅합니다.
	Person p2 = std::move(p1);



	// 예제 - 4
	const Person p3("ahn", 1985);

	// const Person인 p3을 std::move를 통해서 캐스팅합니다. 
	// 하지만 const Person&&으로 변환되고 const가 붙어서 이동 생성자가 채택되지 못하고
	// p4는 복사 생성자로 생성됩니다.
	Person p4 = std::move(p3);

	

	cout << "Done" << endl;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

