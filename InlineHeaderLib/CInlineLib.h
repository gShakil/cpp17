#pragma once
#include <string>
/*
* 3 번
c++ 17 이전에서 가능한 해결책 중 하나.
이 방법으로 복수의 모듈에 헤더 파일이 포함되게 허용해서 어디서든 완전히 같은 인스턴스에 접근 가능
그러나 해당 객체는 프로그램 시작시가 아닌 첫 함수 호출시에 생성된다.
이는 프로그램이 시작될 때 중요한 처리를 할 만한 전역 객체가 필요할 때 문제가 발생한다. 

* 
*/
class foo 
{
public:
	static std::string& standard_string() {
		static std::string s{ "some string" };
	}

}

/*
* 2 번
 C++17에서는 inline이 붙는다면 서로 다른 모듈에 있는 여러 개의 같은 심볼의 정의를 허용할 수 있다.
 링커가 동일한 시그니처로 된 여러개의 심볼을 찾았는데, 인라인으로 정의되어 있다면 첫 번째 심볼을 선택하고
 다른 심볼도 같은 정의를 갖는다고 신뢰하게 된다.
*/
class CInlineLib
{
public:
	static const inline std::string standard_string;
	//{"some static globally avaliable string"};
	inline int ReturnnVal(int n1) { return m_nTestVal; };
protected:
	float ReturnfVal(int n1);
private:
	static inline int m_nTestVal;
	float m_fTestVal;
};
	
inline CInlineLib global_inline_lib;

/*
* 1 번
* //아래와 같이 선언되었을 때 CInclude_Ex1.cpp와 CInclude_Ex2.cpp에서 #include "CInlineLib.h"를 선언할 경우
* //LNK2005 에러와 함께 컴파일에 실패한다.
class CInlineLib
{
public:
	static const std::string standard_string;
	//{"some static globally avaliable string"};
protected:

private:

};

CInlineLib global_inline_lib;
*/