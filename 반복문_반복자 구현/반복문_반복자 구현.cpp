// 반복문_반복자 구현.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class num_iterator
{
    int i;
public:
    //명시적인 생성자로 객체를 만드는게 일반적으로 좋은 이유는 다른 타입으로부터 
    //암묵적으로 형을 변환함으로써 객체가 생성되는 사고를 방지할 수 있기 때문.
    explicit num_iterator(int position = 0)
        : i{ position } {}

    //반복자 (*it)를 참조하면 정수를 반환하게 된다.
    int operator*() const { return i; }

    //반복자가 증가(++it)하면 내부 숫자 카운터 i가 증가된다
    num_iterator& operator++()
    {
        ++i;
        return *this;
    }

    //for 반복문은 현재 반복자를 끝 반복자와 비교한다.
    //둘이 같지 않으면 계속해서 순환하게 된다.
    bool operator != (const num_iterator& other) const
    {
        return i != other.i;
    }
};



//이는 반복자 클래스이다. 또한 for(int i: intermediate(a,b)) {...}를 작성해
//a 부터 b 까지 순환하게 사전 프로그래밍이 된 시작과 끝 반복자를 포함하는 중개 객체가 필요하다.
class num_range
{
    //이 클래스는 두 개의 정수 멤버 변수를 포함시킨다.
    //몇 번째 수로 순환을 시작할지와 마지막 수 바로 다음의 수가 몇 번째 수인지를 나타낸다.
    //0에서 9까지 순환할 때 a는 0을, b는 10으로 설정하게 된다.
    int a;
    int b;
public:
    num_range(int from, int to)
        :a{ from }, b{ to }
    {}

    //구현해야 할 것은 멤버 변수 두 가지. 시작 및 종료 함수 둘 뿐이다.
    //둘 다 해당 범위의 시작과 끝을 가리키는 반복자를 반환한다.
    num_iterator begin() const { return num_iterator{ a }; }
    num_iterator end() const { return num_iterator{ b }; }

};

int main()
{
    //클래스가 모두 구현되었으면 100부터 109까지의 범위를 순환해 해당 값을 출력하는 메인 함수를 작성해보자.

    
    /*
    * for( auto: range) {code_block;} 이라 할 때,
    * 컴파일러는 다음과 같이 평가한다.
    
    auto __begin = std::begin(range);
    auto __end = std::end(range);
    for( ; __begin != __end; ++__begin){
        auto x = *__begin;
        코드블록
        }
    따라서 아래 세 가지 연산자가 필요함을 알 수 있다.
    1. operator!= : 같지 않은지 비교
    2. operator++: 전위 증가
    3. operator* : 참조

    //참고) 
    * x.begin()대신에 std::begin(x)을 사용하는 이유: 멤버 함수를 사용할 수 있을 때 std::begin(x)이 자동으로 x.begin()을 호출하기 때문.
    * x가 begin() 함수를 갖지 않는 배열일 경우에는 std::begin(x)은 해당 처리 방법을 자동으로 찾는다. 이는 std::end(x)도 동일하다.
    * begin() / end() 멤버 함수를 제공하지 않는 사용자 정의 타입은 std::begin/std::end로 동작할 수 없다.
    */

    for (int i : num_range{ 100,110 })
        std::cout << i << ", ";
    std::cout << '\n';
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
