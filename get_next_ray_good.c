#include "raytr.h"

static float R[6][6],T[6][6][6],in[6],outvec[6],Zo,z;
static float delta_p,delta_y,delta_angle;
static float dp,dy,dangle;
static int   set_up= FALSE,cray_num=0;
static RAY   template;
int   using_x_direction;



get_ray_setup(out)
FILE *out;
{
    int i,j,k,dum;
    float numsamples;
    char fname[50];
    FILE *file;

    printf("Transport file name:  ");
    scanf("%s",fname);
    file = fopen(fname,"r");
    if( ! file ) 
       {
       printf("Unable to open file.\n");
       exit(1);
       }
/*
    fscanf("%f\n",&Zo);
*/
    Zo = 24.56;
    for(j=0;j<6;j++)
       {
       for(i=0;i<6;i++)
          {
          fscanf(file,"%f ",&(R[j][i]));
          }
       fscanf(file,"\n");
       }

    for(i=0;i<6;i++)
       for(j=0;j<6;j++)
          for(k=0;k<6;k++)
             T[i][j][k] = 0.0;
    for(i=0;i<5;i++)
       {
       for(j=0;j<6;j++)
          {
          for(k=0;k<=j;k++)
             fscanf(file,"%d %d %e",&dum,&dum,&(T[i][j][k]) );
          fscanf(file,"\n");
          }
       fscanf(file,"\n");
       }
    fclose( file );

    for(i=0;i<6;in[i++]=0.0);
    in[_X] = 0.01;
    printf("z=0 equals how meters along the beam path:  ");
    scanf("%f",&z);
    printf("Do you want to vary the\n");
    printf("  (1)  dispersive\n");
    printf("  (2)  transverse\n");
    scanf("%d",&i);
    if( i == 1 )
       using_x_direction = TRUE;
    else if ( i== 2)
       using_x_direction = FALSE;
    else
       {
       printf("Not a choice\n");
       exit(1);
       }
    if( using_x_direction )
       {
       printf("Enter delta theta and number of sample points:  ");
       scanf("%f,%f",&delta_angle,&numsamples);
       dangle = 2.0*delta_angle/(numsamples-1.0);
       in[_THETA] = -delta_angle;
       printf("Enter delta p and number of sample points    :  ");
       scanf("%f,%f",&delta_p,&numsamples);
       dp = 2.0*delta_p/(numsamples-1.0);
       in[_DELTA] = -delta_p;
       fprintf(out,"title 'Dispersive:  DQ: %5.1f; D: %5.1f",delta_angle,delta_p);
       fprintf(out,"; z=0 is at %6.2f m.'\n",z);
       fprintf(out,"case  '             FG         G'\n");
       }
    else
       {
       printf("Enter delta phi and number of sample points:  ");
       scanf("%f,%f",&delta_angle,&numsamples);
       dangle = 2.0*delta_angle/(numsamples-1.0);
       in[_PHI] = -delta_angle;
       printf("Enter delta y and number of sample points  :  ");
       scanf("%f,%f",&delta_y,&numsamples);
       dy = 2.0*delta_y/(numsamples-1.0);
       in[_Y] = -delta_y;
       fprintf(out,"title 'Tranverse:  DF: %5.1f; Dy: %5.1f",delta_angle,delta_y);
       fprintf(out,"; z=0 is at %6.2f m.'\n",z);
       fprintf(out,"case  '            FG         F'\n");
       }
    set_up= TRUE;
    ray_number = 0;  
}

int get_next_ray(r,out,left,right)
RAY *r;
FILE *out;
double left,right;
{
    int i,j,k;
    float theta;

    if( ! set_up )
       get_ray_setup(out);
    if( cray_num == 0 )
      {
      if( using_x_direction )
         {
         if( in[_THETA] > delta_angle )
            return( 0 );
         for(i=0;i<6;i++)
            {
            outvec[i] = 0;
            for(j=0;j<6;j++)
               {
               outvec[i] += R[i][j]*in[j];
               for(k=0;k<6;k++)
                  outvec[i] += T[i][j][k]*in[j]*in[k];
               }
            }
         template.x = left;
         template.y = outvec[_X];
         template.theta = 0.5*PI + outvec[_THETA]/1000.0;
         theta = outvec[_THETA]/1000.0;
         if( (in[_DELTA] += dp) > delta_p )
            {
            in[_DELTA] = -delta_p;
            in[_THETA] += dangle;
            }
         }
      else 
         {
         if( in[_PHI] > delta_angle )
            return( 0 );
         for(i=0;i<6;i++)
            {
            outvec[i] = 0;
            for(j=0;j<6;j++)
               {
               outvec[i] += R[i][j]*in[j];
               for(k=0;k<6;k++)
                  outvec[i] += T[i][j][k]*in[j]*in[k];
               }
            }
         template.x = left;
         template.y = outvec[_Y];
         template.theta = 0.5*PI + outvec[_PHI]/1000.0;
         if( (in[_Y] += dy) > delta_y )
            {
            in[_Y] = -delta_y;
            in[_PHI] += dangle;
            }
         }
/*
      template.y += tan(template.theta-0.5*PI)*(z-Zo)*100.0;
*/
      fprintf(out,"%f %f\n%f %f\njoin\n",left,template.y,right,
                        template.y-tan(template.theta-0.5*PI)*(right-left) );

      }
   r->x = template.x;
   r->y = template.y;
   r->theta = template.theta + 0.0211451339*(float)(cray_num-1);
   cray_num = (cray_num+1)%3;
   ray_number++;
/*
   fprintf(out,"%f %f\n%f %f\njoin dotdash\n",left,r->y,right,
                        r->y+tan(r->theta-0.5*PI)*(right-left) );
*/
   return( 1);
}
