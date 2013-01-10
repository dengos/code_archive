/**
 * ===========================================================================
 *
 *          @file  Point.cc
 *         @brief  
 *
 *        @author  dengos (w), dengos.w@gmail.com, scut
 *       @version  1.0
 *          @date  01/10/2013 04:18:21 PM
 *
 * ===========================================================================
 */


#include <cmath>
#include <algorithm>


using std::max;


struct Point 
{
    double x;
    double y;
    inline Point(): x(0.0), y(0.0) {}
    inline Point(double dx, double dy): x(dx), y(dy) {}
    inline Point(const Point &other): x(other.x), y(other.y) {}

    inline Point &operator+=(const Point &other)
    {
        x += other.x;  y += other.y;
        return *this;
    }

    inline Point &operator-=(const Point &other)
    {
        x -= other.x;  y -= other.y;
        return *this;
    }
};				/* ----------  end of struct Point  ------ */


inline Point 
operator+(const Point &a, const Point &b)
{
    Point ret(a);
    return ret += b;
}

inline Point 
operator-(const Point &a, const Point &b)
{
    Point ret(a);
    return ret -= b;
}


inline double 
dist2(const Point &a, const Point &b)
{
    return (a.x - b.x) * (a.x - b.x) 
             + (a.y - b.y) * (a.y - b.y);
}

inline double
dist(const Point &a, const Point &b)
{
    return sqrt(dist2(a, b));
}

inline double
dot(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

inline double
cross(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}


inline Point
rotate_ccw(const Point &a, double sin_theta, double cos_theta)
{
    return Point(a.x * cos_theta - a.y * sin_theta, 
            a.x * sin_theta + a.y * cos_theta);
}


