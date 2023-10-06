
#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

int main()
{
    vector<int> digits = {1, 2, 3, 4, 5};
    digits.erase(digits.begin(), digits.begin() + 1);
    cout << digits.at(0);
    return 0;
}