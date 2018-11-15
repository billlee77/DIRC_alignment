#ifndef RAYTR_H
#define RAYTR_H

#include <iostream>

#include <stdio.h>
#include <float.h>
#include <math.h>



#include "TCanvas.h"
#include "TGraph.h"
#include "TText.h"
#include "TAxis.h"


#define TRUE  1
#define FALSE 0

#define PI 3.14159
#define PMT_SIZE 10

#define _X      0
#define _THETA  1
#define _Y      2
#define _PHI    3
#define _Z      4
#define _DELTA  5


#define sqr(x)  ((x)*(x))
#define rnd()   ((float)rand()/2147483648.0)


struct MIRROR {
  /*    double Cx,Cy,R,L,Mx,My,Fx,Fy,phi; */
  double Cx,Cy,R,L,Mx,My,Fx,Fy,phi,X1x,X1y,X2x,X2y;
};

struct RAY{
    double x,y,theta;
};

struct STATS{
	double sum,sumsqr,min,max;
	double avg,sd,n;
	double angle,s;
};



typedef struct {

	double x_pos, y_pos;
	double angle, width;

}MIRROR_DIM;



struct COMP_MIRR {

	Double_t mirror_sub_1_x, mirror_sub_1_y, mirror_sub_1_angle; 
	Double_t mirror_sub_2_x, mirror_sub_2_y, mirror_sub_2_angle; 
	Double_t mirror_sub_3_x, mirror_sub_3_y, mirror_sub_3_angle; 
	Double_t mirror_width;

} ;


// int ray_number,num_caught;


/*extern float x1,y1,x2,y2,rr; */
//extern float x1,yy1,x2,y2,rr; 


class mirror_stats {

	public:

		MIRROR_DIM* flat_mirror_dim;
		COMP_MIRR* composite_mirror_dim;
		MIRROR_DIM* window_dim;
		MIRROR_DIM* pmt_window_dim;
		MIRROR_DIM* side_reflector_dim;
		MIRROR_DIM* side_honrizontal_mirror_dim;


};



typedef struct {

	Double_t mis_x, mis_y; 
	Double_t rot_center_x, rot_center_y;
	Double_t rot_angle;

} MIRROR_Miss;





void set_main_mirror(MIRROR*);
void draw_mirror(mirror_stats*, TCanvas*);

//void mirror_box_misalignment(MIRROR*, MIRROR_Miss*);
Double_t mirror_box_misalignment_x(Double_t, Double_t, MIRROR_Miss*);
Double_t mirror_box_misalignment_y(Double_t, Double_t, MIRROR_Miss*);





int get_next_ray(RAY*, float, float);
void reset_get_ray();
void get_ray_setup();

int intersect_main_mirror( MIRROR*, RAY*, TCanvas*);

int flat_reflect(mirror_stats*, RAY*, TCanvas*);

bool fitting_mirror(Double_t, Double_t, Double_t, Double_t, RAY*);
bool fitting_mirror_flat_mirror(Double_t, Double_t, Double_t, Double_t, RAY*);

void composite_mirror_reflect(Double_t, Double_t, Double_t, RAY*);
void composite_mirror_reflect_mod(Double_t, Double_t, Double_t, RAY*);

void side_mirror_reflect(Double_t, Double_t, Double_t, RAY*);

int hit_PMT(MIRROR*, RAY*, STATS*, TCanvas* c1);

void follow_ray_out(RAY*, TCanvas*, double, double, double, double);

//extern const Double_t window_corner_x, window_corner_y;
extern Double_t reference_x;
extern Double_t reference_y;

extern Double_t global_offset_x;
extern Double_t global_offset_y;

void long_flat_mirror_reflect(Double_t, Double_t, Double_t, RAY*);
void side_flat_mirror_reflect(Double_t, Double_t, Double_t, RAY*);


// 
// 
// Double_t SetWin_x(Double_t x) { window_corner_x = x;}
// Double_t SetWin_y(Double_t y) { window_corner_x = y;}

// Double_t PMT_SIZE = 10;

#endif
