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
Point& operator+(const Point& a, const Point& b)
{
	return *new Point(a.x + b.x, a.y + b.y);
}

/*--------------- Overloaded binary - operator	----------------*/
/* Subtract two Points						*/
/* IN  : reference of the two operands				*/
/* OUT : result Point						*/
/*--------------------------------------------------------------*/
Point& operator-(const Point& a,const Point& b)
{
	return *new Point(a.x - b.x,a.y - b.y);
}

/*-------------- Overloaded unary - operator -------------------*/
/* Negates a Point						*/
/* IN  : operand						*/
/* OUT : negated Point						*/
/*--------------------------------------------------------------*/
Point& operator-(const Point& a)
{
	return *new Point(-a.x,-a.y);
}

/*------------------ Overloaded * operator  --------------------*/
/* Multiplies a Point with a scalar				*/
/* IN  : Point and scalar operand				*/
/* OUT : result Point						*/
/*--------------------------------------------------------------*/
Point& operator*(const Point& a, double s)
{
	return *new Point(s * a.x,s * a.y);
}

Point& operator*(double s,const Point& a)
{
	return *new Point(s * a.x,s * a.y);
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
