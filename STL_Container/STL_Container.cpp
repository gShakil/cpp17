// STL_Container.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void quick_remove_at(std::vector<T>& v, std::size_t idx)
{
    if (idx < v.size())    {
        v[idx] = std::move(v.back());
        v.pop_back();
    }
}
template <typename T>
void quick_remove_at(std::vector<T>& v
    , typename std::vector<T>::iterator it)
{
    if (it != v.end()) {
        *it = std::move(v.back());
        v.pop_back();
    }
}
//예제 3.
//void insert_sorted(vector<string>& v, const string& word) {
//    const auto insert_pos(lower_bound(begin(v), end(v), word));
//    v.insert(insert_pos, word);
//}
template <typename C, typename T>
void insert_sorted(C& v, const T& item)
{
    const auto insert_pos(lower_bound(begin(v), end(v), item));
    v.insert(insert_pos, item);
}



int main()
{
    //예제 1. 원래의 순서가 중요한 경우 삭제 방법중 하나
    vector<int> v{ 1,2,3,2,5,2,6,2,4,8 };
    const auto new_end(remove(begin(v), end(v), 2)); // 벡터에는 2 값이 두 개 이상 존재 .해당 값을 삭제함
    v.erase(new_end, end(v));

	for (auto i : v) {
		cout << i << ", ";
	}
    cout << "=================================" << '\n';

	const auto odd([](int i) {return i % 2 != 0; });
    v.erase(remove_if(begin(v), end(v), odd), end(v)); // 위 두 단계를 거치지 않고 한 번에 제거할 수 있다.
	v.shrink_to_fit(); // 크기에 맞게 신규 메모리 영역을 할당하고 모든 요소를 신규 메모리 영역으로 옮긴다.

    for (auto i : v) {
        cout << i << ", ";
    }
    cout << "=================================" << '\n';

    //예제 2. quick_remove
    //원래의 순서가 중요치 않은 경우 O(1)의 시간으로 삭제

    //방법 1. 인덱스를 아는 경우
    std::vector<int> vv{ 123,456,789,100,200 };
    quick_remove_at(vv, 2);
    for (int i : vv)
    {
        std::cout << i << ",";
    }
    std::cout << '\n';

    //방법 2. 인덱스를 모르는 경우
    quick_remove_at(vv, std::find(std::begin(vv), std::end(vv), 123));
	for (int i : vv)
	{
		std::cout << i << ",";
	}
	std::cout << '\n';
    

    //예제 3. 벡터에 정렬된 상태로 입력
    vector<string> vs{ "some", "random", "words", "without", "order", "aaa", "yyy" };
    sort(begin(vs), end(vs)); // 해당 벡터를 정렬한다.

    insert_sorted(vs, "foobar");
    insert_sorted(vs, "zzz");
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
