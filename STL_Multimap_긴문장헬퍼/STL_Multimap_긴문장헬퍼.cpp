// STL_Multimap_긴문장헬퍼.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <iterator>
#include <map> // muiltimap 포함
#include <algorithm>

using namespace std;

string filter_ws(const string& s)
{
    //텍스트에서 마침표 부호 사이의 문자열을 추출해 토큰화할 때
    //빈 칸이나 줄바꿈 표시와 같은 공백으로 둘러쌓인 문장을 얻게 됌.
    //이러한 공백은 크기만 키우므로 헬퍼 함수를 정의해 걸러낸다.
    const char* ws{ " \r\n\t" };
    const auto a(s.find_first_not_of(ws));
    const auto b(s.find_last_not_of(ws));
    if (a == string::npos)
        return {};
    return s.substr(a, b);
}

//실제 문장 길이를 계산하는 함수는 모든 문자를 포함한 거대한 문자열을 받아서 std::muiltimap으로 반환한다.
//그리고 정렬된 문장 길이를 해당 문장에 매핑한다.
multimap<size_t, string> get_sentence_stats(const string& content)
{
    //나중에 반환값이 될 multimap 구조체와 몇 가지 반복자를 선언하는 것으로 시작한다.
    //반복문을 사용할 것이므로 end 반복자도 필요하다.
    //그런 다음 두 개의 반복자를 이용해 텍스트 사이에서 연이은 마침표를 찾아낸다.
    //두 마침표 사이에 있는 모든 것은 문장으로 인식한다.
     multimap<size_t, string> ret;
    const auto end_it(end(content));
    auto it1(begin(content));
    auto it2(find(it1, end_it, '.'));

    //it2는 it1으로부터 항상 마침표를 사이에 두고 떨어져 있다.
    //it1이 텍스트의 끝에 도달하지 않는 한 유효하다.
    //두 번째 조건은 it2가 언제나 최소한 한 개 이상의 문자를 사이에 두고 떨어져 있는지를 확인하는 것이다.
    //이 조건을 충족하지 않는 경우 it1과 it2 사이에 읽어낼 문자가 아무것도 없는 것이다.
    while (it1 != end_it && distance(it1, it2) > 0)
    {
        //반복자 사이의 모든 문자를 이용해 하나의 문자열을 만들고,
        //이 문자열의 처음부터 끝까지 모든 공백을 걸러내 순수한 문장 자체의 길이를 계산한다.
        string s{ filter_ws({it1, it2}) };
        //공백으로 이루어진 문장도 있을 수 있다. 이 경우 그냥 해당 문장을 제거한다.
        //그렇지 않은 경우 문장 안에 단어가 몇 개 들어가 있는지 길이를 계산한다.
        //단어 사이에는 빈칸이 있기 때문에 이 처리는 매우 쉽다.
        //그리고 multimap을 이용해 계산한 단어 수를 문장과 함께 저장한다.
        if (s.length() > 0){
            const auto words(count(begin(s), end(s), ' ') + 1);
            ret.emplace(make_pair(words, move(s)));
        }

        //다음 반복문을 위해 선두에 오는 반복자인 it1을 다음 문장의 마침표 옆에 놓는다.
        it1 = next(it2, 1);
        it2 = find(it1, end_it, '.');
    }
    //반복문이 종료되면 multimap이 모든 문장과 그에 해당하는 단어 수로 짝을 지어 포함하고, 이를 반환할 수 있게 된다.
    return ret;
}

int main()
{
	//필요한 함수를 입력하기 전 std::cin이 공백을 건너뛰지 말 것을 명령한다. 문장의 형태가 되려면 여러 공백이 들어있어도 끊어지지 않는 하다로 돼야 하기 때문이다.
    //전체 파일을 읽어고기 위해 std::cin을 캡슐화 하는 입력 문자열 반복자로부터 std::string을 초기화한다.
    cin.unsetf(ios::skipws);
    //string content{ istream_iterator<char>{cin}, {} };
    string content = { "Lorem ipsum dolor sit amet\
, consectetur adipiscing elit. In fermentum dapibus \
nunc a aliquam. Proin tincidunt porta euismod.\
 Integer finibus, tellus luctus iaculis accumsan, \
dui risus faucibus sapien, non auctor nisi lorem id elit.\
 Mauris varius eros nisl, a porttitor metus porttitor non.\
 In quis ligula ligula. Quisque luctus, lectus nec fermentum\
 iaculis, nibh est congue dui, quis dapibus diam mauris sed massa.\
 Lorem ipsum dolor sit amet, consectetur adipiscing elit.\
 Duis tempor tellus est, suscipit varius leo dictum vitae.\
 Ut ut sapien vel erat molestie sodales at sed ligula.\
 Vivamus quis velit mauris. Pellentesque vitae elementum mi.\
 Praesent ex ligula, tristique eget quam non, feugiat consectetur nisl.\
 Fusce tellus ligula, laoreet in sodales sit amet, consectetur eu ligula.\
 Etiam eget ligula cursus, congue eros a, varius neque." };
     
    //출력을 위해 multimap 결과 값이 필요하므로, get_sentence_stats 호출을 반복문에 직접 추가해 문자열과 함께 넘겨준다.
    //해당 요소를 반복문에서 한 줄씩 출력한다.
    for (const auto& [word_count, sentence] : get_sentence_stats(content)) {
        cout << word_count << "words: " << sentence << ".\n";
    }
    
    cin >> content;
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
