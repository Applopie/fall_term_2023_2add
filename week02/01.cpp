#include <iostream>

using namespace std;

class Vec3d
{
public:
    double x, y, z;

    Vec3d(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_) {}

    Vec3d() : x(0), y(0), z(0) {}

    ~Vec3d()
    {
        cerr << "Vec3d destructor\n";
    }

    double Lenght()
    {
        return sqrt(x * x + y * y + z * z);
    }
};

int main()
{
}