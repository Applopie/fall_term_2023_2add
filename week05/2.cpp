#include <iostream>

class ToyDescriptor
{
public:
    ToyDescriptor();

    ToyDescriptor(const ToyDescriptor &);
    ToyDescriptor &operator=(const ToyDescriptor &);
    ToyDescriptor(ToyDescriptor &&);
    ToyDescriptor &operator=(ToyDescriptor &&);
    ~ToyDescriptor();

    void Close();

private:
    bool is_open;
};

struct GoodType;
struct GoodType2;
struct BadType;

template <class T, class U = void>
struct IsGoodType;

template<>
struct IsGoodType<GoodType> {
    static const bool value = true;
};

template <>
struct IsGoodType<GoodType2>
{
    static const bool value = true;
};

template<class T, class U>
struct IsGoodType {
    static const bool value = false;
};

template<class T>
struct IsGoodType<T, std::enable_if_t<std::is_integral_v<T>>> {
    static const bool value = true;
};

template <class T>
inline constexpr bool IsGoodTypeV = IsGoodType<T>::value;


ToyDescriptor &operator<<(ToyDescriptor &td, const char *str)

int main() {
    std::cout << std::boolalpha
}