#include <math.h>
#define pi 3.1415926535
#define R 6371000

float get_distance(float longtitude1, float latitude1, float longtitude2, float latitude2){
    longtitude1 *= (pi/180);
    latitude1 *= (pi/180);
    longtitude2 *= (pi/180);
    latitude2 *= (pi/180);

    float d_long = (longtitude2 - longtitude1);
    float d_latit = (latitude2 - latitude1);

    float a  = sin(d_latit/2)*sin(d_latit/2) + cos(latitude1) * cos(latitude2) * sin(d_long/2) * sin(d_long/2);
    float c = 2* atan2(sqrt(a), sqrt(1-a));
    float d = R*c;
    return d;

}
