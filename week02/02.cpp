#include <iostream>
#include <cstdint>

using u32 = uint32_t;

class Array
{
public:
    Array(size_t sz) : size(sz)
    {
        data = new u32[sz];
    }

    Array(const Array &rhs) : size(rhs.size)
    {
        data = new u32[rhs.size];
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = rhs.data[i];
        }
    }

    Array &operator=(const Array &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        Array t(rhs);
        std::swap(size, t.size);
        std::swap(data, t.data);
        return *this;
    }

    Array(Array &&rhs) : size(rhs.size), data(rhs.data)
    {
        rhs.size = 0;
        rhs.data = nullptr;
    }

    ~Array() { delete[] data; }

    const u32 &operator[](size_t index) const
    {
        return data[index];
    }
    u32 &operator[](size_t index)
    {
        return data[index];
    }

public:
    size_t Size() const { return size; }
    size_t size;
    u32 *data;
};

std::ostream &operator<<(std::ostream &os, const Array &a)
{
    if (a.data == nullptr)
        return os << "<MOVED_OUT>";
    os << '[';
    for (size_t i = 0; i < a.Size() - 1; ++i)
    {
        os << a[i] << ", ";
    }
    os << a[a.Size() - 1];
    os << ']';
    return os;
}

int main()
{
    Array a{10};
    for (size_t i = 0; i < 10; ++i)
    {
        a[i] = i;
    }

    Array b = a;
    std::cout << b << '\n';
    a = b;
    b = a;

    Array c = std::move(a);
    std::cout << c << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
}