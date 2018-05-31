/* This program allows for the raytracing the cerenkov light from particles
transvering the detector, including reflecting off the mirror and hitting or
missing the PMTS. The position and direction of the particles are determined
from the input of the first and second order TRANSPORT matrices. The program
generates a topdrawer file of the particle trajectories and light paths, called
'RAYTR.TOP'.	*/




// #include <stdio.h>
// #include <float.h>
// #include <math.h>

#define FIRST  1
#define SECOND 2

/* gh 
#define MAX_X_SIZE 8.5
#define MAX_Y_SIZE 5.0
*/




#include "raytr.h"

#define MAX_X_SIZE 7.5
#define MAX_Y_SIZE 7.5

// #define PI 3.14159
// #define PMT_SIZE 20.00

#define sqr(x)  ((x)*(x))
#define rnd()   ((float)rand()/2147483648.0)
 
// typedef  struct
// {
//   /*    double Cx,Cy,R,L,Mx,My,Fx,Fy,phi; */
//   double Cx,Cy,R,L,Mx,My,Fx,Fy,phi,X1x,X1y,X2x,X2y;
// } MIRROR;
// 
// typedef struct
// {
//     double x,y,theta;
// }  RAY;
// 
// 
// typedef struct
// {
// 	double sum,sumsqr,min,max;
// 	double avg,sd,n;
// 	double angle,s;
// } STATS;

// extern int using_x_direction;
// 


// /* float x1,y1,x2,y2,rr;*/

int ray_number = 0, num_caught=0;

float x1,yy1,x2,y2,rr;

//void set_main_mirror(&m1,out);


using namespace std;

int main()
{


	
 	double top,bottom,left,right;
 	double phi,theta,dtheta,theta_m,x,y,dx,dy,y_x;
 	double lx,ly,ll,psi,zeta,s,ll_pr,size;
 	float t,b,l,r;
 	int nmirror,hit,cycle,i,npmt=0;


	TCanvas* c1 = new TCanvas("c1", "c1", 600, 800);

 	MIRROR m1,m2;
 	RAY    r1;
 	STATS  s1,s2;
 	FILE *out,*eff1,*eff2,*tmp1,*tmp2;
	
    top=10.0;
    left=0.0;   
	right=10.0;
    bottom=0.0;

	cout << "/*--------------------------------------------------*/" << endl;

  
	do
		{
		printf("Number of mirrors in the detector (1 or 2):  ");
		scanf("%d",&nmirror);
		}
 	while( (nmirror != 1) && (nmirror != 2) );

	cout <<  nmirror << endl;

 	printf("Please enter bottom,top:  ");
 	scanf("%f,%f",&b,&t);
 	printf("             left,right:  ");
 	scanf("%f,%f",&l,&r);
 	top = t;    bottom = b;
	left = l;   right = r;


	cout << t << "  " << b << "  " << "  " << l << "  " << r << endl;
 	
 	

 /** this puts a grid over the topdrawer file
 	dx = (right-left)/10.0;
 	for(x=left+dx; x < right; x += dx)
 	   fprintf(out,"%f %f\n %f %f\njoin dots\n",x,top,x,bottom);
 	dy = (top-bottom)/10.0;
 	for(y=bottom+dy; y < top; y += dy)
 	   fprintf(out,"%f %f\n %f %f\njoin dots\n",left,y,right,y);
 **/



	printf("Mirror One:\n");
	set_main_mirror(&m1);




	if( nmirror == 2 )
		{
		printf("Mirror Two:\n");
		set_main_mirror(&m2);
		}

	npmt = nmirror;

	printf("Move PMT(s) (1=yes)?  ");
	scanf("%d",&i);



	if( i )
		{
		printf("PMT 1:  Focal point:  % 6.1f,% 6.1f, phi:  % 61.f deg\n",
					m1.Fx,m1.Fy,m1.phi*90.0/asin(1.0) );
		printf("New Focal point:  ");
		scanf("%lf,%lf", &(m1.Fx), &(m1.Fy));
		printf("New theta (deg):  ");
		scanf("%lf", &(m1.phi) );

		m1.phi *= asin(1.0)/90.0;

        if( nmirror == 2 )
			{
			printf("Use second PMT (1=yes)?  ");
			scanf("%d",&i);
			if( i != 1 )
				npmt = 1;
			}
	
		if( npmt == 2 )
			{
			printf("PMT 2:  Focal point:  % 6.1f,% 6.1f, phi:  % 61.f deg\n",
					m2.Fx,m2.Fy,m2.phi*90.0/asin(1.0) );
			printf("New Focal point:  ");
			scanf("%lf,%lf",&(m2.Fx),&(m2.Fy) );
	       		printf("New theta (deg):  ");
			scanf("%lf",&(m2.phi) );
	       		m2.phi *= asin(1.0)/90.0;
			}
		}

	
/*	eff1 = fopen("eff1.dat","a");  
	if( eff1 == NULL )
		{
		printf("error openning data file.\n");	
		exit(1);
		}
*/	

	eff2 = fopen("raytr_eff.dat","a");  

	if( eff2 == NULL ) {
		printf("error opening data file.\n");	
		exit(1);
	}







	cout << endl << "End of the test "<< endl;

	cout <<  nmirror << endl;
	cout <<  nmirror << endl;
	cout <<  nmirror << endl;









//	for(cycle=FIRST; cycle <= SECOND; cycle += 1)


	for(cycle=FIRST; cycle <= FIRST; cycle += 1) {	
		s1.sum = s1.sumsqr = s1.min = s1.max = s1.n = 0.0;
		s2.sum = s2.sumsqr = s2.min = s2.max = s2.n = 0.0;
	

		cout << "asdasd " << endl;

		cout <<  nmirror << endl;

//		exit(0);




/* set up the topdrawer file */
/* size of data window suchthat height/width ratio is correct */
		y_x = (top-bottom)/(right-left);
		if( y_x < (MAX_Y_SIZE/MAX_X_SIZE) )
			{
			x = MAX_X_SIZE;
			y = y_x*x;
			}
		else
			{
		   	y = MAX_Y_SIZE;
		   	x = (1.0/y_x)*y;
		   	}

		out = fopen("test_test_test_test.txt","w");

		fprintf(out,"set dev post color sideways\n");
		fprintf(out,"new plot\n");
		fprintf(out,"set font duplex\n");
		fprintf(out,"set card length 150\n");
/* gh
		fprintf(out,"set window x %f 9.0 y %f 8.0\n",9.0-x,8.0-y);
*/
		fprintf(out,"set window x %f 7.5 y %f 9.8\n",7.5-x,9.8-y);
		fprintf(out,"set limits x %f %f y %f %f\n",left,right,bottom,top);
		/* gh
		fprintf(out,"title 0.5 %f size 1.25 'Mirror One:'\n",7.0-y);
		*/
		fprintf(out,"title 0.5 %f size 1.25 'Mirror One:'\n",9.0-y);






		cout << "1st corner " << m1.X1x << "   " << m1.X1y << "   " << double(m1.phi) << "     " << asin(1.0)/90.0<< endl;

 		draw_mirror(&m1, c1);

// 		draw_mirror();

// 
// 		if( nmirror == 2 ) {
// 		  	fprintf(out,"title 'Mirror Two:'\n");
// 		  	draw_mirror(&m2,out);
// 		}
// 


/* we will what to run this part twice so that we can reposition the PMTs to
where the focal spot actually is, not where it was calculated to be */		
		if( cycle == SECOND ) {

			cout << " cycle == Second? " << endl;
			reset_get_ray();
		}
       		num_caught=0;

/* the functions in the conditionals return TRUE such that the way they are
read make sense, i.e. while there is another ray to get... */

		Int_t i = 0;

		while( get_next_ray(&r1, left, right) ) {

//			cout << i++ << endl;
//			cout << "While loop ~~~~ " << endl; 

		   	hit = 0;

 		   	if( intersect_main_mirror(&m1, &r1, c1) ) {

// 
// 


				
				flat_reflect(&m1, &r1, c1);

 				hit = hit_PMT(&m1, &r1, &s1, c1);

//		      	follow_ray_out(&r1, c1, left, right, top, bottom);


 		    }                       

// else if( nmirror==2 ) {
// 
// 				if( intersect_main_mirror(&m2,&r1,out) ) {
// 
// 					if( npmt == 2 ) {
// 		         		hit = hit_PMT(&m2,&r1,out,&s2);
// 					}
// 		        }
// 			}


//		   	if( hit == 0 )
//		      		follow_ray_out(&r1,out,left,right,top,bottom);
///*			fprintf(eff1,"% f   % f\n",s1.s,s1.angle);	*/

	    }



	    cout << "While loop ouit ~~~~ " << endl; 



//		s1.avg = s1.sum/s1.n;
//		s1.sd = sqrt( s1.sumsqr/s1.n - s1.avg*s1.avg );
//		if( npmt == 2 )
//			{
//			s2.avg = s2.sum/s2.n;
//			s2.sd = sqrt( s2.sumsqr/s2.n - s2.avg*s2.avg );
//			}
//	        
//		fprintf(out,"title 'in:  %d,  caught:  %d, eff:  %3.2f%%,",
//		  	ray_number,num_caught,
//			((float)num_caught)/((float)ray_number)*100.0 );
//		if( npmt == 2 )
//		  {
//			fprintf(out,"  spot sizes:  %3.2f%%, %3.2f%%'\n",
//				fabs(s1.max - s1.min)/	PMT_SIZE*50.0,
//				fabs(s2.max - s2.min)/PMT_SIZE*50.0);
//





///* gh: output results */
//		    if( cycle==FIRST )
//		       {
//		        fprintf(eff2," %3.0f %3.0f %3.0f %3.0f %3.0f ",
//				m1.R,m1.X1x,m1.X2x,m2.X1x,m2.X2x);
//
//		        fprintf(eff2," %3.0f %4.0f %3.0f  %3.0f %4.0f %3.0f ",
//				m1.Fx,m1.Fy,m1.phi*57.295,m2.Fx,m2.Fy,m2.phi*57.295);
//                       }
//		  }
//		else
//			fprintf(out,"  spot size:  %3.2f%%'\n",
//				fabs(s1.max - s1.min)/PMT_SIZE*50.0);
//		fprintf(out,"title bottom 'Z (cm)'\n");
//		if( using_x_direction )
//		   fprintf(out,"title left   'X (cm)'\n");
//		else
//		   fprintf(out,"title left   'Y (cm)'\n");
//		fclose( out );
//		if( npmt == 2)
//		  {
//			printf("in:  %d,  caught:  %d, eff:  %3.2f%%,  spot sizes:  %3.2f%%  %3.2f%%\n",
//		   		ray_number,
//				num_caught,
//				((float)num_caught)/((float)ray_number)*100.0,
//				fabs(s1.max - s1.min)/PMT_SIZE*50.0,
//				fabs(s2.max - s2.min)/PMT_SIZE*50.0);
///* gh: output results */
//		    if( cycle==SECOND )
//		       {
//		        fprintf(eff2," %3.1f %4.1f %3.0f  %3.1f %4.1f %3.0f ",
//				m1.Fx,m1.Fy,m1.phi*57.295,m2.Fx,m2.Fy,m2.phi*57.295);
//
//		        fprintf(eff2," %3.2f %3.2f %3.2f ",
//			  ((float)num_caught)/((float)ray_number)*100.0 ,  /* eff   */
//			  fabs(s1.max - s1.min)/PMT_SIZE*50.0,             /* spot1 */
//			  fabs(s2.max - s2.min)/PMT_SIZE*50.0);            /* spot2 */
//                       }
//		  }
//		else
//			printf("in:  %d,  caught:  %d, eff:  %3.2f%%,  spot size:  %3.2f%%\n",
//		   		ray_number,
//				num_caught,
//				((float)num_caught)/((float)ray_number)*100.0,
//				fabs(s1.max - s1.min)/PMT_SIZE*50.0);
//
///*		fprintf(eff1,"%6.2f  %6.2f  %6.2f  ",m1.Fx,m1.Fy,
//			((float)num_caught)/((float)ray_number)*100.0); */
//		if( npmt == 2 )
//			size = 0.5*( fabs(s1.max - s1.min)/PMT_SIZE*50.0
//				 +   fabs(s2.max - s2.min)/PMT_SIZE*50.0 );
//		else
//			size = fabs(s1.max - s1.min)/PMT_SIZE*50.0;
///*		fprintf(eff1,"%6.2f  ",size); */
//




///*--------------------------------------------------*/
///*--------------------------------------------------*/
///*--------------------------------------------------*/
//		printf("Reposition focal point (1=yes)?  ");
//		scanf("%d",&i);
//		if( i != 1 )
//	               	cycle = SECOND;
//		if( cycle == FIRST )
//			{
//			reposition_fpoint(&m1,&s1);
//			if( npmt == 2 )
//				reposition_fpoint(&m2,&s2);
//			}
///*--------------------------------------------------*/
///*--------------------------------------------------*/

		}

	c1->Print("mirror.eps");


	
/*	fprintf(eff1,"\n"); */
	fprintf(eff2,"\n"); 

/* gh - write focal point y positions to tmp files for batch script use */
	tmp1 = fopen("tmp1.dat","w");
	fprintf(tmp1," %4.0f \n",m1.Fy);
	tmp2 = fopen("tmp2.dat","w");
	fprintf(tmp2," %4.0f \n",m2.Fy);

}

                                                           
