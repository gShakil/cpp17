// STL반복자_호환_반복자_구현.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <algorithm>

using namespace std;

class num_iterator
{
    int i;
public:
    explicit num_iterator(int position = 0) : i{ position } {}
    int operator*() const { return i; }
    num_iterator& operator++() {
        ++i;
        return *this;
    }
    bool operator != (const num_iterator& other) const {
        return i != other.i;
    }
    bool operator == (const num_iterator& other) const {
        return !(*this != other);
    }
};
class num_range {
    int a;
    int b;
public:
    num_range(int from, int to)
        : a{ from }, b{ to }
    {}
    num_iterator begin() const { return num_iterator{ a }; }
    num_iterator end()   const { return num_iterator{ b }; }
};


/*
c++17 이전에는 반복자 타입을 std::iterator<...>로부터 상속받았어야 했다.
그래야 해당 클래스를 모든 타입 정의를 이용해 자동으로 반복자가 되게 할 수 있었다.
여전히 동작하는 기능이긴 하지만, c++17부터 점차 쓰이지 않고있다.
 
컴파일러 버전에 따라 아래 정의가 존재하지 않으면 오류가 발생할 수 있다.
이는 std::iterator_traits와 관련된 오류이며 이를 해결해주기 위해서는 반복자 클래스의 특성 기능을 활용해야 한다.
num_iterator를 정의한 후에 다음과 같이 std::iterator_traits 타입의 템플릿 구조체 특수화를 작성해준다.
이는 STL에 num_iterator가 전위 반복자 카테고리이며 int 값을 순환한다는 것을 알게 해준다.

일부 STL 알고리즘은 사용되는 반복자 타입의 특징을 알고 있어야 한다.또한 반복자에 의해 순환되는 요소들의 자료형도 알고 있어야 한다.
서로 다른 구현이 필요한 이유다.
반복자 타입이 my_iterator라는 가정하에 모든 STL 알고리즘은 std::iterator_traits<my_iterator>를 통해 타입 정보에 접근하게 된다.
해당 특성 클래스는 서로 다른 타입의 멤버 정의를 최대 다섯 개까지 포함시킨다.
*/
namespace std {
    template<>
    struct iterator_traits<num_iterator> {
        using iterator_category = std::forward_iterator_tag; // 해당 반복자가 속하는 카테고리는 ? 
        using value_type        = int;  // *it로 접근하게 되는 요소가 어떤 타입인지 ? (순수 출력 반복자는 void이다 ) 
        using difference_type   = void; // it1 - it2 를 사용해 얻는 결과가 어떤 타입인지 정의
        using pointer           = int*; // 요소를 가리키기 위해 포인터가 필요한가 ?
        using reference         = int&; // 요소를 참조하기 위해 참조형이 필요한가 ? 
    };
}


int main()
{
    num_range r{ 100, 110 };
    auto [min_it, max_it](minmax_element(begin(r), end(r))); // minmax_element: 해당 범위에서 가장 작은 값과 큰 값을 가리키는 두 개의 정수를 std::pair로 반환
    cout << *min_it << " - " << *max_it << '\n';
}
