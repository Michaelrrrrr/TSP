#pragma once
class Points
{
private:
	double x, y, z;

public:
	Points() : x(0), y(0), z(0) {}
	Points(double x1, double y1, double z1) : x(x1), y(y1), z(z1) {}

	void setPoint(double x1, double y1, double z1) { x = x1; y = y1; z = z1; }
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }

};