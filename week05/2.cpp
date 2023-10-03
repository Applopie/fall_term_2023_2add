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

ToyDescriptor &operator<<(ToyDescriptor &td, const char *str);