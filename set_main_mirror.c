/* this function gets the position data for a mirror from the user. See my
notes for the details for the geometry and variables */

#include "raytr.h"

//set_main_mirror(m,out)
//MIRROR *m;

using namespace std;

extern float x1,yy1,x2,y2,rr;

void set_main_mirror (MIRROR*m) {

     double x,y,lx,ly,Xcx,Xcy,nx,ny,nnx,nny,r,phi;


//	cout << x1 << endl;

       printf("x1 (x,y):  ");
       scanf("%f,%f",&x1,&yy1);
       m->X1x = x1;
       m->X1y = yy1;
 


      printf("x2 (x,y):  ");
      scanf("%f,%f",&x2,&y2);
      m->X2x = x2;
      m->X2y = y2;
      printf("Radius  :  ");
      scanf("%f",&rr);
      m->R = rr;
      lx = 0.5*(x2-x1);
      ly = 0.5*(y2-yy1);
      Xcx = x1 + lx;
      Xcy = yy1 + ly;
      nx = lx/sqrt(lx*lx+ly*ly);
      ny = ly/sqrt(lx*lx+ly*ly);
      r = sqrt( sqr(m->R) - (lx*lx+ly*ly) );
      phi = acos( ny );
      if( nx <  0.0 )
         phi = PI - phi;
      phi -= 0.5*PI;
      if( phi < 0.0 )
         phi += 2.0*PI;
      printf("Please choose a curvature direction:\n");
      printf(" (1)  %-5.2f,%-5.2f  %f\n (2)  %-5.2f,%-5.2f  %f\n",-ny,nx,
               phi*57.296,ny,-nx,((phi-PI) > 0.0 ? phi - PI : phi + PI)*57.296);
      scanf("%f",&rr);
      phi -= 0.5*PI;
      if( phi < 0.0 )
         phi += 2.0*PI;
      m->phi = phi;
      if( rr == 1.0 )
         {
         nnx = -ny;
         nny =  nx;
         }
      else if ( rr == 2.0 )
         {
         nnx =  ny;
         nny = -nx;
         }
      else
         {
         printf("Not a choice.\n");
         exit(1);
         }
      printf("Thank you.\n");
      m->Cx = Xcx + r*nnx;
      m->Cy = Xcy + r*nny;
      m->Mx = Xcx - (m->R - r)*nnx;
      m->My = Xcy - (m->R - r)*nny;
      m->Fx = 0.5*(m->Cx + m->Mx);
      m->Fy = 0.5*(m->Cy + m->My);
      m->L  = sqrt( sqr(m->Mx - x1) + sqr(m->My - yy1) );
      phi = acos( -nnx );
      if( nny < 0.0 )
         phi *= -1.0;
      m->phi += phi;
      nx = (m->Fx - m->Mx)/sqrt( sqr(m->Fx-m->Mx) + sqr(m->Fy-m->My) );
      ny = (m->Fy - m->My)/sqrt( sqr(m->Fx-m->Mx) + sqr(m->Fy-m->My) );
      nnx =  nx*cos(phi) + ny*sin(phi);
      nny = -nx*sin(phi) + ny*cos(phi);
      m->Fx = m->Mx + 0.5*m->R*nnx;
      m->Fy = m->My + 0.5*m->R*nny;
 
      printf("Focal Point:  % 6.1f,% 6.1f\n",m->Fx,m->Fy);
 
 #ifdef DEBUG
 printf("Xc:  % f,% f\n",Xcx,Xcy);
 printf("C :  % f,% f\n",m->Cx,m->Cy);
 printf("M :  % f,% f\n",m->Mx,m->My);
 printf("L :  % f\n",m->L);
 printf("F :  % f,% f\n",m->Fx,m->Fy);
 printf("ph:  % f\n",m->phi*57.296);	
 #endif

}
