#include <stdio.h>
#include <math.h>

/* this program is for generating a .com file to calculate the
	tolerances of the positions of the mirrors and PMTs in the
	cerenkov detector. The .com uses RAYTR.EXE.		*/


main()
{
 	float delta,ddelta,mindelta,maxdelta,ndelta;
	float phi1,phi2,delta_rad,x1x,x1y,x2x,x2y;
	FILE *out1,*out2;

	/* want to rotate the mirrors about the point 135,0    */
/*
	phi1 =  13.48/90.0*asin(1.0);
	phi2 = -22.05/90.0*asin(1.0);
	printf("Varying mirror rotation,\n");
	printf("Enter min,max delta (deg) and number of sample points:  ");
	scanf("%f,%f,%f",&mindelta,&maxdelta,&ndelta);
	ddelta = (maxdelta-mindelta)/(ndelta-1.);
	out1 = fopen("toler.com","w");
	out2 = fopen("toler.dat","w");
	fprintf(out1,"$del eff1.dat;*\n");
	for(delta = mindelta; delta <= maxdelta; delta += ddelta)
		{
		delta_rad = delta/90.0*asin(1.0);  
		x1x = 135.0 + 30.0*sin(phi1 + delta_rad);
		x1y = 30.0*cos(phi1 + delta_rad);
		x2x = 135.0 + 30.0*sin(phi2 - delta_rad);
		x2y = -30.0*cos(phi2 - delta_rad);
		fprintf(out1,"$run raytr\n");
		fprintf(out1,"1\n-40,60\n0,150\n");
		fprintf(out1,"%f,%f\n%f,%f\n120\n2\n",x1x,x1y,x2x,x2y);
		fprintf(out1,"1\n91.3,35\n215\n");
		fprintf(out1,"hms2.dat\n24\n2\n22,9\n5,9\n");
		fprintf(out1,"0\n");
		fprintf(out1,"$del raytr.top;*\n");
		fprintf(out2,"%f\n",delta + 17.77);
		}
*/

	/* want to vary the y position of the PMT */
/*
	printf("Varying PMT y position,\n");
	printf("Enter min,max delta (cm) and number of sample points:  ");
	scanf("%f,%f,%f",&mindelta,&maxdelta,&ndelta);
	ddelta = (maxdelta-mindelta)/(ndelta-1.);
	out1 = fopen("toler.com","w");
	out2 = fopen("toler.dat","w");
	fprintf(out1,"$del eff1.dat;*\n");
	for(delta = mindelta; delta <= maxdelta; delta += ddelta)
		{
		fprintf(out1,"$run raytr\n");
		fprintf(out1,"1\n-40,60\n0,150\n");
		fprintf(out1,"142.0,29.2\n123.7,-27.9\n120\n2\n");
		fprintf(out1,"1\n%f,35\n215\n",91.3+delta);
		fprintf(out1,"hms2.dat\n24\n2\n22,9\n5,9\n");
		fprintf(out1,"0\n");
		fprintf(out1,"$del raytr.top;*\n");
		fprintf(out2,"%f\n",delta + 91.3);
		}
*/

	printf("Varying PMT x position,\n");
	printf("Enter min,max delta (cm) and number of sample points:  ");
	scanf("%f,%f,%f",&mindelta,&maxdelta,&ndelta);
	ddelta = (maxdelta-mindelta)/(ndelta-1.);
	out1 = fopen("toler.com","w");
	out2 = fopen("toler.dat","w");
	fprintf(out1,"$del eff1.dat;*\n");
	for(delta = mindelta; delta <= maxdelta; delta += ddelta)
		{
		fprintf(out1,"$run raytr\n");
		fprintf(out1,"2\n-60,60\n0,150\n");
		fprintf(out1,"136.6,56\n136.6,0\n120\n2\n");
		fprintf(out1,"136.6,-56\n136.6,0\n120\n1\n");
		fprintf(out1,"1\n79.9,%f\n0.0\n",28.0+delta);
		fprintf(out1,"1\n79.9,-28.0\n180.0\n");
		fprintf(out1,"hms2.dat\n24\n1\n82.5,9\n5,9\n");
		fprintf(out1,"0\n");
		fprintf(out1,"$del raytr.top;*\n");
		fprintf(out2,"%f\n",delta + 28);
		}
}
