#include "raytr.h"


int get_next_ray(r,out,left,right)
RAY *r;
FILE *out;
double left,right;
{
    float theta,y;

    ray_number++;
    switch( ray_number )
      {
      case 1:
        theta = 0.46*PI;
        y = 10.0;
        break;
      case 2:
        theta = 0.5*PI;
        y = 0.0;
        break;
      case 3:
        theta = 0.54*PI;
        y = -10.0;
        break;
      default:
        return( 0 );
      }
    r->x = left;
    r->y = y;
    r->theta = theta;
    fprintf(out,"%f %f\n%f %f\njoin\n",
                  left,y,right,y-tan(theta-0.5*PI)*(right-left));
    return( 1 );
}

