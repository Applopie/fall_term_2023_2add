
#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

int main()
{
    vector<int> digits = {1, 2, 3, 4, 5};
    vector<int> digits2;
    digits2 = digits;
    for (int i = 0; i < 5; i++)
    {
        cout << digits2.at(i) << ' ';
    }
    return 0;
}