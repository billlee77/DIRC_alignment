/* not so much as reposition focal point as reposition the PMT */
#include "raytr.h"

reposition_fpoint(m,sts)
MIRROR *m;
STATS  *sts;
{
	double Fx,Fy,r,s,psi,Fxp,Fyp;

	Fx = m->Fx - m->Mx;	/* translate origin to M, the point 	*/
	Fy = m->Fy - m->My;	/* about which to rotate		*/
	r = hypot(Fx,Fy);
	s = sts->sum/sts->n;
	psi = 2.0*asin(0.5*s/r);
	Fxp =   Fx*cos(psi)  +  Fy*sin(psi);  /* rotate */
	Fyp =  -Fx*sin(psi)  +  Fy*cos(psi);
	m->Fx = Fxp + m->Mx;	/* translate to original origin		*/
	m->Fy = Fyp + m->My;
	m->phi += psi;
}

