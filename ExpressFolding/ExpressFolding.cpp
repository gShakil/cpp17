// ExpressFolding.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

/*
표현식 접기 (Folding)


*/

#include <iostream>
#include <vector>
#include <set>
//예제 1. 
template<typename ... Ts>
auto sum(Ts ... ts)
{
    /*
    (ts + ...) 혹은 (... + ts ) 둘 다 가능하지만 
    ...가 연산자 오른쪽에 놓이면 오른쪽 접기, 왼쪽에 놓이면 왼쪽 접기.
    왼쪽 단항 접기는 (1 + (2 + (3 + ( 4 + 5)))로 펼쳐짐
    오른쪽 단항 접기는 (((1 + 2) + 3) + 4) + 5)로 펼쳐짐
    */
    return (ts + ...);

    // 이렇게 표현할 시 인자 없이 sum()으로 호출시 0으로 평가되며, sum(1,2,3) 호출시 (1 + (2 + (3 + 0)))으로 평가됨
    // && 로 빈 파라미터를 접으면 true가 되며, ||로 접으면 false가 된다.
    //return (ts + ... + 0);  // 주석 해제시 main()함수에 있는 sum(h,w)때문에 컴파일이 안됨
}


//예제 2.
template<typename R, typename ... Ts>
auto matches(const R& range, Ts ... ts)
{
    /*
    std::count 함수는 세 번쨰 파라미터와 같은 범위에 있는 모든 요소의 개수를 반환.

    */

    return (std::count(std::begin(range), std::end(range), ts) + ...);
}

//예제 3.
template <typename T, typename ... Ts>
bool insert_all(T& set, Ts ... ts)
{
    /*
    std::set 함수의 시그니처
    std::pair<iterator, bool> insert(const value_type& value);
    삽입에 성공하면 리턴되는 bool 변수는 true, 실패하면 false. 
    반복자는 set에 추가된 새로운 요소를 가리킴. 실패하였을 때는 삽입하려는 값과 충돌되는 기존 요소를 가리킴
    */

    return (std::set.insert(ts).second && ...);
}

//예제 4.
template <typename T, typename ... Ts>
bool within(T min, T max, Ts ... ts)
{
    return ((min <= ts && ts <= max) && ...);
}

//예제 5.
template <typename T, typename ... Ts>
void vinsert_all(std::vector<T>& vec, Ts ... ts)
{
    //실제 결과 값에 표현식 접기를 쓰지 않는 개별 vec.push_back(...)으로 파라미터 묶음을
    //펼치기 위해 여기서 (,) 연산자를 사용한 것에 주목.
    //(,) 연산자가 아무 처리도 하지 않는 암시적인 식별 값 void()를 보유하기 때문
    (vec.push_back(ts), ... );
}

int main()
{
    //예제 1.
    int nSum = sum(3, 4, 5); // 12 반환
    std::string h = "Hello";
    std::string w = " World";
    sum(h, w); // Hello World 반환

    //예제 2.
    std::vector<int> v{ 1,2,3,4,5 };
    matches(v, 2, 3); // 2 반환
    matches(v, 100, 200); // 0 반환
    matches("abcdefg", 'x', 'y', 'z'); // 0 반환
    matches("abcdefg", 'a', 'd', 'f'); // 3 반환

    //예제 3.
    std::set<int> my_set{ 1,2,3 };
    insert_all(my_set, 4, 5, 6); // true를 반환
    insert_all(my_set, 7, 8, 2); // false를 반환. 2값이 충돌함
    insert_all(my_set, 4, 2, 5); // 2를 삽입하는 도중 실패. false를 반환. 이 때 my_set는 1,2,3,4를 포함한다. 2를 삽입하는 도중 중단되기 때문.

    //예제 4.
    within(10, 20, 1, 15, 30); // 30이 10 ~ 20에 속하지 않으므로 false 반환
    within(10, 20, 11, 12, 13); // true 반환
    within(5.0, 5.5, 5.1, 5.2, 5.3); // true 반환

    std::string aaa{ "aaa" };
    std::string bcd{ "bcd" };
    std::string def{ "def" };
    std::string zzz{ "zzz" };

    within(aaa, zzz, bcd, def); // true 반환
    within(aaa, def, bcd, zzz); // false 반환

    //예제 5.
    std::vector<int> vint{ 1,2,3 };
    vinsert_all(v, 4, 5, 6);

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
