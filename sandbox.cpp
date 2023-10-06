

// CPP code to demonstrate std::string::at

#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

// Function to demonstrate std::string::at
void atDemo(string str)
{
    cout << str.at(5) << endl;
    cout << typeid(str.at(5)).name() << endl;

    // Below line throws out of
    // range exception as 16 > length()
    // cout << str.at(16);
}

// Driver code
int main()
{
    string str("0123456789");
    atDemo(str);
    vector<int> dig;
    dig.push_back(str.at(2));
    cout << typeid(dig.at(0)).name();
    return 0;
}