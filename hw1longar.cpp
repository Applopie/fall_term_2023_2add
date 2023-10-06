#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using u16 = uint16_t;

class LongNum
{
public:
    LongNum()
    {
        sign = true;
        digits.push_back(0);
    }
    LongNum(const string &value)
    {

        if (value.empty())
        {
            LongNum();
        }

        len = 0;
        if (value[0] == '-')
        {
            sign = false;
            len = 1;
        }
        else
        {
            sign = true;
        }
        for (int i = len; i < value.lenght(); i++)
        {
            digits.push_back(value.at(i));
        }

        DeleteUnnZeros();
    };
    LongNum(long long numb)
    {
        LongNum(to_string(numb));
    }
    LongNum(const LongNum &rhs)
    {
        sign = rhs.sign;
        digits = rhs.digits;
    };

private:
    void DeleteUnnZeros()
    {
        while (digits.size > 1 && digits.at(0) == 0)
        {
            digits.erase(digits.begin(), digits.begin() + 1)
        }
    };

    int digit(int index);
    vector<u16> digits;
    bool sign;
};