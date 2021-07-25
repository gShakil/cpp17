// STL_Container_map.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <unordered_map>

using namespace std;
//예제 1.
struct billionaire {
    string name;
    double dollars;
    string country;
};

//예제 2.

//예제 3.
template <typename M>
void print(const M& m) {
    cout << "\n***Race platement***\n";
    for (const auto& [placement, driver] : m) {
        cout << placement << ": " << driver << '\n';
    }
}
//예제 4.
//평범한 해시 함수로 처리할 수 없는 자신만의 사용자 정의 구조체 정의.
struct coord {
    int x;
    int y;

    bool operator==(const coord& r) {
        return this->x == r.x && this->y == r.y;
    }
};
//STL 고유의 해시 능력을 최대한 활용하기 위해 std 네임스페이스를 열어 자신만의
//특수화된 std::hash 템플릿 구조체를 생성한다. 여타 해시 특수화와 같이 해당
//구조체도 같은 using 타입 에일리어스(alias)절을 포함시킨다.

//이 때 해상 struct에서의 핵심은 operator() 정의에 있다. 아주 기초적인 해시
//기술인 struct coord의 숫자 멤버 변수를 추가하는 단순한 과정이지만,
//어떻게 처리하는지 보여주기만 하면 되므로 여기서는 이것으로 충분하다.
//훌륭한 해시 함수는 전체 범위에 걸쳐 값을 최대한 균등하게 배분함으로써
//해시 충돌을 방지한다.
namespace std
{
    template<>
    struct hash<coord>
    {
        using argument_type = coord;
        using result_type = size_t;
        result_type operator()(const argument_type& c) const
        {
            return static_cast<result_type>(c.x)
                + static_cast<result_type(c.y);
        }
    };
}

int main()
{
    //예제 1.
    list<billionaire> billionaires{
        {"Bill gates", 86.0, "USA"},
        {"Warren Buffer", 75.6, "USA"},
        {"Jeff Bezos", 72.8, "USA"},
        {"Amancio Ortega", 71.3, "Spain"},
        {"Mark Zuckerberg", 56.0, "USA"},
        {"Carlos Slim", 54.5, "Mexico"},
        {"Bernard Arnault", 41.5, "France"},
        {"Liliane Bettencourt", 39.5, "France"},
        {"Wang Jianlin", 31.3, "China"},
        {"Li Ka-shing", 31.2, "Hong Kong"}
    };

    map<string, pair<const billionaire, size_t>> m;

    for (const auto& b : billionaires) {
        //try_emplace: 키가 이미 존재하는 경우 try_emplace가 해당 키와 관련된 객체를 생성하지 않는다.
        //이는 특히 해당 타입의 객체 생성 비용이 매우 높은 경우 성능 향상에 큰 도움이 된다.
        auto [iterator, success] = m.try_emplace(b.country, b, 1);
        
        if (!success) {
            iterator->second.second += 1;
        }
    }

    for (const auto& [key, value] : m) {
        const auto& [b, count] = value;
        cout << b.country << " : " << count
            << " billionaires. Richest is "
            << b.name << " with " << b.dollars
            << " B$\n";
    }
    //예제 2.
    //std::map에 여러 요소를 삽입하고 이에 해당하는 삽입 판별을 이용해 검색 횟수를 줄임.
    map<string, size_t> m2{ {"b",1}, {"c",2}, {"d",3} };

    //처음에는 판별이 없으므로 맵의 end 반복자를 가리키는 가장 첫 번째 삽입을 처리한다.
    auto insert_it(std::end(m2));

    //주어진 반복자 판별을 이용하여 거꾸로 된 알파벳순으로 요소를 삽입할 것.
    //그러고 난 후 이를 삽입 함수의 반환값으로 다시 초기화.
    //다음 요소는 판별 바로 직전에 삽입됨.
    for (const auto& s : { "z", "y", "x", "w" }) {
        insert_it = m2.insert(insert_it, { s, 1 });
    }

    //단순히 처리되지 않은 경우를 보여주기 위하여 가장 뒤쪽에
    //가장 왼쪽에 위치하여야 하는 문자열을 삽입하자.
    m2.insert(end(m2), { "a",1 });

    //내용물을 출력해보면 잘못된 삽입 판별이 큰 영향을 끼치지는 않는다는 것을 볼 수 있다.
    for (const auto& [key, value] : m2) {
        cout << "\"" << key << "\":" << value << ", ";
    }
    
    //예제 3.
    //c++17 이후부터 가능한 메모리 재할당 없이 키 값 요소를 변경하는 방법.
    map<int, string> race_placement{
        {1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
        {4, "Peach"}, {5, "Yoshi"}, {6, "Koopa"},
        {7, "Toad"}, {8, "Donkey Kong Jr."}
    };
    print(race_placement);

    //3번과 8번의 키 값을 변경하고자 한다.
    //extract 함수는 C++17부터 도입된 함수.
    //이 함수는 할당 처리로 발생하는 어떤 부작용도 없이 맵으로부터 특정 요소를 효과적으로 제거한다.
    //아래 함수 외에도 iterator로 추출하는 함수가 오버로드 되어있는데, 그 함수는 값을 찾지 않아도 되기에 조금 더 빠르다.
    auto a(race_placement.extract(3));
    auto b(race_placement.extract(8));

    //a.empty() // node_type이 비어있는지 확인 가능. 존재하지 않는 키 값에 대하여 추출했을 때 판별해야 한다.

    //여기서 두 키가 서로 변경된다.
    //맵 노드 키는 const로 정의돼 보통 변경되지 않지만, extract 함수를 이용해 추출한 해당 요소의 키를 변경할 수 있다.
    swap(a.key(), b.key());

    //insert 함수는 c++17의 새로운 오버로드 기능을 갖고 있다. 즉, 할당자의 힘을 빌리지 않고도 삽입할 수 있게 추출된 노드를 다룰 수 있다.
    race_placement.insert(move(a));
    race_placement.insert(move(b));

    print(race_placement);

    //예제 4. std::unordered_map을 사용자 지정 타입으로 사용
    //위의 int main() 함수 바깥에서 coord 구조체를 정의함으로써 struct coord를 std::unordered_map의 키로 받아
    //임의의 값으로 매핑할 수 있게 되었다.
    std::unordered_map<coord, int> um{
        {{0,0}, 1}, {{0,1}, 2}, {{2,1},3}
    };
    for (const auto& [key,value] : um) {
        cout << "key : " << key << " value : " << value << std::endl;
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
