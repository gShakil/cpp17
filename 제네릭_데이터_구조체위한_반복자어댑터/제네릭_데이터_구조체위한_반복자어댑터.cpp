// 제네릭_데이터_구조체위한_반복자어댑터.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <deque>

using namespace std;

int main()
{
    //여기서는 이를 int로 특수화하여 표준 입력을 전수로 구문 분석하게 한다.
    //이 반복자를 순환하면 std::vector<int>와 같이 보일 것이다.
    istream_iterator<int> it_cin{ cin };
    istream_iterator<int> end_cin;

    //std::deque<int> 인스턴스를 생성해 표준 입력에 의한 정수를 전부 deque에 복사한다.
    //deque 자체는 반복자가 아니므로 std::back_inserter헬퍼 함수를 사용해 std::back_insert_iterator로 감싸 넣는다.
    //이 특별한 반복자 래퍼는 표준 입력으로부터 받은 각각의 요소에 대해 v.push_back(요소)를 실행하게 된다.
    //이 방법으로 deque의 크기가 자동으로 증가한다.

    deque<int> v;
    copy(it_cin, end_cin, back_inserter(v));

    //다음 예제에서는 std::istringstream을 사용해 deque의 중간 요소들을 복사한다.
    //가장 먼저 문자열 양식에 몇 가지 숫자를 정의한 다음 이를 통해 스트림 인스턴스를 생성해보자.
    istringstream sstr{ "123 456 789" };

    //deque의 어디에 삽입할지 약간의 정보가 필요하다.
    //중간 어디쯤이 될 것이니 deque의 시작 포인터를 사용해 std::next 함수에 넣어준다.
    //이 함수의 두 번째 인자는 v.size() / 2 단계로 나아가 반복자를 반환하게 된다는걸 알려준다.
    //이게 deque의 절반이다.
    //두 번째 파라미터가 첫 번째 파라미터에서 사용되는 반복자의 difference_type이기 때문에 v.size()를 int로 형변환한다.
    auto deque_middle(next(begin(v), static_cast<int>(v.size()) / 2));

    //이제 입력 문자 스트림으로부터 파싱된 정수들을 deque에 하나씩 복사할 수 있다.
    //스트림 반복자 래퍼의 끝 반복자는 생성자 인자가 없는 텅빈 std::istream_iterator<int>일 뿐이다.(코드 라인에 빈 {}괄호로 표시한다)
    //deque는 삽입자 (inserter) 래퍼 std::insert_iterator로 감싸 넣는다.
    //deque_middle 반복자를 사용해 deque의 중간을 가리키게 한다.
    copy(istream_iterator<int>{sstr}, {}, inserter(v, deque_middle));

    //이제 deque의 맨 앞에 몇 가지 요소를 삽입할 수 있도록 std::front_insert_iterator를 사용해보자.
    initializer_list<int> il2{ -1, -2, -3 };
    copy(begin(il2), end(il2), front_inserter(v));

    //마지막 단계로 화면에 deque의 전체 내용을 출력한다. std::ostream_iterator는 출력 반복자처럼 작동한다.
    //여기서는 std::cout의 범위에 사본으로 구한 모든 정수값에 대해 앞으로 순회하며, 각각의 요소 다음에 ", "를 첨부한다.
    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
    cout << '\n';



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
