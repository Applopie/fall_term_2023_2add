#include <fstream>

using namespace std;

int main()
{
    ofstream fout("nubers.txt");
    for (int i = 0; i < 30; i++)
    {
        fout << i + 1 << ' ';
    }
    fout << endl;
    fout.close();
    return 0;
}