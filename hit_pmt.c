/* Determines whether the light ray is to strike the face of the PMT, updates
the stats for later repositioning of the PMT.  See my notes for the details of
the geometry used here.	*/
#include "raytr.h"

#define RD 57.29577951

using namespace std;


int hit_PMT(MIRROR* m, RAY* r, STATS* stat, TCanvas* c1) {
    double x,y,lx,ly,ll,ll_pr,s,phi,psi,zeta;

	extern int num_caught;


#ifdef DEBUG    
printf("ray:  x,y:  % f,% f   theta:  % f\n",r->x,r->y,r->theta*RD);
printf("mirror:  F: % f,% f,  phi  :  % f\n",m->Fx,m->Fy,m->phi*RD);
#endif

//     lx = m->Fx - r->x;
//     ly = m->Fy - r->y;
// 
//     ll = sqrt( lx*lx + ly*ly );
// 	
// 	
// 	cout << lx << "    " << ly  << "     " << ll<< endl;
// 
// 
//     psi = acos( sin(r->theta)*lx/ll + cos(r->theta)*ly/ll );
//     phi = PI - fabs(PI/2 - r->theta);


    lx = m->Fx - r->x;
    ly = m->Fy - r->y;
    ll = sqrt( lx*lx + ly*ly );
    psi = acos( sin(r->theta)*lx/ll + cos(r->theta)*ly/ll );

//    phi = PI - fabs(m->phi - r->theta);

    phi = PI - fabs(PI - r->theta);





#ifdef DEBUG
printf("l       :   % f,% f, psi:     % f,  phi:  % f\n",lx,ly,psi*RD,phi*RD);
#endif

	cout << psi/2/PI*360 << "  " << phi/PI*180 << endl;
//	exit(0);
//
    s = ll*sin(psi)/sin(phi);

#ifdef DEBUG
printf("  s: % f\n",s);
scanf("%lf",&y);
#endif

//    zeta = PI - phi - psi;

    ll_pr = sqrt( s*s + ll*ll - fabs(2.0*s*ll*cos(zeta)) );
//    ll_pr = sqrt( s*s + ll*ll);

//    x = r->x + ll_pr*sin(r->theta);
//    y = r->y + ll_pr*cos(r->theta);


//     x = r->x + ll_pr*sin(r->theta - PI);
//     y = r->y + ll_pr*cos(r->theta - PI);

    zeta = PI - phi - psi;
    ll_pr = sqrt( s*s + ll*ll );
//    ll_pr = sqrt( s*s + ll*ll - fabs(2.0*s*ll*cos(zeta)) );
    x = r->x + ll_pr*cos(PI/2 - r->theta-PI);
    y = r->y + ll_pr*sin(PI/2 - r->theta-PI);


	cout << ll_pr  << "    " << r->theta*180/PI << "   " << (r->theta -PI) *180/PI << endl;
	
//	exit(0);


	cout << " ssssssss  " << x << "   " <<  m->phi/PI*180 << "   " << y << "    " << ll_pr  << "     " << 3 * PI/2 << "    " << (r->theta)/2/PI *360 << "    " << ll_pr*sin(3/2 * PI - r->theta) << "      " << ll_pr*cos(3/2 * PI - r->theta) << endl;




//	exit(0);


    
    if( y < m->Fy )
	s *= -1.0;

    stat->angle = phi*57.296;
    stat->s = s;
    stat->sum += s;
    stat->sumsqr += s*s;
    if( stat->n == 0.0 )
	stat->min = stat->max = s;
    stat->n++;
    if( s < stat->min )
	stat->min = s;
    if( s > stat->max )
	stat->max = s;



	cout << r->x << "    " <<  r->y << endl;
	cout << x << "    " << y << endl;
	


	c1->Update();
	


	double xx, yy;

	xx = 110;

	yy =  r->y + tan(3*PI/2 - r->theta) * (110 - r->x);  


	TGraph* traj = new TGraph();
  
  	traj->SetPoint(traj->GetN(), r->x, r->y);

 
 	traj->SetPoint(traj->GetN(), x, y);
 
 	traj->SetPoint(traj->GetN(), xx, yy);
  	
  	traj->SetLineStyle(2);
  		
  	traj->DrawClone("*C");
  	
    delete traj;





    if( fabs(s) <= PMT_SIZE )
       	{
//       	fprintf(out,"%f %f\n%f %f\njoin dots\n",(float)r->x,(float)r->y,(float)x,(float)y);
       	num_caught++;
       	return( 1 );
       	}
    else 
       	{
       	return( 0 );
       	}
}
