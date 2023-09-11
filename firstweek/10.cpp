#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    vector<float> hr;
    int a = 0;
    cin >> a;
    for (int i = 0; i < a; i++)
    {
        hr.push_back(float(1) / float(i + 1));
    }
    for (float elem : hr)
    {
        cout << elem << ' ';
    }
    cout << endl;
    return 0;
}