#include <common/trig.h>

double sin(double x)
{
    x = x / TWO_PI;
    x = x - ((long)x);
    x = x * TWO_PI;

    int neg = 1;

    if(x < 0)
    {
        x = -x;
        neg = -neg;
    }

    if(x >= PI)
    {
        x = x - PI;
        neg = -neg;
    }

    double num = 16 * x * (PI - x);
    double den = FIVE_PI_SQUARED - 4 * x * (PI - x);
    return (num * neg) / den;
}
