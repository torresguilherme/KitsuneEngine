#ifndef MATH_HPP_
#define MATH_HPP_
#include <cmath>

inline double deg2rad(double);
inline double rad2deg(double);

class Vec2
{
	public:
	double x;
	double y;

	Vec2(double, double);
	double lenght();
	Vec2 normalize();
	double distanceTo(Vec2&);
	Vec2 rotate(double);
};

Vec2 operator+(const Vec2& a, const Vec2& b);
Vec2 operator-(const Vec2& a, const Vec2& b);
Vec2 operator*(const Vec2& a, const double real);
Vec2 operator/(const Vec2& a, const double real);
double operator*(const Vec2& a, const Vec2& b);

class Vec3
{
	public:
	double x;
	double y;
	double z;

	Vec3(double, double, double);
	double lenght();
	Vec3 normalize();
	double distanceTo(Vec3&);
	Vec3 cross(Vec3&);
};

Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& a, const double real);
Vec3 operator/(const Vec3& a, const double real);
double operator*(const Vec3& a, const Vec3& b);

class Mat4
{
	static const int SIZE = 4;
	double m[SIZE][SIZE];

	public:
	double const* operator[](int const) const;
	double* operator[](int const);
};	

void makeIdentity(Mat4&);
Mat4 operator*(const Mat4& a, const Mat4& b);

class Quaternion
{
	public:
	double x;
	double y;
	double z;
	double w;

	Quaternion(double, double, double, double);
	double lenght();
	Quaternion normalize();
	Quaternion conjugate();
};

Quaternion operator*(const Quaternion&, const Vec3&);
Quaternion operator*(const Quaternion&, const Quaternion&);

#endif
