#include <fstream>
#include <iostream>

using namespace std;

int fib(int *array, int rb)
{
    array[0] = array[1] = 1;
    for (int i = 2; i < rb; i++)
    {
        array[i] = array[i - 1] + array[i - 2];
    }
    return *array;
}

int main()
{
    int a = 0;
    cin >> a;
    ofstream fout("fibm.txt");
    int arr[a];
    int ar = fib(arr, a);
    for (int i = 0; i < a; i++)
    {
        fout << i + 1 << ' ' << arr[i] << endl;
    }
    fout.close();
    return 0;
}