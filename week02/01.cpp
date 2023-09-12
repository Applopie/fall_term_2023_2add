#include <iostream>
#include <cmath>

using namespace std;

class Vec3d
{
public:
    double x, y, z;

    Vec3d(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_) {}

    Vec3d() : x(0), y(0), z(0) {}

    Vec3d(const Vec3d &rhs)
        : x(rhs.x), y(rhs.y), z(rhs.z)
    {
        cerr << "Vec3d copy ctor\n";
    }

    Vec3d(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_)
    {
        cerr << "Vec3d 3-arg ctor\n";
    }

    Vec3d() : x(0), y(0), z(0)
    {
        cerr << "Vec3d default ctor\n";
    }

    ~Vec3d()
    {
        cerr << "Vec3d destructor\n";
    }

    double Lenght()
    {
        return sqrt(x * x + y * y + z * z);
    }

    Vec3d &operator+=(const Vec3d &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return (*this);
    }

    Vec3d &operator+(const Vec3d &a, const Vec3d &b)
    {
        return {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    ostream &operator<<(ostream &os, const Vec3d &v)
    {
        os << "Vec3d[" << v.x << ", " << v.y << ", " << v.z << "]\n";
        return os
    }
};

int main()
{
    Vec3d a = {3, 5, 7};
    std::cout << a << endl;
    return 0;
}