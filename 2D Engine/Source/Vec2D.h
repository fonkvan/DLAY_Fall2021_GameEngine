#pragma once

struct Vec2D
{
	double x;
	double y;
	//Calculate the vector product of two vectors
	double DotProduct(Vec2D u){ return (u.x * x) + (u.y * y); }
	//Calculate the magnitude, ie length, of this vector
	double Magnitude(){ return sqrt(x*x + y*y); }
	//Get the normal vector on the straight line segment between 2 points (which is the same as 2 vectors)
	Vec2D GetNormal(Vec2D u)
	{
		double dx = u.x - x;
		double dy = u.y - y;
		return Vec2D{-dy, dx};
	}
	//Normalize a vector such that direction is still the same, but magnitude is 1
	void Normalize() 
	{
		double Mag = Magnitude();
		x = x/Mag;
		y = y/Mag;
	}
};