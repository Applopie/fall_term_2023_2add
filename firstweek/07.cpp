#include <fstream>
#include <iostream>

using namespace std;

int fib(int n)
{
    if (n == 1 or n == 2)
    {
        return 1;
    }
    else
    {
        return fib(n - 1) + fib(n - 2);
    }
}

int main()
{
    int a = 0;
    cin >> a;
    ofstream fout("fibs.txt");
    for (int i = 0; i < a; i++)
    {
        fout << i + 1 << ' ' << fib(i + 1) << endl;
    }
    fout.close();
    return 0;
}