#include <iostream>

using i32 = int32_t;
using u64 = uint64_t;

/*template <class T>
T sum(T&& a, T&& b) {
    return a+b;
}*/

template <class T, class U>
T sum(T &&a, U &&b)
{
    return a + b;
}

template <class T, class U>
struct SumResult {
    using type = /*typename*/ decltype(std::declval<T>() + std::declval<U>());
};

template <class T, class U> 
SumResult<T, U> Sum(T&& a, U&& b);


int main() {
    std::cout << Sum<i32>(42, 42) << "\n";
    std::cout << Sum<double>(42, 42) << "\n";
}