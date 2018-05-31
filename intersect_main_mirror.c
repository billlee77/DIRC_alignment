/* this function determines whether the given ray intersects the given mirror.
If there is an intersection, the ray is moved to the point of intersection, and
updated to point in the reflected direction. See my notes for the geometry and
variables. Returns TRUE if there is an intersection	*/
#include "raytr.h"

//MIRROR *m;
//RAY    *r;

using namespace std;

int intersect_main_mirror( MIRROR* m, RAY* r, TCanvas* c1) {
    double dx,dy,x,y,b,c,dis,t1,t2,nx,ny,phi;
   
/* determine if ray intersects the circle that is mirror is part of	*/
    dx = m->Cx - r->x;
    dy = m->Cy - r->y;
    b = -2.0*(dx*sin(r->theta)+dy*cos(r->theta));
    c = dx*dx + dy*dy - m->R*m->R;
    dis = b*b - 4.0*c;





    if( dis > 0.0 ) { /* if true, does intersect circle */

       t1 = 0.5*(-b + sqrt(dis));
       t2 = 0.5*(-b - sqrt(dis));
       x = r->x + t1*sin(r->theta);               /* try first intersection pt*/
       y = r->y + t1*cos(r->theta);
       dis = sqrt( sqr(x-m->Mx) + sqr(y-m->My) ); /*distance from intersection*/

       if( dis > m->L ) {                         /* point to middle of mirror*/
                                                  /* first not it, */
         x = r->x + t2*sin(r->theta);             /* try second */
         y = r->y + t2*cos(r->theta);
         dis = sqrt( sqr(x-m->Mx) + sqr(y-m->My) );

         if( dis > m->L ) {
            dis = -1.0;
         }

       }

    }




//    cout << b*b << "    " << c << "     " << dis << endl;   
//  	cout << r->x << "    " <<  r->y << endl;
//  		exit(0);






    if( dis > 0.0 ) {                     /* does intersect mirror */

//       fprintf(out,"%f %f\n%f %f\njoin dots\n",r->x,r->y,x,y);

		cout << r->x << "    " <<  r->y << endl;


 	   TGraph* traj_in = new TGraph();
 
 	   traj_in->SetPoint(traj_in->GetN(), r->x, r->y);
 	   traj_in->SetPoint(traj_in->GetN(), x, y);
 	
 	   traj_in->SetLineStyle(2);
 //	   traj_in->SetLineWidth(2);
 	   	
 	   traj_in->DrawClone("*C");
 	   
       delete traj_in;
	   





       r->x = x;
       r->y = y;
       nx = -(x-m->Cx)/m->R; /*calculate normal to mirror at intersection pt*/
       ny = -(y-m->Cy)/m->R;
       phi = acos( ny );
       if( nx < 0.0 )
         phi = 2.0*PI - phi;
       r->theta += PI;              /* set new ray angle, reflected about pt */
       if( r->theta > 2.0*PI )
          r->theta = r->theta - 2.0*PI;
       r->theta = 2.0*phi - r->theta;
       if( r->theta > 2.0*PI )
          r->theta = r->theta - 2.0*PI;
       if( r->theta < 0.0 )
          r->theta += 2.0*PI;
       return( 1 );

   } else { 
       return( 0 );

   }

}
