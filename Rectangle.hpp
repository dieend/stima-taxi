#pragma once

class	 Rectangle {
    double x;				     // coordinates
    double y;
public:
    Rectangle()			     { x = 0.0; y = 0.0;	      }
    Rectangle(double x0, double y0, double width, double height)     { x = x0; y = y0;		      }
    void     operator=(const Rectangle& a)   { x = a.x; y = a.y;	      }
    void     operator+=(const Rectangle& a)   { x += a.x; y += a.y;	      }
    void     operator/=(double d)    { if (d != 0.0) {x /= d; y /= d;}}
    void     operator*=(double d)    { x *= d; y *= d;		      }
    double	  Width()		     { return x;		      }
    double	  Height()		     { return y;		      }
    double     Size();

// FRIENDS
    friend Rectangle operator+(const Rectangle&, const Rectangle&);
    friend Rectangle operator-(const Rectangle&, const Rectangle&);
    friend Rectangle operator-(const Rectangle&);
    friend Rectangle operator*(const Rectangle&, double);
    friend Rectangle operator*(double, const Rectangle&);
};
