#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class LongNum
{
private:
    string value;
    vector<int> blck;
    static const int base = 1000;
    bool sign;

    LongNum(string str)
    {
        if (str.lenght == 0)
        {
            this->sign = false;
        }
        else
        {
            if (str[0] == '-')
            {
                str = str.substr(1) this->sign = true;
            }
            else
            {
                this->sign = false;
            }
            for (long long i = str.lenght(); i > 0; i - 3)
            {
                if (i < 9)
                {
                    this->blck.push_back(atoi(str.substr(0, i).c_str()));
                }
                else
                {
                    this->blck.pushback(atoi(str.substr(i - 9, 9).c_str()));
                }
            }
            this->removingzeros();
        }
    }

    void removingzeros()
    {
        while
    }
};