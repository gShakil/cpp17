// ifswitch_Restricted.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
/*
if와 switch 구문으로 변수의 범위를 제한할 수 있다
*/
#include <iostream>
#include <map>

int main()
{
    //1. if 구문
    //std::map의 find 함수를 사용하여 문자열 맵에서 특정 문자를 찾는 경우.
    char c = 'F';
    std::map<int, char> stdmap;
    if (auto var = stdmap.find(c); var != stdmap.end())
    {
        //*var이 유효하며, 작업을 수행한다
    }
    else
    {
        //var은 마지막 참조자이므로 예외처리 구간이다.
    }
    //var은 더 이상 사용할 수 없다.

    //2. switch 구문
    switch (char c(getchar()); c)
    {
    case 'a':
        break;
    case 'b':
        break;
        //...
    default:
        break;
    }

    //3. c++17 이전과 c++17에서의 if
    //이전:
    bool bVar(false);
    if (bVar)
    {
        //bVar 접근 가능
    }
    else
    {
        //bVar 접근 가능
    }
    // 여전히 //bVar 접근 가능

    //c++17:
    //if(bool bVar (init_value); condition)
    if (bool bVar2(false); bVar = true)
    {
        // bVar2 접근 가능
    }
    else
    {
        // bVar2 접근 가능
    }
    // bVar2 접근 불가능

    //4. c++17 이전과 c++17에서의 switch
    //이전:
    bool bSw(false);
    switch (bSw)
    {
    case true:
        break;
    case false:
        break;
    }
    //bSw 접근 가능

    //c++17:
    switch (bool bSw2(false); bSw)
    {
    case true:
        break;
    case false:
        break;
    }
    //bSw2 접근 불가능

    //위와 같은 방법으로 크리티컬 섹션의 범위도 제한할 수 있다.
    /*
    * lock_guard: 생성자의 인자로 뮤텍스를 받는 클래스.
    * 생성자에서 뮤텍스를 잠그며 소멸자에서 해제한다.
    if (std::lock_guard<std::mutex> lg{ my_mutex }; some_condition)
    {

    }
    else
    {

    }
    */
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
