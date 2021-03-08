#pragma once
class Ray;
class Wall;
class Vector3 {
private:
	// coordinates
	double _x;
	double _y;
	double _z;
public:
	Vector3(double x = 0, double y = 0, double z = 0);
	Vector3 operator+=(Vector3 otherVector3);
	Vector3 operator=(const Vector3 &otherVector3);
	bool operator!=(const Vector3& otherVector3);
	// read only easy access value of x, y, and z
	const double& x{ _x };
	const double& y{ _y };
	const double& z{ _z };
};

bool Vector3::operator!=(const Vector3& otherVector3) {
	return(_x == otherVector3._x && _y == otherVector3._y && _z == otherVector3._z);
}
Vector3::Vector3(double x, double y, double z) :
	_x{ x }, _y{ y }, _z{ z }
{}

Vector3 Vector3::operator+=(Vector3 otherVector3) {
	_x += otherVector3._x;
	_y += otherVector3._y;
	_z += otherVector3._z;
	return *this;
}

Vector3 Vector3::operator=(const Vector3 &otherVector3) {
	_x = otherVector3._x;
	_y = otherVector3._y;
	_z = otherVector3._z;
	return *this;
}

#include <cmath>
double GetDistance(Vector3 point1, Vector3 point2) {
	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2) + pow(point2.z - point1.z, 2));
}