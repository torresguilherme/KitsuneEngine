#include "math.hpp"

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vec2::lenght()
{
	return sqrt(x * x + y * y);
}

Vec2 Vec2::normalize()
{
	Vec2 ret(x/lenght(), y/lenght());
	return ret;
}

float Vec2::distanceTo(Vec2& other)
{
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

Vec2 Vec2::rotate(float degrees)
{
	// to do
	Vec2 ret(0.0, 0.0);
	return ret;
}

// to do: operators

Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vec3::lenght()
{
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalize()
{
	Vec3 ret(x/lenght(), y/lenght(), z/lenght());
	return ret;
}

float Vec3::distanceTo(Vec3& other)
{
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

Vec3 Vec3::rotate(float degrees)
{
	// to do
	Vec3 ret(0.0, 0.0, 0.0);
	return ret;
}

// to do: operators

void makeIdentity(Mat4 matrix)
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

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Quaternion::lenght()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalize()
{
	Quaternion ret(x/lenght(), y/lenght(), z/lenght(), w/lenght());
	return ret;
}

Quaternion Quaternion::conjugate()
{
	Quaternion ret(-x, -y, -z, w);
	return ret;
}

// to do: quaternion operators
