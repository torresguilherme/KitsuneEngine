#include "math.hpp"

inline double deg2rad(double degrees)
{
	return degrees * (M_PI / 180.0);
}

inline double rad2deg(double radians)
{
	return radians * (180.0 / M_PI);
}

// VEC2

Vec2::Vec2(double x, double y)
{
	this->x = x;
	this->y = y;
}

double Vec2::lenght()
{
	return sqrt(x * x + y * y);
}

Vec2 Vec2::normalize()
{
	return Vec2(x/lenght(), y/lenght());
}

double Vec2::distanceTo(Vec2& other)
{
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

Vec2 Vec2::rotate(double degrees)
{
	double rad = deg2rad(degrees);
	double aCos = cos(rad);
	double aSin = sin(rad);
	return Vec2((x * aCos - y * aSin), (x * aSin * y * aCos));
}

Vec2 operator+(const Vec2& a, const Vec2& b)
{
	return Vec2(a.x + b.x, a.y + b.y);
}

Vec2 operator-(const Vec2& a, const Vec2& b)
{
	return Vec2(a.x - b.x, a.y - b.y);
}

Vec2 operator*(const Vec2& a, const double real)
{
	return Vec2(a.x * real, a.y * real);
}

Vec2 operator/(const Vec2& a, const double real)
{
	return Vec2(a.x / real, a.y / real);
}

double operator*(const Vec2& a, const Vec2& b)
{
	return (a.x * b.x) + (a.y * b.y);
}

// VEC3

Vec3::Vec3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double Vec3::lenght()
{
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalize()
{
	return Vec3(x/lenght(), y/lenght(), z/lenght());
}

double Vec3::distanceTo(Vec3& other)
{
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

Vec3 Vec3::cross(Vec3& other)
{
	double x_ = y * other.z - z * other.y;
	double y_ = z * other.x - x * other.z;
	double z_ = x * other.y - y * other.x;
	return Vec3(x_, y_, z_);
}

Vec3 operator+(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& a, const double real)
{
	return Vec3(a.x * real, a.y * real, a.z * real);
}

Vec3 operator/(const Vec3& a, const double real)
{
	return Vec3(a.x / real, a.y / real, a.z / real);
}

// MAT4

double operator*(const Vec3& a, const Vec3& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

double const* Mat4::operator[](int const in) const
{
	return &m[0][in];
}

double* Mat4::operator[](int const in)
{
	return &m[0][in];
}

void makeIdentity(Mat4& matrix)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(i == j)
			{
				matrix[i][j] = 1;
			}

			else
			{
				matrix[i][j] = 0;
			}
		}
	}
}

// to do: matrix operators

// QUATERNION

Quaternion::Quaternion(double x, double y, double z, double w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

double Quaternion::lenght()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalize()
{
	return Quaternion(x/lenght(), y/lenght(), z/lenght(), w/lenght());
}

Quaternion Quaternion::conjugate()
{
	return Quaternion(-x, -y, -z, w);
}

// to do: quaternion operators
