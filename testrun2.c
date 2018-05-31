#include <stdio.h>
#include <math.h>


main()
{
	float sl,el;
        float l,theta,x1,cx,cy,fpx,fpy,r,dl,z,x,y;
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
		x = 150.0 - l;
		y = 60.0;
		theta = atan(x/y);
		x1 = l;
		r = 2.0*(y/2.0+20.0)/sin(2.0*theta);
		fprintf(out,"$! l = %f\n",l);
                fprintf(out,"$run raytr\n");
		fprintf(out," 1\n -40,70\n 0,150\n");
		fprintf(out," %f,-30\n 150, 30\n %f\n 1\n",x1,r);
                fprintf(out," hms_spec.dat\n %f\n 2\n 22,15\n 5,15\n",z);
	  	fprintf(out,"$del raytr.top;*\n");  
		}
	for(l=sl,i=0;i < numl; i++, l += dl)
		{
		x = 150.0 - l;
		y = 60.0;
		theta = atan(x/y);
		x1 = l;
		r = 2.0*(y/2.0+20.0)/sin(2.0*theta);
		x1 = 0.5*(l+150);
		fprintf(out,"$! l = %f\n",l);
                fprintf(out,"$run raytr\n");
		fprintf(out," 2\n -70,70\n 0,150\n");
		fprintf(out," %f,0\n %f, 55\n %f\n 1\n",x1,x1,r);
		fprintf(out," %f,0\n %f,-55\n %f\n 2\n",x1,x1,r);
                fprintf(out," hms_spec.dat\n %f\n 1\n 82.5,15\n 5,15\n",z);
	  	fprintf(out,"$del raytr.top;*\n");  
		}
}
