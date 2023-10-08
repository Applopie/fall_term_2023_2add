
#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

int main()
{
    string value = "124";
    vector<int> digits;
    int a = value[1] - '0';
    cout << a;
    digits.push_back(a);
    cout << digits[0];
    return 0;
}