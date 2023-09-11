#include <iostream>
#include <fstream>

using namespace std;

int main(int a, char **argv)
{
    a = 15;
    ofstream fout("numbers.txt");
    for (int i = 0; i < a; i++)
    {
        fout << i + 1 << ' ';
    }
    fout << endl;
    fout.close();
    return 0;
}