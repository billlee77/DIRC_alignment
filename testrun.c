#include <stdio.h>
#include <math.h>

float f(x,L)
float x,L;
{

	return( 27.5 + 7.5*cos(x) - L*sin(x) );
}

float fp(x,L)
float x,L;
{
	return( -7.5*sin(x) - L*cos(x) );
}

float angle(L)
float L;
{
	float x,newx,dx,eps=1e-5;
	int try;

	x = 0.35;
	for(try=0;fabs( f(x,L) ) > eps;try++)
		{
		if( try > 100 )
			{
			printf("More than 100 tries at finding a root.\n");
			printf("L:  %f\n",L);
			exit(1);
			}
		dx = f(x,L)/fp(x,L);
		newx = x - dx;
		x = newx;
		}
	return( x );
}


main()
{
	float sl,el;
        float l,theta,x1,cx,cy,fpx,fpy,r,dl,z;
	int   i,numl;
        FILE *out;

	printf("starting, ending and number of l:  ");
	scanf("%f,%f,%d",&sl,&el,&numl);
	printf("z=0 at what distance (m)        :  ");
	scanf("%f",&z);
        out = fopen("testrun.com","w");
        fprintf(out,"$sd disk1:[nicholas.cerenkov.raytrace]\n");
        fprintf(out,"$set noverify\n");
	fprintf(out,"$del eff1.dat;*\n");
	dl = (el-sl)/(numl-1.);
	fpy = 62.5;
        cy  = 27.5;
	for(l=sl,i=0;i < numl; i++, l += dl)
		{
		fprintf(out,"$! l = %f\n",l);
                theta = angle(l);
		x1 = 150. - 55.0*tan(.5*theta);
                cx = .5*(150+x1);
                fpx = 150. - l;
		r = 2.0*sqrt( (cx-fpx)*(cx-fpx) + (cy-fpy)*(cy-fpy) );
                fprintf(out,"$run raytr\n");
		fprintf(out," 2\n -70,70\n 0,150\n");

		fprintf(out," %f,0\n 150, 55\n %f\n 1\n",x1,r);
		fprintf(out," %f,0\n 150,-55\n %f\n 2\n",x1,r);
                fprintf(out," hms_spec.dat\n %f\n 1\n 82.5,15\n 5,15\n",z);
		fprintf(out,"$del raytr.top;*\n");
		}
}
