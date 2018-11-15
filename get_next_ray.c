/* this file has three functions:
	get_ray_setup() :- loads the TRANSPORT matrices,
	reset_get_ray() :- resets the counter variables for another pass
	get_next_ray() :- sets the ray to the next ray to follow.
*/
#include "raytr.h"

static float R[6][6],T[6][6][6],in[6],outvec[6],Zo,z;
static float delta_plo,delta_phi,delta_y,delta_angle;
static float dp,dy,dangle;
static int   set_up= FALSE,cray_num=0;




/* added by dbd january 16 2008 */
/* static float cer_angle = 0.01157; */
/* cerenkov angle for neon at 1 atm, n= 1.000067 */
/* gh - 2008
   Cherenkov angle for 7.0 GeV/c pions, 2.84deg 
   delta_plo,delta_phi for asymmetric SHMS delta acceptance
*/
static float cer_angle = 0.049567;
int   using_x_direction;





/*--------------------------------------------------*/
/*--------------------------------------------------*/


extern int ray_number,num_caught;

using namespace std;


void get_ray_setup() {

    	int i,j,k,dum;
    	float numsamples;
    	char fname[50];
    	FILE *file;


	do {
    		printf("Transport file name:  ");
    		scanf("%s",fname);
    		file = fopen(fname,"r");
    		if( ! file ) 
	       		printf("Unable to open file '%s'.\n",fname);
       		}
    	while( ! file );
    	Zo = 24.56;
	fscanf(file," %f\n",&Zo);
/* read first order matrix */
    	for(j=0;j<6;j++)
       		{
       		for(i=0;i<6;i++)
          		{
          		fscanf(file,"%f ",&(R[j][i]));
          		}
       		fscanf(file,"\n");
       		}

/* read second order matrix */
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

/* input user stuff */
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
    	else {
       		printf("Not a choice\n");
       		exit(1);
        }

    	if( using_x_direction ) {
       		printf("Enter delta theta and number of sample points:  ");
       		scanf("%f,%f",&delta_angle,&numsamples);
       		dangle = 2.0*delta_angle/(numsamples-1.0);
       		in[_THETA] = -delta_angle;
       		printf("Enter delta plo, delta phi, and number of sample points    :  ");
       		scanf("%f,%f,%f",&delta_plo,&delta_phi,&numsamples);
		/* dp = 2.0*delta_p/(numsamples-1.0); */
       		dp = (delta_phi-delta_plo)/(numsamples-1.0);
       		in[_DELTA] = delta_plo;

//       		fprintf(out,"title 'Dispersive:  DQ: %5.1f; D: %5.1f%5.1f",delta_angle,delta_plo,delta_phi);
//       		fprintf(out,"; z=0 is at %6.2f m.'\n",z);
//       		fprintf(out,"case  '             FG         G'\n");
 
      	} else {

       		printf("Enter delta phi and number of sample points:  ");
       		scanf("%f,%f",&delta_angle,&numsamples);
       		dangle = 2.0*delta_angle/(numsamples-1.0);
       		in[_PHI] = -delta_angle;
       		printf("Enter delta y and number of sample points  :  ");
       		scanf("%f,%f",&delta_y,&numsamples);
       		dy = 2.0*delta_y/(numsamples-1.0);
       		in[_Y] = -delta_y;

//       		fprintf(out,"title 'Tranverse:  DF: %5.1f; Dy: %5.1f",delta_angle,delta_y);
//       		fprintf(out,"; z=0 is at %6.2f m.'\n",z);
//       		fprintf(out,"case  '            FG         F'\n");

       	}

    	set_up= TRUE;
    	ray_number = 0;  

}






// reset_get_ray(out)
// FILE *out;




/*--------------------------------------------------*/
/*--------------------------------------------------*/


void reset_get_ray() {

    	if( using_x_direction )
       		{
       		in[_THETA] = -delta_angle;
		/*       		in[_DELTA] = -delta_p; */
       		in[_DELTA] = -delta_plo;

//        		fprintf(out,"title 'Dispersive:  DQ: %5.1f; D: %5.1f%5.1f",delta_angle,delta_plo,delta_phi);
//        		fprintf(out,"; z=0 is at %6.2f m.'\n",z);
//        		fprintf(out,"case  '             FG         G'\n");

       		}
    	else
       		{
       		in[_PHI] = -delta_angle;
       		in[_Y] = -delta_y;

//        		fprintf(out,"title 'Tranverse:  DF: %5.1f; Dy: %5.1f",delta_angle,delta_y);
//        		fprintf(out,"; z=0 is at %6.2f m.'\n",z);
//        		fprintf(out,"case  '            FG         F'\n");
       		}

    	ray_number = 0;  

}


/*--------------------------------------------------*/
/*--------------------------------------------------*/


int get_next_ray(RAY* r, float left, float right) {

//	RAY *r;


	RAY  templ;

    int i,j,k;
    float theta;

// 	if( ! set_up )
//        		get_ray_setup();
//     	if( cray_num == 0 ) {
// 
//       		if( using_x_direction ) {
// 
// 
// 				/*--------------------------------------------------*/
// 				/// Exit with the last ray
// 
// 
//          		if( in[_THETA] > delta_angle )
//             			return( 0 ); /* done last ray */
// /* do matrix multiplies */
//          		for(i=0;i<6;i++)
//             			{
//             			outvec[i] = 0;
//             			for(j=0;j<6;j++)
//                				{
//                				outvec[i] += R[i][j]*in[j];
//                				for(k=0;k<6;k++)
//                   				outvec[i] += T[i][j][k]*in[j]*in[k];
//                				}
//             			}
// /* convert to RAY structure */
//          		templ.x = left;
//          		templ.y = outvec[_X];
//          		templ.theta = 0.5*PI - outvec[_THETA]/1000.0;
//          		theta = outvec[_THETA]/1000.0;
// /* increment to next ray */
//          		/* if( (in[_DELTA] += dp) > delta_p ) */
//          		if( (in[_DELTA] += dp) > delta_phi ) {
// 			        /* in[_DELTA] = -delta_p; */
//             			in[_DELTA] = delta_plo;
//             			in[_THETA] += dangle;
//                 }
//  
//         	} else { 
// 
// // 				/* tranverse case, like above dispersive case ( using_x_direction = TRUE ) */
// //      
// // 	         		if( in[_PHI] > delta_angle )
// // 	            			return( 0 );
// // 	         		for(i=0;i<6;i++)
// // 	            			{
// // 	            			outvec[i] = 0;
// // 	            			for(j=0;j<6;j++)
// // 	               				{
// // 	               				outvec[i] += R[i][j]*in[j];
// // 	               				for(k=0;k<6;k++)
// // 	                  				outvec[i] += T[i][j][k]*in[j]*in[k];
// // 	               				}
// // 	            			}
// // 	         		templ.x = left;
// // 	         		templ.y = outvec[_Y];
// // 	         		templ.theta = 0.5*PI + outvec[_PHI]/1000.0;
// // 	
// // 	         		if( (in[_Y] += dy) > delta_y ) {
// // 	
// // 	            	  in[_Y] = -delta_y;
// // 	            	  in[_PHI] += dangle;
// // 	
// // 	            	}
// 
//          	}
// 
//       		templ.y += tan(templ.theta-0.5*PI)*(Zo-z)*100.0;
// 
// //      		fprintf(out,"%f %f\n%f %f\njoin\n",left,template.y,right,
// //                        template.y-tan(template.theta-0.5*PI)*(right-left) );
// 
// 
// 
//  	  	   	TGraph* traj_in = new TGraph();
//    
//    		   	traj_in->SetPoint(traj_in->GetN(), left,templ.y);
//    	   		traj_in->SetPoint(traj_in->GetN(), right, templ.y-tan(templ.theta-0.5*PI)*(right-left));
//    	
//    	   		traj_in->SetLineStyle(2);
//  
//    //	   	traj_in->SetLineWidth(2);  	   	
//      	   	traj_in->Draw("C");
//    
// 			delete traj_in;
// 
//       		}
// 
//   	r->x = templ.x;
//   	r->y = templ.y;
//   	r->theta = templ.theta + cer_angle*(float)(cray_num-1);
// 
// 
// 
//     	r->x = 0.0;
//     	r->y = 20.8;
//     	r->theta = 1.5;
// 
// 

//	cout << r->x  <<  "   " << r->y << "    " << r->theta << endl;

//	exit(0);




//	cout << "???   " << ray_number << "     "  << r->x << "    " << r->y << "     " << r->theta << endl;




//     	r->x = 22.0;
//     	r->y = 37.0;
//     	r->theta = -40* asin(1.0)/90 ;
// 
//     	r->x = 13.0;
//     	r->y = 46.0;
//     	r->theta = -60* asin(1.0)/90 ;
// 
//     	r->x = 25.0;
//     	r->y = 40.0;
//     	r->theta = -42.13* asin(1.0)/90 ;
// 



		if (ray_number == 0) {
	
    		r->theta = -42.13* asin(1.0)/90 ;

//    		r->x = 22.0;
//    		r->y = 38.0;


//    		r->x = 22.0;
//    		r->y = 38.0;

//  	  		r->x = reference_x +  23 * sin(abs(r->theta));
//    			r->y = reference_y -  23 * cos(abs(r->theta));



  	  		r->x = reference_x +  (5) * sin(abs(r->theta));
   			r->y = reference_y -  (5) * cos(abs(r->theta));
 
//      		r->theta = -60* asin(1.0)/90;
 
 
 //    		r->x = 19.9876;
 //    		r->y = 40.2249;
 
 			cout << "Setup  the ray " << endl;
 			
 //			exit(0);
 
 
//  		   		r->x = 22.0 +  (-15) * sin(abs(r->theta));
//      			r->y = 38.0 -  (-15) * cos(abs(r->theta));
  		
  				
      			r->theta = -60* asin(1.0)/90 ;
 // 
 // 
 
//  		   		r->x = reference_x +  22 * sin(abs(r->theta));
//    			r->y = reference_y -  22 * cos(abs(r->theta));

// 		   		r->x = reference_x +  27 * sin(abs(r->theta));
//    			r->y = reference_y -  27 * cos(abs(r->theta));


			

		} else {



     		r->theta = -42.13* asin(1.0)/90 ;
// 
// //    		r->x = 22.0 +  ray_number * 0.5 * sin(abs(r->theta));
// //    		r->y = 38.0 -  ray_number * 0.5 * cos(abs(r->theta));
// 
// 			
// 			if (ray_number%2 == 1) {
// 
//  		   		r->x = 22.0 -  ray_number * 1 * sin(abs(r->theta));
//     			r->y = 38.0 +  ray_number * 1 * cos(abs(r->theta));
// 
// 				cout << "Ray number: " << ray_number  << "  " << r->x << "  " << r->y  << "   modulus: " << ray_number%2 << "   " << ray_number * 1 * sin(abs(r->theta)) << "   " << ray_number * 1 * cos(abs(r->theta)) << endl;
// 
// 			} else {
// 
//  		   		r->x = 22.0 +  ray_number * 1 * sin(abs(r->theta));
//     			r->y = 38.0 -  ray_number * 1 * cos(abs(r->theta));
// 
// 				cout << "Ray number: " << ray_number  << "  " << r->x << "  " << r->y  << "   modulus: " << ray_number%2 << "   " << ray_number * 1 * sin(abs(r->theta)) << "   " << ray_number * 1 * cos(abs(r->theta)) << endl;
// 
// 			}


			if (ray_number == 1) {

 		   		r->x = reference_x +  12 * sin(abs(r->theta));
    			r->y = reference_y -  12 * cos(abs(r->theta));

			} else if(ray_number == 2) {
 

 		   		r->x = reference_x +  17 * sin(abs(r->theta));
    			r->y = reference_y -  17 * cos(abs(r->theta));


			} else if(ray_number == 3) {
 

 		   		r->x = reference_x +  22 * sin(abs(r->theta));
    			r->y = reference_y -  22 * cos(abs(r->theta));

			} else if(ray_number == 4) {

 		   		r->x = reference_x +  27 * sin(abs(r->theta));
    			r->y = reference_y -  27 * cos(abs(r->theta));

		
			} 

		}

		if (ray_number == 5) {
			return 0;
		}


   		ray_number++;
   		cray_num = (cray_num+1)%3;



   	return(1);

}

/*--------------------------------------------------*/
/*--------------------------------------------------*/



                                                
