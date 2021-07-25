// STL_Map_빈도수.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

//덧붙여진 쉼표, 마침표, 콜론을 단어로부터 분리해내기 위해 헬퍼 함수 선언
string filter_punctuation(const string &s)
{
    const char* forbidden{ ".,:; " };
    const auto idx_start(s.find_first_not_of(forbidden));
    const auto idx_end(s.find_last_not_of(forbidden));
    return s.substr(idx_start, idx_end - idx_start + 1);
}

int main()
{
    //빈도수 카운터에 보이는 모든 단어와 연관된 맵 수집.
    //추가로 지금까지 등장한 단어 중 가장 긴 단어의 길이를 기록하는 변수를 갖는다
    //그러면 나중에 결과를 출력할 때 빈도수 도표를 깔끔하게 들여쓸 수 있다.
    map<string, size_t> words;
    int max_word_len{ 0 };

    //std::cin에서 std::string 변수로 나르는 도중 해당 입력 스트림이 공백을 제거할 것.
    //이렇게 하면 입력 내용을 단어별로 얻을 수 있다.
    string s;
    while (cin >> s) {
        if (s == ";;") break;

        //여기 나온 단어에는 쉼표, 마침표, 콜론이 있을 수 있는데, 문장의 마지막에서 대개 사용된다.
        //앞서 정의한 헬퍼 함수를 이용해 이러한 쉼표, 마침표, 콜론을 분리해낸다.
        auto filtered(filter_punctuation(s));

        //해당 단어가 지금까지 나온 단어 중 가장 길 경우 max_word_len변수를 갱신시킨다
        max_word_len = max<int>(max_word_len, filtered.length());

        //words 맵 안에서 단어의 카운터 값 증가.
        //처음에는 증가시키기 전 암묵적으로 생성된다.
        ++words[filtered];
    }
        //여기까지 오면 words 맵에서 입력 스트림으로부터 모든 고유 단어를 저장했다.
        //이는 각 단어의 빈도수를 나타내는 카운터와 짝을 짓는다.
        //해당 맵은 단어들을 키로 사용하며, 알파벳 순서로 정리되어 있다.
        //빈도수에 따라 모든 단어를 정렬해 출력하기 위하여 모든 단어-빈도수 쌍이 들어갈 벡터의 인스턴스를 만들고,
        //이를 맵에서 벡터로 옮겨놓는다.
        vector<pair<string, size_t>> word_counts;
        word_counts.reserve(words.size());
        move(begin(words), end(words), back_inserter(word_counts));

        //현재 벡터의 모든 단어-빈도수 쌍은 map과 같은 순서로 들어가있다.
        //빈도수 순으로 벡터를 정렬한다.
        sort(begin(word_counts), end(word_counts), [](auto const& f, auto const& s) {return f.second > s.second; });

        //모든 데이터가 원하는 순서로 놓였으므로, 사용자 터미널에 출력해준다.
        //std::setw를 이용해 깔끔한 들여쓰기 형태의 서식으로 스트림 데이터를 정리해 테이블과 같은 모습으로 만든다.
        cout << "# " << setw(max_word_len) << "<WORD>" << " #<COUNT>\n";
        for (const auto& [word, count] : word_counts)
        {
            cout << setw(max_word_len + 2) << word << " #" << count << '\n';
        }

        cin >> s;
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
