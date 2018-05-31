#ifndef RAYTR_H
#define RAYTR_H

#include <iostream>

#include <stdio.h>
#include <float.h>
#include <math.h>



#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"


#define TRUE  1
#define FALSE 0

#define PI 3.14159

#define _X      0
#define _THETA  1
#define _Y      2
#define _PHI    3
#define _Z      4
#define _DELTA  5

#define PMT_SIZE 10.00

#define sqr(x)  ((x)*(x))
#define rnd()   ((float)rand()/2147483648.0)


typedef struct
{
  /*    double Cx,Cy,R,L,Mx,My,Fx,Fy,phi; */
  double Cx,Cy,R,L,Mx,My,Fx,Fy,phi,X1x,X1y,X2x,X2y;
} MIRROR;

typedef struct
{
    double x,y,theta;
} RAY;

typedef struct
{
	double sum,sumsqr,min,max;
	double avg,sd,n;
	double angle,s;

} STATS;

// int ray_number,num_caught;


/*extern float x1,y1,x2,y2,rr; */
//extern float x1,yy1,x2,y2,rr; 


void set_main_mirror(MIRROR*);
void draw_mirror(MIRROR*, TCanvas*);



int get_next_ray(RAY*, float, float);
void reset_get_ray();
void get_ray_setup();

int intersect_main_mirror( MIRROR*, RAY*, TCanvas*);

int flat_reflect(MIRROR*, RAY*, TCanvas*);

int hit_PMT(MIRROR*, RAY*, STATS*, TCanvas* c1);

void follow_ray_out(RAY*, TCanvas*, double, double, double, double);




#endif
