#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using u16 = uint16_t;

class LongNum
{
public:
    vector<u16> digits;
    bool sign;

    LongNum() // zero constructor
    {
        sign = true;
        digits.push_back(0);
    }
    LongNum(const string &value) // main constructor
    {

        if (value.empty())
        {
            LongNum();
        }

        u16 len = 0;
        if (value[0] == '-')
        {
            sign = false;
            len = 1;
        }
        else
        {
            sign = true;
        }
        for (int i = len; i < value.length(); i++)
        {
            int a = value[i] - '0';
            digits.push_back(a);
        }

        DeleteUnnZeros();
    };
    LongNum(long long numb) // constructor for suitable numbers
    {
        LongNum(to_string(numb));
    }
    LongNum(const LongNum &rhs) // copying mechanism
    {
        sign = rhs.sign;
        digits = rhs.digits;
    };

    /*LongNum(LongNum &&rhs) // replacement
        : digits(rhs.digits), sign(rhs.sign)
    {
        rhs.digits.clear();
    }*/

    LongNum &operator=(const LongNum &rhs) // assignment by copying
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            sign = rhs.sign;
            digits = rhs.digits;
            return *this;
        }
    }

    /*LongNum &operator=(const LongNum &rhs) // assignment by replacement
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            swap(sign, rhs.sign);
            swap(digits, rhs.digits);
            return *this;
        }
    }*/

    bool operator==(const LongNum &rhs) const
    {
        if ((sign != rhs.sign) || (digits.size() != rhs.digits.size()))
        {
            return false;
        }
        for (int i = 0; i < digits.size(); i++)
        {
            if (digits.at(i) != rhs.digits.at(i))
            {
                return false;
            }
        }
        return true;
    }
    bool operator>(const LongNum &rhs) const
    {
        if (sign && !rhs.sign)
        {
            return true;
        }
        if (!sign && rhs.sign)
        {
            return false;
        }

        if (sign)
        {
            if (digits.size() > rhs.digits.size())
            {
                return true;
            }
            else if (digits.size() < rhs.digits.size())
            {
                return false;
            }
            else
            {
                for (int i = 0; i < digits.size(); i++)
                {
                    if (digits.at(i) > rhs.digits.at(i))
                    {
                        return true;
                    }
                    else if (digits.at(i) < rhs.digits.at(i))
                    {
                        return false;
                    }
                }
            }
        }
        if (!sign)
        {
            if (digits.size() > rhs.digits.size())
            {
                return false;
            }
            else if (digits.size() < rhs.digits.size())
            {
                return true;
            }
            else
            {
                for (int i = 0; i < digits.size(); i++)
                {
                    if (digits.at(i) > rhs.digits.at(i))
                    {
                        return false;
                    }
                    else if (digits.at(i) < rhs.digits.at(i))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    bool operator<(const LongNum &rhs) const
    {
        if (sign && !rhs.sign)
        {
            return false;
        }
        if (!sign && rhs.sign)
        {
            return true;
        }

        if (sign)
        {
            if (digits.size() > rhs.digits.size())
            {
                return false;
            }
            else if (digits.size() < rhs.digits.size())
            {
                return true;
            }
            else
            {
                for (int i = 0; i < digits.size(); i++)
                {
                    if (digits.at(i) > rhs.digits.at(i))
                    {
                        return false;
                    }
                    else if (digits.at(i) < rhs.digits.at(i))
                    {
                        return true;
                    }
                }
            }
        }
        if (!sign)
        {
            if (digits.size() > rhs.digits.size())
            {
                return true;
            }
            else if (digits.size() < rhs.digits.size())
            {
                return false;
            }
            else
            {
                for (int i = 0; i < digits.size(); i++)
                {
                    if (digits.at(i) > rhs.digits.at(i))
                    {
                        return true;
                    }
                    else if (digits.at(i) < rhs.digits.at(i))
                    {
                        return false;
                    }
                }
            }
        }
        return false;
    }

    LongNum operator-() const
    {
        LongNum res = *this;
        res.sign = !sign;

        return res;
    }

    LongNum operator+(LongNum &rhs) const
    {
        if ((sign && rhs.sign) || (!sign && !rhs.sign))
        {
            return summarizing(*this, rhs);
        }
        if (sign && !rhs.sign)
        {
            if (digits.size() == rhs.digits.size())
            {
                if (*this > -rhs)
                {
                    return subtraction(*this, rhs);
                }
                else
                {
                    return -subtraction(-rhs, -*this);
                }
            }
            else if (digits.size() > rhs.digits.size())
            {
                return subtraction(*this, rhs);
            }
            else
            {
                return -subtraction(-rhs, -*this);
            }
        }
        if (!sign && rhs.sign)
        {
            if (digits.size() == rhs.digits.size())
            {
                if (-*this > rhs)
                {
                    return -subtraction(-*this, -rhs);
                }
                else
                {
                    return subtraction(rhs, *this);
                }
            }
            else if (digits.size() > rhs.digits.size())
            {
                return -subtraction(-*this, -rhs);
            }
            else
            {
                return subtraction(rhs, *this);
            }
        }
        return rhs;
    }

    LongNum operator-(LongNum &rhs) const
    {
        if ((sign && !rhs.sign) || (!sign && rhs.sign))
        {
            return summarizing(*this, rhs);
        }
        else if (sign)
        {
            if (digits.size() >= rhs.digits.size())
            {
                return subtraction(*this, rhs);
            }
            else
            {
                return -subtraction(-rhs, -*this);
            }
        }
        else if (!sign)
        {
            if (digits.size() <= rhs.digits.size())
            {
                return subtraction(rhs, *this);
            }
            else
            {
                return -subtraction(-*this, -rhs);
            }
        }
    }

    LongNum operator*(LongNum &lhs) const
    {
        LongNum result;
        u16 rhsl = digits.size();
        u16 lhsl = lhs.digits.size();

        LongNum temp;

        if ((sign && lhs.sign) || (!sign && !lhs.sign))
        {
            result.sign = true;
        }
        if ((!sign && lhs.sign) || (sign && !lhs.sign))
        {
            result.sign = false;
        }

        size_t zeros_to_insert = 0;
        for (int i = lhs.digits.size() - 1; i >= 0; i--)
        {
            size_t digit = lhs.digits.at(i);
            temp = multiply(*this, digit);
            temp.digits.insert(temp.digits.end(), zeros_to_insert++, 0);
            result = result + temp;
        }
        return result;
    }

private:
    void DeleteUnnZeros()
    {
        while (digits.size() > 1 && digits.at(0) == 0)
        {
            digits.erase(digits.begin(), digits.begin() + 1);
        }
    };

    LongNum summarizing(const LongNum &rhs, const LongNum &lhs) const
    {
        LongNum result;
        result.digits.clear();
        u16 rhsl = rhs.digits.size();
        u16 lhsl = lhs.digits.size();
        size_t index = 0;
        u16 sum = 0;

        while (index < rhsl && index < lhsl)
        {
            sum = sum / 10 + rhs.digits.at(rhsl - index - 1) + lhs.digits.at(lhsl - index - 1);
            result.digits.insert(result.digits.begin(), sum % 10);
            index++;
        }
        if (rhsl >= lhsl)
        {
            while (index < rhsl)
            {
                sum = sum / 10 + rhs.digits.at(rhsl - index - 1);
                result.digits.insert(result.digits.begin(), sum % 10);
                index++;
            }
            if (sum / 10 != 0)
            {
                result.digits.insert(result.digits.begin(), 1);
            }
        }
        else
        {
            while (index < lhsl)
            {
                sum = sum / 10 + lhs.digits.at(lhsl - index - 1);
                result.digits.insert(result.digits.begin(), sum % 10);
                index++;
            }
            if (sum / 10 != 0)
            {
                result.digits.insert(result.digits.begin(), 1);
            }
        }
        result.sign = rhs.sign;
        return result;
    }

    LongNum subtraction(const LongNum &rhs, const LongNum &lhs) const
    {
        LongNum result;
        result.digits.clear();
        u16 rhsl = rhs.digits.size();
        u16 lhsl = lhs.digits.size();
        size_t index = 0;
        u16 res = 0;
        bool decrease = false;

        while (index < rhsl && index < lhsl)
        {
            if (rhs.digits.at(rhsl - index - 1) >= lhs.digits.at(lhsl - index - 1))
            {
                res = rhs.digits.at(rhsl - index - 1) - lhs.digits.at(lhsl - index - 1);
                if (decrease == true)
                {
                    res = res - 1;
                }
                decrease = false;
                result.digits.insert(result.digits.begin(), res);
                index++;
            }
            else
            {
                res = 10 + rhs.digits.at(rhsl - index - 1) - lhs.digits.at(lhsl - index - 1);
                if (decrease == true)
                {
                    res = res - 1;
                }
                if (res == 10)
                {
                    res = 0;
                    decrease = false;
                }
                else
                {
                    decrease = true;
                }
                result.digits.insert(result.digits.begin(), res);
                index++;
            }
        }
        while (index < rhsl)
        {
            res = rhs.digits.at(rhsl - index - 1);
            if (decrease)
            {
                if (res == 0)
                {
                    decrease = true;
                    res = 9;
                }
                res = res - 1;
            }
            result.digits.insert(result.digits.begin(), res);
            index++;
        }

        for (size_t i = 0; i < result.digits.size(); i++)
        {
            if (result.digits[0] == 0)
            {
                result.digits.erase(result.digits.cbegin());
            }
            else
            {
                break;
            }
        }
        return result;
    }

    LongNum multiply(const LongNum &lhs, unsigned int rhs) const
    {
        LongNum result;
        result.digits.clear();
        result.sign = true;
        unsigned int backup = 0;
        for (int i = lhs.digits.size() - 1; i >= 0; i--)
        {
            unsigned int digitproduct = lhs.digits.at(i) * rhs + backup;
            if (digitproduct > 9)
            {
                backup = digitproduct / 10;
                digitproduct %= 10;
            }
            else
                backup = 0;
            result.digits.push_back(digitproduct);
        }
        if (backup != 0)
            result.digits.push_back(backup);
        std::reverse(result.digits.begin(), result.digits.end());
        return result;
    }
};

std::ostream &operator<<(std::ostream &os, const LongNum &rhs)
{
    if (rhs.digits.size() == 0)
    {
        return os;
    }

    if (!rhs.sign)
    {
        os << '-';
    }
    for (int i = 0; i < rhs.digits.size(); i++)
    {
        os << rhs.digits.at(i);
    }
    os << '\n';

    return os;
}

/*int main()
{
    LongNum a("154");
    LongNum b("23");
    LongNum c("2");
    cout << b << ' ' << a << endl;
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * c << endl;
    return 0;
}*/