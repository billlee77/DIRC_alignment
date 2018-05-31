/* guess what, this function draws the mirror it is passed to the topdrawer
file. suprised ? */
#include "raytr.h"

//draw_mirror(m,out)
//MIRROR *m;





//void draw_mirror(Mirror &m, File *out) {

using namespace std;

void draw_mirror(MIRROR* m, TCanvas* c1) {



	cout << "    " << " I am here!! " << "  " << endl;

    double theta_m,dtheta,phi,theta,x,y;

	FILE   *out;

	cout << "1st corner " << m->X1x << "   " << m->X1y << endl;
	cout << "2nd corner " << m->X2x << "   " << m->X2y << endl;


	TGraph* g1 = new TGraph(); 

	TGraph* flat_mirror = new TGraph(); 

	TGraph* g_win_1 = new TGraph(); 




/* gh
     fprintf(out,"title ' 12st3 corner:  %4.0f,%4.0f; ",x1,yy1);
     fprintf(out,"22nd3 corner:  %4.0f,%4.0f; ",x2,y2);
     fprintf(out,"radius:  %4.0f; ",m->R);
     fprintf(out,"focal point:  %4.0f,%4.0f'\n",m->Fx,m->Fy); 
     fprintf(out,"case '  X  X                      X  X'\n");
*/

//      fprintf(out,"title ' 1st corner:  %4.0f,%4.0f; ",m->X1x,m->X1y);
//      fprintf(out,"2nd corner:  %4.0f,%4.0f; ",m->X2x,m->X2y);
//      fprintf(out,"radius:  %4.0f; ",m->R);
//      fprintf(out,"focal point:  %5.1f,%5.1f; ",m->Fx,m->Fy);
//      fprintf(out,"phi:   %4.0f'\n",m->phi*57.295);


	cout << "========== " << m->R  << endl;



    theta_m = 2.0*asin( 0.5*m->L/m->R );
    dtheta = theta_m / 10.0;
    phi = acos( (m->My-m->Cy)/m->R );

    if( (m->Mx-m->Cx) < 0.0 )
       phi = 2.0*PI - phi;
    for(theta = -theta_m; theta <= theta_m; theta += dtheta)
       {
       x = m->Cx + m->R*sin(theta+phi);
       y = m->Cy + m->R*cos(theta+phi);

		g1->SetPoint(g1->GetN(), x, y);
 
    	cout << x  << "   " << y << endl;

//       fprintf(out,"%f %f\n",x,y);
       }


//	g1->SetPoint(0, m->X1x, m->X1y);
//	g1->SetPoint(1, m->X2x, m->X2y);


 





    for( Int_t flat_itt = 80; flat_itt <= 140; flat_itt++ ){

        x = 10;
        y = flat_itt ;

		flat_mirror->SetPoint(flat_mirror->GetN(), x, y);
 
    }





    for(Int_t itt = 10; itt <= 50; itt++){

        x = 2;
        y = itt;

		g_win_1->SetPoint(g_win_1->GetN(), x, y);
 
    }




	g1->SetLineColor(2);
	flat_mirror->SetLineColor(2);


	g_win_1->SetMarkerColor(6);
	g_win_1->SetLineColor(6);
	g_win_1->SetLineWidth(6);






	g1->Draw("A*C");

	g1->GetYaxis()->SetRangeUser(-50,250);

	g1->GetXaxis()->SetLimits(-20, 125);

	g1->Draw("AC");
	
	c1->Update();

	flat_mirror->Draw("Csame");

	g_win_1->Draw("Csame");





	/*--------------------------------------------------*/
	/// Drawing PMT window

	TGraph* g_win = new TGraph(); 

//     for( Int_t win_itt = 0; win_itt <= 20; win_itt++ ){
// 
//         x = 80 + win_itt;
//         y = 220 - win_itt;
// 
// 		g_win->SetPoint(g_win->GetN(), x, y);
//  
//     }

 	g_win->SetPoint(g_win->GetN(), m->Fx - PMT_SIZE*sin(m->phi), m->Fy + PMT_SIZE*cos(m->phi));
 	g_win->SetPoint(g_win->GetN(), m->Fx + PMT_SIZE*sin(m->phi), m->Fy - PMT_SIZE*cos(m->phi));

	g_win->SetMarkerColor(3);
	g_win->SetLineColor(3);
	g_win->SetLineWidth(3);

	g_win->Draw("Csame");



//	exit(0);


//     fprintf(out,"join\n");
//     fprintf(out,"%f %f\n%f %f\njoin\n",
//           m->Fx + PMT_SIZE*sin(m->phi),m->Fy + PMT_SIZE*cos(m->phi),
//           m->Fx - PMT_SIZE*sin(m->phi),m->Fy - PMT_SIZE*cos(m->phi));
// /*
//     fprintf(out,"%f %f\n%f %f\njoin dash\n",
//           m->Fx + 14.0*sin(m->phi),m->Fy + 14.0*cos(m->phi),
//           m->Fx - 14.0*sin(m->phi),m->Fy - 14.0*cos(m->phi));
// */
//     fprintf(out,"symbol 4O\n%f %f\nplot\n",m->Fx,m->Fy);
// 


}


