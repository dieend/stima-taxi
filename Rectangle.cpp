#include <cmath>
#include "Rectangle.hpp"

/*------------------------- Size -------------------------------*/
/* Calculates the absolute value of the Rectangle			*/
/* IN  : -							*/
/* OUT : length							*/
/*--------------------------------------------------------------*/
double Rectangle::Size()
{
	return sqrt( x * x + y * y );
}
