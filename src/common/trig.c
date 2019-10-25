#include <common/trig.h>

double sin(double x)
{
    if(x > TWO_PI)
    {
        x /= TWO_PI;
        x -= ((long)x);
        x *= TWO_PI;
    }

    int neg = 1;

    if(x < 0)
    {
        x = -x;
        neg = -neg;
    }

    if(x >= (1.5 * PI))
    {
        x = TWO_PI - x;
        neg = -neg;
    }
    else if(x >= PI)
    {
        x = x - PI;
        neg = -neg;
    }
    else if(x >= (0.5 * PI))
        x = PI - x;

    return (16 * x * (PI - x)) / (FIVE_PI_SQUARED - 4 * x * (PI - x)) * neg;
}
