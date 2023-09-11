#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    int a = 0;
    cin >> a;
    float arr[a];
    for (int i = 0; i < a; i++)
    {
        arr[i] = float(1) / float(i + 1);
    }
    for (int i = 0; i < a; i++)
    {
        cout.width(4);
        cout.precision(5);
        cout << arr[i] << ' ';
    }
    cout << endl;
    return 0;
}