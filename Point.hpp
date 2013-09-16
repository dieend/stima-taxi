/****************************************************************************
**    TEST FILE FOR graph (Dynamic Layout Alg)
**
**    HEADER   - 2D Point OPERATIONS
**
** Author: dr. Szirmay-Kalos Laszlo (szirmay@fsz.bme.hu)
**	   Technical University of Budapest, Hungary
*****************************************************************************/
/*
*    Point - 2D GEOMETRIC Point TYPE
*/
class	 Point {
    double x;				     // coordinates
    double y;
public:
    Point()			     { x = 0.0; y = 0.0;	      }
    Point(double x0, double y0)     { x = x0; y = y0;		      }
    void     operator=(const Point& a)   { x = a.x; y = a.y;	      }
    void     operator+=(const Point& a)   { x += a.x; y += a.y;	      }
    void     operator/=(double d)    { if (d != 0.0) {x /= d; y /= d;}}
    void     operator*=(double d)    { x *= d; y *= d;		      }
    double	  X()		     { return x;		      }
    double	  Y()		     { return y;		      }
    double     Size();

// FRIENDS
    friend Point operator+(const Point&, const Point&);
    friend Point operator-(const Point&, const Point&);
    friend Point operator-(const Point&);
    friend Point operator*(const Point&, double);
    friend Point operator*(double, const Point&);
};
