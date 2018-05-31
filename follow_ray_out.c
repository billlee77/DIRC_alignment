/* this function calculates where a light ray that missed the PMTs leaves the
data window.	*/
#include "raytr.h"

using namespace std;

void follow_ray_out(RAY* r, TCanvas* c1, double left, double right, double top, double bottom) {


    double b,c,x,y;

    if( (r->theta==0.0) || (r->theta==2.0*PI) )
       {
       x = r->x;
       y = top;
       }
    else if ( r->theta < 0.5*PI )
       {
       b = top-r->y;
       c = b*tan(r->theta);
       if( (r->x+c) <= right )
         {
         x = r->x+c;
         y = top;
         }
       else
         {
         x = right;
         y = r->y + (right-r->x)*tan(0.5*PI-r->theta);
         }
       }
    else if( r->theta == 0.5*PI )
       {
       x = right;
       y = r->y;
       }
    else if ( r->theta < PI )
       {
       b = right-r->x;
       c = b*tan(r->theta-0.5*PI);
       if( (r->y-c) >= bottom )
         {
         x = right;
         y = r->y-c;
         }
       else
         {
         x = r->x + (r->y-bottom)*tan(PI-r->theta);
         y = bottom;
         }
       }
    else if( r->theta == PI )
       {
       x = r->x;
       y = bottom;
       }
    else if( r->theta < 1.5*PI )
       {
       b = r->y-bottom;
       c = b*tan(r->theta - PI);
       if( (r->x-c) >= left )
         {
         x = r->x-c;
         y = bottom;
         }
       else
         {
         x = left;
         y = r->y - (r->x-left)*tan(1.5*PI - r->theta);
         }
       }
    else if( r->theta == 1.5*PI )
       {
       x = left;
       y = r->y;
       }
    else
       {
       b = r->x-left;
       c = b*tan(r->theta - 1.5*PI);
       if( (r->y+c) <= top )
         {
         x = left;
         y = r->y+c;
         }
       else
         {
         x = r->x - (top-r->y)*tan( 2.0*PI - r->theta);
         y = top;
         }
       }


//	   cout <<  r->x << "    " << r->y << "    " << x << "    " <<y << endl;

	   c1->Update();
	
 	   TGraph* traj = new TGraph();
 
 	   traj->SetPoint(traj->GetN(), r->x, r->y);
 	   traj->SetPoint(traj->GetN(), x, y);
 	
 	   traj->SetLineStyle(2);
 //	   traj->SetLineWidth(2);
 	   	
 	   traj->DrawClone("C");
 
 	   delete traj;

//    fprintf(out,"%f %f\n%f %f\njoin dots\n",r->x,r->y,x,y);

}


