// tuple.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

// 예제 1. tuple 리턴
tuple<unsigned char, int, float> GetStockInfo(const std::string &name)
{
    unsigned char N1 = 50;
	int N2 = 150;
	float fValue = 12.34f;
	
	//리턴하는 두 가지 방법 존재
	return { N1, N2, fValue };
	return make_tuple(N1, N2, fValue);
}


// 예제 2. 구조체 리턴
auto foo() {
	struct retVals {        // Declare a local structure 
		int i1, i2;
		string str;
	};

	return retVals{ 10, 20, "Hi" }; // Return the local structure
}

// 예제 3. 구조체 값 캐스팅
struct info {
	unsigned id;
	string name;
	size_t salary;
};




int main()
{

	if constexpr (std::is_same_v<int, bool>)
	{
		cout << " true #1" << endl;
	}
	else
	{
		cout << " false #1" << endl;
	}

	if (std::is_same_v<int, bool>)
	{
		cout << " true #2" << endl;
	}
	else
	{
		cout << " false #2" << endl;
	}

	std::cout << std::is_same<float, std::int32_t>::value << '\n';
 	bool d = std::is_same<int, bool>::value;
	int n = std::is_same<int, bool>::value;
// 	if constexpr (std::is_same<int, bool>)
// 	{
// 		cout << " true #1" << endl;
// 	}
// 	else
// 	{
// 		cout << " false #1" << endl;
// 	}
// 
// 	if (std::is_same<int, bool>)
// 	{
// 		cout << " true #2" << endl;
// 	}
// 	else
// 	{
// 		cout << " false #2" << endl;
// 	}

	// 예제 1. tuple 리턴
	const auto [UC, N, fValue] = GetStockInfo("TupleTest");
	cout << UC << N << fValue << endl;
	tuple<unsigned char, int, float> Ret = GetStockInfo("TupleTest");

	// 예제 2. 구조체 리턴
	const auto [value1, value2, value3] = foo();
	cout << value1 << ", " << value2 << ", " << value3 << endl;
	
	// 예제 3. 구조체 값 캐스팅
	info in{ 1,"num",9876 };
	auto [q, w, e] = in;

	q = 150;

	info in2{ 2,"string",1000 };
	auto& [A, B, C] = in2;

	A = 250; // 값을 변환이 가능하다
	in2.name = "char";
	cout << q << "  " << w << "  " << e << endl;
	cout << A << "  " << B << "  " << C << endl;

	// 예제 4. map 컨테이너 UnPacking
	map<string, size_t> mp{
		{"key1", 1000},
		{"key2",2000},
		{"key3",3000},
	};
	for (const auto& [aa, bb] : mp) {
		cout << aa << "   " << bb << endl;
	}


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
