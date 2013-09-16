/*****************************************************************************
**    TEST FILE FOR graph (Dynamic Layout Alg)
**
**    MODUL   - 2D Point OPERATIONS
**
** Author: dr. Szirmay-Kalos Laszlo (szirmay@fsz.bme.hu)
**	   Technical University of Budapest, Hungary
*****************************************************************************/
#include <cmath>

#include "Point.hpp"

/*------------------ Overloaded + operator  --------------------*/
/* Adds two Points						*/
/* IN  : reference of the two operands				*/
/* OUT : result Point						*/
/*--------------------------------------------------------------*/
Point operator+(Point a, Point b)
{
	Point sum;
	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return sum;
}

/*--------------- Overloaded binary - operator	----------------*/
/* Subtract two Points						*/
/* IN  : reference of the two operands				*/
/* OUT : result Point						*/
/*--------------------------------------------------------------*/
Point operator-(Point a, Point b)
{
	Point dif;
	dif.x = a.x - b.x;
	dif.y = a.y - b.y;
	return dif;
}

/*-------------- Overloaded unary - operator -------------------*/
/* Negates a Point						*/
/* IN  : operand						*/
/* OUT : negated Point						*/
/*--------------------------------------------------------------*/
Point operator-(Point a)
{
	Point neg;
	neg.x = -a.x;
	neg.y = -a.y;
	return neg;
}

/*------------------ Overloaded * operator  --------------------*/
/* Multiplies a Point with a scalar				*/
/* IN  : Point and scalar operand				*/
/* OUT : result Point						*/
/*--------------------------------------------------------------*/
Point operator*(Point a, double s)
{
	Point scaled;
	scaled.x = s * a.x;
	scaled.y = s * a.y;
	return scaled;
}

Point operator*(double s, Point a)
{
	Point scaled;
	scaled.x = s * a.x;
	scaled.y = s * a.y;
	return scaled;
}

/*------------------------- Size -------------------------------*/
/* Calculates the absolute value of the Point			*/
/* IN  : -							*/
/* OUT : length							*/
/*--------------------------------------------------------------*/
double Point::Size()
{
	return sqrt( x * x + y * y );
}
