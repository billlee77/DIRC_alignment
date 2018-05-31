#include <stdio.h>
#include <math.h>

#define N	50	/* number of runs	*/

#define TRA	0	/* transverse	*/
#define DIS     1	/* dispersive	*/
#define UNCOR	0	/* uncorrected	*/
#define COR	1	/* corrected	*/

/* this program adjusts the output of the position finding run of RAYTR
	to take in account of the tilt of the mirror in x position of the 
	focal point for the dispersive direction.	*/

float 	fpx[60][2][2],
	fpy[60][2][2],
	ep[60][2][2],
	size[60][2][2],
	radius[60];

main()
{
	FILE *in,*out;
	int i;
	float theta,newfpx,newfpx2;

/*	if( !(in=fopen("eff1.dat","r")) )
		{
		printf("unable to open 'eff1.dat'.\n");
		exit(1);
		}
	for(i=0;i<N;i++)
		{
		fscanf(in,"%f %f %f %f ",&(fpx[i][TRA][UNCOR]),
					 &(fpy[i][TRA][UNCOR]),
					 &(ep[i][TRA][UNCOR]),
					 &(size[i][TRA][UNCOR]) );
		fscanf(in,"%f %f %f %f ",&(fpx[i][TRA][COR]),
					 &(fpy[i][TRA][COR]),
					 &(ep[i][TRA][COR]),
					 &(size[i][TRA][COR]) );
		fscanf(in,"\n");
		}
	for(i=0;i<N;i++)
		{
		fscanf(in,"%f %f %f %f ",&(fpx[i][DIS][UNCOR]),
					 &(fpy[i][DIS][UNCOR]),
					 &(ep[i][DIS][UNCOR]),
					 &(size[i][DIS][UNCOR]) );
		fscanf(in,"%f %f %f %f ",&(fpx[i][DIS][COR]),
					 &(fpy[i][DIS][COR]),
					 &(ep[i][DIS][COR]),
					 &(size[i][DIS][COR]) );
		fscanf(in,"\n");
		}
	fclose(in);
*/
	if( !(in=fopen("radius.lst","r")) )
		{
		printf("unable to open 'radius.lst'.\n");
		exit(1);
		}
	for(i=0;i<N;i++)
		{
		fscanf(in,"%f\n",radius+i);
		}
	fclose( in );
 

	out = fopen("out.top","w");
	fprintf(out,"set font duplex\n");
	fprintf(out,"title top 'efficiency vs PMT placement'\n");
	fprintf(out,"title bottom 'PMT placement (cm)'\n");
	fprintf(out,"title left 'efficiency and spot size (%% of PMT size)'\n");
	fprintf(out,"title      'solid: transverse, dashed: dispersive'\n");
	fprintf(out,"title      'solid: corrected, dotted: uncorrected'\n");
	fprintf(out,"set limits x 0 to 120 y 60 to 105\n");

/* uncorrected transverse efficiency	*/
	for(i=0;i<N;i++)
		{
		fprintf(out,"%f %f\n",fpx[i][TRA][UNCOR],ep[i][TRA][UNCOR]);
		}
	fprintf(out,"join 1 dots\n");

/* corrected transverse efficiency	*/
	for(i=0;i<N;i++)
		{
		fprintf(out,"%f %f\n",fpx[i][TRA][COR],ep[i][TRA][COR]);
		}
	fprintf(out,"join 1\n");

/* uncorrected transverse spot size	*/
	for(i=0;i<N;i++)
		{
		fprintf(out,"%f %f\n",fpx[i][TRA][UNCOR],size[i][TRA][UNCOR]);
		}
	fprintf(out,"join 1 dots\n");

/* corrected transverse spot size	*/
	for(i=0;i<N;i++)
		{
		fprintf(out,"%f %f\n",fpx[i][TRA][COR],size[i][TRA][COR]);
		}
	fprintf(out,"join 1\n");

/* uncorrected dispersive efficiency	*/
	for(i=0;i<N;i++)
		{
		theta = asin( fpy[i][TRA][UNCOR]/radius[i]);
		newfpx = fpx[i][DIS][UNCOR] + radius[i]*(1.0-cos(theta) );
		fprintf(out,"%f %f\n",newfpx,ep[i][DIS][UNCOR]);
		}
	fprintf(out,"join 1 dotdash\n");

/* corrected dispersive efficiency	*/
	for(i=0;i<N;i++)
		{
		theta = asin( fpy[i][TRA][COR]/radius[i]);
		newfpx = fpx[i][DIS][COR] + radius[i]*(1.0-cos(theta) );
		fprintf(out,"%f %f\n",newfpx,ep[i][DIS][COR]);
		}
	fprintf(out,"join 1 dashes\n");

/* uncorrected dispersive spot size	*/
	for(i=0;i<N;i++)
		{
		theta = asin( fpy[i][TRA][UNCOR]/radius[i]);
		newfpx = fpx[i][DIS][UNCOR] + radius[i]*(1.0-cos(theta) );
		fprintf(out,"%f %f\n",newfpx,size[i][DIS][UNCOR]);
		}
	fprintf(out,"join 1 dotdash\n");

/* corrected dispersive spot size	*/
	for(i=0;i<N;i++)
		{
		theta = asin( fpy[i][TRA][COR]/radius[i]);
		newfpx = fpx[i][DIS][COR] + radius[i]*(1.0-cos(theta) );
		fprintf(out,"%f %f\n",newfpx,size[i][DIS][COR]);
		}
	fprintf(out,"join 1 dashes\n");


	fprintf(out,"new frame\n");
	fprintf(out,"title top 'x vs y position'\n");
	fprintf(out,"title bottom 'x position (cm)'\n");
	fprintf(out,"title left 'y position (cm)'\n");
	fprintf(out,"title      'solid: transverse, dashed: dispersive'\n");
	fprintf(out,"set limits x 0 to 120 y 26 to 52\n");
	fprintf(out,"title      'solid: corrected, dotted: uncorrected'\n");

/* uncorrected transverse x vs y	*/
	for(i=0;i<N;i++)
		{
		fprintf(out,"%f %f\n",fpx[i][TRA][UNCOR],fpy[i][TRA][UNCOR]);
		}
	fprintf(out,"join 1 dots\n");

/* corrected transverse x vs y	*/
	for(i=0;i<N;i++)
		{
		fprintf(out,"%f %f\n",fpx[i][TRA][COR],fpy[i][TRA][COR]);
		}
	fprintf(out,"join 1\n");

/* uncorrected dispersive x vs y	*/
	for(i=0;i<N;i++)
		{
		theta = asin( fpy[i][TRA][UNCOR]/radius[i]);
		newfpx = fpx[i][DIS][UNCOR] + radius[i]*(1.0-cos(theta) );
		fprintf(out,"%f %f\n",newfpx,fpy[i][DIS][UNCOR]);
		}
	fprintf(out,"join 1 dotdash\n");

/* corrected dispersive spot x vs y	*/
	for(i=0;i<N;i++)
		{
		theta = asin( fpy[i][TRA][COR]/radius[i]);
		newfpx = fpx[i][DIS][COR] + radius[i]*(1.0-cos(theta) );
		fprintf(out,"%f %f\n",newfpx,fpy[i][DIS][COR]);
		}
	fprintf(out,"join 1 dashes\n");

	fclose(out);

	out = fopen("eff1_adjusted.dat","w");
	for(i=0;i<N;i++)
		{
		theta = asin( fpy[i][TRA][UNCOR]/radius[i]);
		newfpx = fpx[i][DIS][UNCOR] + radius[i]*(1.0-cos(theta) );
		theta = asin( fpy[i][TRA][COR]/radius[i]);
		newfpx2 = fpx[i][DIS][COR] + radius[i]*(1.0-cos(theta) );
		fprintf(out,"%6.2f  %6.2f  %6.2f  %6.2f  ",newfpx,
					 fpy[i][DIS][UNCOR],
					 ep[i][DIS][UNCOR],
					 size[i][DIS][UNCOR]) ;
		fprintf(out,"%6.2f  %6.2f  %6.2f  %6.2f  ",newfpx2,
					 fpy[i][DIS][COR],
					 ep[i][DIS][COR],
					 size[i][DIS][COR]) ;
		fprintf(out,"\n");
		}
}	
