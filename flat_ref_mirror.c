/* Second reflector	*/

#include "raytr.h"

using namespace std;

int flat_reflect( MIRROR* m, RAY* r, TCanvas* c1) {

     double dx,dy,x,y,b,c,dis,t1,t2,nx,ny,phi;

//     
//      dx = m->Cx - r->x;
//      dy = m->Cy - r->y;


	m->R = 0;

	cout << "Mirror: " << m->Cx << "  " << m->Cy << "  " << m->R << "  " << m->L << endl;
	cout << "Mirror: " << m->phi << "  " << m->X1x << "  " << m->X1y << "  " << m->X2x << "  " << m->X2y << endl;

	cout << "Ray: " << r->x << "    " << r->y << "    " << r->theta << "   " <<  m->phi << endl;
	cout << "Intesect: " << 10 << "    " << r->y + tan(0.5*PI-r->theta)* (10 - r->x) << endl;

	x = 10;
	y = r->y + tan(0.5*PI-r->theta)* (10 - r->x);


  	TGraph* traj = new TGraph();
  
  	traj->SetPoint(traj->GetN(), r->x, r->y);
  	traj->SetPoint(traj->GetN(), x, y);
  	
  	traj->SetLineStyle(2);
  		
  	traj->DrawClone("*C");
  	
    delete traj;

	cout << "Angle " << r->theta << "  " << r->theta - 0.5*PI << endl;

	r->x = x;   
	r->y = y;   
	r->theta = r->theta - 0.5*PI;   


	return 1;


}
