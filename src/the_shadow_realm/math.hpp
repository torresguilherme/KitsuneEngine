#ifndef MATH_HPP_
#define MATH_HPP_
#include <cmath>

inline double deg2rad(double);
inline double rad2deg(double);

class Vec2
{
	public:
	float x;
	float y;

	Vec2(float, float);
	float lenght();
	Vec2 normalize();
	float distanceTo(Vec2&);
	Vec2 rotate(float);
};

Vec2 operator+(const Vec2& a, const Vec2& b);
Vec2 operator-(const Vec2& a, const Vec2& b);
Vec2 operator*(const Vec2& a, const float real);
Vec2 operator/(const Vec2& a, const float real);
float operator*(const Vec2& a, const Vec2& b);

class Mat4
{
	public:
	static const int SIZE = 4;

	private:
	float m[SIZE][SIZE];

	public:
	float const* operator[](int const) const;
	float* operator[](int const);
};	

class Vec3
{
	public:
	float x;
	float y;
	float z;

	Vec3(float, float, float);
	float lenght();
	Vec3 normalize();
	float distanceTo(Vec3&);
	Vec3 cross(Vec3&);
	
	// transform operations
	Vec3 translate(Mat4& translation);
	Vec3 scale(Mat4& scale);
	Vec3 rotateX(Mat4& rot);
	Vec3 rotateY(Mat4& rot);
	Vec3 rotateZ(Mat4& rot);
};

Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& a, const float real);
Vec3 operator/(const Vec3& a, const float real);
float operator*(const Vec3& a, const Vec3& b);

void makeIdentity(Mat4&);
Mat4 operator*(const Mat4& a, const Mat4& b);

class Quaternion
{
	public:
	float x;
	float y;
	float z;
	float w;

	Quaternion(float, float, float, float);
	float lenght();
	Quaternion normalize();
	Quaternion conjugate();
};

Quaternion operator*(const Quaternion&, const Vec3&);
Quaternion operator*(const Quaternion&, const Quaternion&);

#endif
