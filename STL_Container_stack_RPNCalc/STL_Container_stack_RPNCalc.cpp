// STL_Container_stack_RPNCalc.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <stack>
#include <iterator>
#include <map>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;

//RPN 파서
//문자열 내에서 수학식의 시작과 끝을 나타내는 반복자 쌍을 받는다.
//이는 토큰 하나하나씩 처리될 것이다.
template <typename IT>
double evaluate_rpn(IT it, IT end)
{
    //토큰을 순환하는 동안 연산이 보일 때까지 나온느 모든 피연산자를 기억해야 함.
    //이 피연산자들이 쌓아올릴 대상이다.
    //모든 숫자를 분석해 double 정밀도의 부동소수점에 저장하면 double 값으로 쌓이게 된다.
    stack<double> val_stack;

    //스택에 있는 내용물에 편리하게 접근하기 위해 헬퍼 함수를 구현한다.
    auto pop_stack([&]() {
        auto r(val_stack.top()); val_stack.pop();
        return r;
        });

    //지원하는 수학 연산 전부를 정의한다.
    //이를 맵에 저장해서 모든 연산 토큰을 실제 연산과 연결한다.
    //이 때 연산은 호출 가능한 람다로 표현되는데, 피연산자 두 개를 받아 더하거나 곱한 후
    //결과물을 반환한다.

    map<string, double(*) (double, double)> ops{
        {"+", [](double a, double b) {return a + b; }},
        {"-", [](double a, double b) {return a - b; }},
        {"*", [](double a, double b) {return a * b; }},
        {"/", [](double a, double b) {return a / b; }},
        {"^", [](double a, double b) {return pow(a,b); }},
        {"%", [](double a, double b) {return fmod(a,b); }}
    };

    //이제 입력 내용을 순환할 수 있다.
    //입력 반복자가 문자열을 제공한다는 가정하에 각 토큰당 새로운 std::stringstream을 넘겨주는데,
    //이는 숫자를 파싱할 수 있기 때문이다.
    for (; it != end; ++it) {
        stringstream ss{ *it };

        //이제 각각의 토큰으로부터 double 값을 얻어내보자.
        //성공적으로 처리되면 스택에 쌓아놓은 피연산자를 갖는다.
        if (double val; ss >> val) {
            val_stack.push(val);
        }
        //성공하지 못하더라도 연산자의 문제는 아니다.
        //사용자가 다루는 모든 연산은 2항으로 되어 있으므로, 스택으로부터 가장 마지막 두 피연산자를 꺼내야한다.
        else {
            const auto r{ pop_stack() };
            const auto l{ pop_stack() };

            //it 반복자를 참조해 이미 문자열로 나타내는 피연산자를 얻는다.
            //ops 맵을 질의해서 파라미터로 l과 r 두 개의 피연산자를 허용하는 람다 객체를 얻는다.
            try {
                const auto& op(ops.at(*it));
                const double result{ op(l,r) };
                val_stack.push(result);
            }
            catch (const out_of_range&) {
                //수학적 응용 부분을 try절로 감싸서 혹시 있을지 모를 예외의 경우를 잡아낼 수 있게 한다.
                //알 수 없는 수학 연산을 사용자가 제시하면 맵의 at 호출이 out_of_range 예외를 던진다.
                //이러한 경우 invalid_argument 로 명확하지 않은 해당 연산 문자열을 나르는 예외를 다시 던지게 된다.
                throw invalid_argument(*it);
            }
        }
    }
    
    //반복문이 종료하면 스택에 최종 결과물이 나온다.
    return val_stack.top();
    
}

int main()
{
	//앞서 언급한 RPN 파서를 사용해보자.이 처리를 위해 표준 입력을 std::istream_iterator 쌍으로 감싸 넣은 다음, 이를 RPN 파서 함수로 넘겨준다.
		try
	{
		cout << evaluate_rpn(istream_iterator<string>{cin}, {}) << '\n';
	}
	catch (const invalid_argument& e)
	{
		cout << "Invalid operator: " << e.what() << '\n';
	}
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
