/* guess what, this function draws the mirror it is passed to the topdrawer
file. suprised ? */
#include "raytr.h"

//draw_mirror(m,out)
//MIRROR *m;

//void draw_mirror(Mirror &m, File *out) {

using namespace std;

void draw_mirror(mirror_stats* m, TCanvas* c1) {

	cout << "    " << " I am here!! " << "  " << endl;

    Double_t theta_m,dtheta,phi,theta,x,y;

	FILE *out;

	/*--------------------------------------------------*/
	/// Define Composite Main Reflector

	TGraph* g1 = new TGraph(); 
	TGraph* g2 = new TGraph(); 
	TGraph* g3 = new TGraph(); 

	/*--------------------------------------------------*/
	/// Define Flat reflector

	TGraph* flat_mirror = new TGraph(); 

	/*--------------------------------------------------*/
	/// Define PMT window

	TGraph* g_win_1 = new TGraph(); 




// 	cout << "========== " << m->R  << endl;
// 
//     theta_m = 2.0*asin( 0.5*m->L/m->R );
//     dtheta = theta_m / 10.0;
//     phi = acos( (m->My-m->Cy)/m->R );
// 
//     if( (m->Mx-m->Cx) < 0.0 )
//        phi = 2.0*PI - phi;
//     for(theta = -theta_m; theta <= theta_m; theta += dtheta)
//        {
//        x = m->Cx + m->R*sin(theta+phi);
//        y = m->Cy + m->R*cos(theta+phi);
// 
// 		g1->SetPoint(g1->GetN(), x, y);
//  
//     	cout << x  << "   " << y << endl;
// 
// //       fprintf(out,"%f %f\n",x,y);
//        }


	/// global_offset_x =  2.5629;
	global_offset_x = 0.0;

	///*--------------------------------------------------*/
	/// 1.905 cm is the thickness of the back plate

    /// global_offset_y = 15.3484 - 1.88;

    global_offset_y = -1.905;



	/// Rotational center
	

	MIRROR_Miss* mirr_mis = new MIRROR_Miss;

 	mirr_mis->mis_x = 0.0;
 	mirr_mis->mis_y = 0.0;
 
//  	mirr_mis->rot_center_x = 10.3071  + global_offset_x - 0.2;
//  	mirr_mis->rot_center_y = 45.043 + global_offset_y;
//  	mirr_mis->rot_angle = 90;

	TGraph* fix_pin_gr = new TGraph(); 


 	mirr_mis->rot_center_x = 20.0;
 	mirr_mis->rot_center_y = 30.0;
 	mirr_mis->rot_angle    = 5;

	fix_pin_gr->SetPoint(0, mirr_mis->rot_center_x, mirr_mis->rot_center_y);


 	m->composite_mirror_dim->mirror_width = 9.6; 

	/*--------------------------------------------------*/
	/// Original composite mirror position
    //                   
 	// m->composite_mirror_dim->mirror_sub_1_x = 23.6414;
 	// m->composite_mirror_dim->mirror_sub_1_y =  0.3254;
 	// m->composite_mirror_dim->mirror_sub_1_angle = -22.893 * asin(1.0)/90;
 
 	// m->composite_mirror_dim->mirror_sub_2_x = 26.8245;
 	// m->composite_mirror_dim->mirror_sub_2_y = 9.3566;
 	// m->composite_mirror_dim->mirror_sub_2_angle = -15.98 * asin(1.0)/90;
 
 	// m->composite_mirror_dim->mirror_sub_3_x = 28.9044;
 	// m->composite_mirror_dim->mirror_sub_3_y = 18.7036;
 	// m->composite_mirror_dim->mirror_sub_3_angle = -9.067 * asin(1.0)/90;
 

 	 // m->composite_mirror_dim->mirror_sub_1_x = 23.6414 + global_offset_x;

 	 m->composite_mirror_dim->mirror_sub_1_x = 26.2043 + global_offset_x;

 	 // m->composite_mirror_dim->mirror_sub_1_y =  0.3254 + global_offset_y;
 	 m->composite_mirror_dim->mirror_sub_1_y =  15.6738 + global_offset_y;

 	 // m->composite_mirror_dim->mirror_sub_1_angle = - (22.893) * asin(1.0)/90;
 	 m->composite_mirror_dim->mirror_sub_1_angle = - (90-22.893) * asin(1.0)/90;

 	 // m->composite_mirror_dim->mirror_sub_2_x = 26.8245 + global_offset_x;
 	 m->composite_mirror_dim->mirror_sub_2_x = 29.3874 + global_offset_x;

 	 // m->composite_mirror_dim->mirror_sub_2_y = 9.3566 + global_offset_y;
 	 m->composite_mirror_dim->mirror_sub_2_y = 24.705 + global_offset_y;

 	 m->composite_mirror_dim->mirror_sub_2_angle = - (90 - 15.98) * asin(1.0)/90;
 
 	 // m->composite_mirror_dim->mirror_sub_3_x = 28.9044 + global_offset_x;

 	 m->composite_mirror_dim->mirror_sub_3_x = 31.4673 + global_offset_x;

// 	 m->composite_mirror_dim->mirror_sub_3_y = 18.7036 + global_offset_y;
 	 m->composite_mirror_dim->mirror_sub_3_y = 34.052 + global_offset_y;

 	 m->composite_mirror_dim->mirror_sub_3_angle = - (90 - 9.067) * asin(1.0)/90;
 
 	Double_t mirror_sub_1_x, mirror_sub_1_y, mirror_sub_1_angle; 
 	Double_t mirror_sub_2_x, mirror_sub_2_y, mirror_sub_2_angle; 
 	Double_t mirror_sub_3_x, mirror_sub_3_y, mirror_sub_3_angle; 
 	Double_t mirror_width;
 
 	mirror_width       = m->composite_mirror_dim->mirror_width;
 
 	mirror_sub_1_x     = m->composite_mirror_dim->mirror_sub_1_x     ;
    mirror_sub_1_y     = m->composite_mirror_dim->mirror_sub_1_y     ;
    mirror_sub_1_angle = m->composite_mirror_dim->mirror_sub_1_angle ;

    mirror_sub_2_x     = m->composite_mirror_dim->mirror_sub_2_x     ;
    mirror_sub_2_y     = m->composite_mirror_dim->mirror_sub_2_y     ;
    mirror_sub_2_angle = m->composite_mirror_dim->mirror_sub_2_angle ;
                    
    mirror_sub_3_x     = m->composite_mirror_dim->mirror_sub_3_x     ;
    mirror_sub_3_y     = m->composite_mirror_dim->mirror_sub_3_y     ;
    mirror_sub_3_angle = m->composite_mirror_dim->mirror_sub_3_angle ;


	///*--------------------------------------------------*/
	// Adjustment for the thinner mirror

	mirror_sub_1_x     = mirror_sub_1_x + 0.2 * cos( fabs(mirror_sub_2_angle) * asin(1.0)/90 );
	mirror_sub_1_y     = mirror_sub_1_y - 0.2 * sin( fabs(mirror_sub_2_angle) * asin(1.0)/90 );

	mirror_sub_2_x     = mirror_sub_2_x + 0.2 * cos( fabs(mirror_sub_2_angle) * asin(1.0)/90 );
	mirror_sub_2_y     = mirror_sub_2_y - 0.2 * sin( fabs(mirror_sub_2_angle) * asin(1.0)/90 );

	mirror_sub_3_x     = mirror_sub_3_x + 0.2 * cos( fabs(mirror_sub_2_angle) * asin(1.0)/90 );
	mirror_sub_3_y     = mirror_sub_3_y - 0.2 * sin( fabs(mirror_sub_2_angle) * asin(1.0)/90 );


	///*--------------------------------------------------*/
	// Drawing the mirror


	Double_t mirror_sub_1_x_start = mirror_sub_1_x - mirror_width/2*cos(mirror_sub_1_angle);
	Double_t mirror_sub_1_y_start = mirror_sub_1_y + mirror_width/2*sin(mirror_sub_1_angle);
	
	Double_t mirror_sub_1_x_end = mirror_sub_1_x + mirror_width/2*cos(mirror_sub_1_angle);
	Double_t mirror_sub_1_y_end = mirror_sub_1_y - mirror_width/2*sin(mirror_sub_1_angle);
	
	
	Double_t mirror_sub_1_x_start_mis = mirror_box_misalignment_x(mirror_sub_1_x_start, mirror_sub_1_y_start, mirr_mis);
	Double_t mirror_sub_1_y_start_mis = mirror_box_misalignment_y(mirror_sub_1_x_start, mirror_sub_1_y_start, mirr_mis);
	
	Double_t mirror_sub_1_x_end_mis = mirror_box_misalignment_x(mirror_sub_1_x_end, mirror_sub_1_y_end, mirr_mis);
	Double_t mirror_sub_1_y_end_mis = mirror_box_misalignment_y(mirror_sub_1_x_end, mirror_sub_1_y_end, mirr_mis);




	Double_t mirror_sub_2_x_start = mirror_sub_2_x - mirror_width/2*cos(mirror_sub_2_angle);
	Double_t mirror_sub_2_y_start = mirror_sub_2_y + mirror_width/2*sin(mirror_sub_2_angle);
	
	Double_t mirror_sub_2_x_end = mirror_sub_2_x + mirror_width/2*cos(mirror_sub_2_angle);
	Double_t mirror_sub_2_y_end = mirror_sub_2_y - mirror_width/2*sin(mirror_sub_2_angle);
	
	Double_t mirror_sub_2_x_start_mis = mirror_box_misalignment_x(mirror_sub_2_x_start, mirror_sub_2_y_start, mirr_mis);
	Double_t mirror_sub_2_y_start_mis = mirror_box_misalignment_y(mirror_sub_2_x_start, mirror_sub_2_y_start, mirr_mis);
	
	Double_t mirror_sub_2_x_end_mis = mirror_box_misalignment_x(mirror_sub_2_x_end, mirror_sub_2_y_end, mirr_mis);
	Double_t mirror_sub_2_y_end_mis = mirror_box_misalignment_y(mirror_sub_2_x_end, mirror_sub_2_y_end, mirr_mis);



	Double_t mirror_sub_3_x_start = mirror_sub_3_x - mirror_width/2*cos(mirror_sub_3_angle);
	Double_t mirror_sub_3_y_start = mirror_sub_3_y + mirror_width/2*sin(mirror_sub_3_angle);
	
	Double_t mirror_sub_3_x_end = mirror_sub_3_x + mirror_width/2*cos(mirror_sub_3_angle);
	Double_t mirror_sub_3_y_end = mirror_sub_3_y - mirror_width/2*sin(mirror_sub_3_angle);
	
	Double_t mirror_sub_3_x_start_mis = mirror_box_misalignment_x(mirror_sub_3_x_start, mirror_sub_3_y_start, mirr_mis);
	Double_t mirror_sub_3_y_start_mis = mirror_box_misalignment_y(mirror_sub_3_x_start, mirror_sub_3_y_start, mirr_mis);
	
	Double_t mirror_sub_3_x_end_mis = mirror_box_misalignment_x(mirror_sub_3_x_end, mirror_sub_3_y_end, mirr_mis);
	Double_t mirror_sub_3_y_end_mis = mirror_box_misalignment_y(mirror_sub_3_x_end, mirror_sub_3_y_end, mirr_mis);








//  	///*--------------------------------------------------*/
//  	/// Submirror #1
//  
//    	g1->SetPoint(g1->GetN(), mirror_sub_1_x - mirror_width/2*sin(mirror_sub_1_angle), mirror_sub_1_y + mirror_width/2*cos(mirror_sub_1_angle));
//  
//    	g1->SetPoint(g1->GetN(), mirror_sub_1_x + mirror_width/2*sin(mirror_sub_1_angle), mirror_sub_1_y - mirror_width/2*cos(mirror_sub_1_angle));
//  
//  	///*--------------------------------------------------*/
//  	/// Submirror #2
//  
//     g2->SetPoint(g2->GetN(), mirror_sub_2_x - mirror_width/2*sin(mirror_sub_2_angle), mirror_sub_2_y + mirror_width/2*cos(mirror_sub_2_angle));
//  
//     g2->SetPoint(g2->GetN(), mirror_sub_2_x + mirror_width/2*sin(mirror_sub_2_angle), mirror_sub_2_y - mirror_width/2*cos(mirror_sub_2_angle));
//  
//  	///*--------------------------------------------------*/
//  	/// Submirror #3
//  
//     g3->SetPoint(g3->GetN(), mirror_sub_3_x - mirror_width/2*sin(mirror_sub_3_angle), mirror_sub_3_y + mirror_width/2*cos(mirror_sub_3_angle));
//  
//     g3->SetPoint(g3->GetN(), mirror_sub_3_x + mirror_width/2*sin(mirror_sub_3_angle), mirror_sub_3_y - mirror_width/2*cos(mirror_sub_3_angle));










 	///*--------------------------------------------------*/
 	/// Submirror #1
 
   	g1->SetPoint(g1->GetN(), mirror_sub_1_x_start_mis, mirror_sub_1_y_start_mis);
 
   	g1->SetPoint(g1->GetN(), mirror_sub_1_x_end_mis, mirror_sub_1_y_end_mis);


	m->composite_mirror_dim->mirror_sub_1_x     = mirror_box_misalignment_x(mirror_sub_1_x, mirror_sub_1_y, mirr_mis); 
	m->composite_mirror_dim->mirror_sub_1_y     = mirror_box_misalignment_y(mirror_sub_1_x, mirror_sub_1_y, mirr_mis);
	m->composite_mirror_dim->mirror_sub_1_angle = mirror_sub_1_angle + mirr_mis->rot_angle*asin(1)/90;


 
 	///*--------------------------------------------------*/
 	/// Submirror #2
 
    g2->SetPoint(g2->GetN(), mirror_sub_2_x_start_mis, mirror_sub_2_y_start_mis);

    g2->SetPoint(g2->GetN(), mirror_sub_2_x_end_mis, mirror_sub_2_y_end_mis);

	m->composite_mirror_dim->mirror_sub_2_x     = mirror_box_misalignment_x(mirror_sub_2_x, mirror_sub_2_y, mirr_mis); 
	m->composite_mirror_dim->mirror_sub_2_y     = mirror_box_misalignment_y(mirror_sub_2_x, mirror_sub_2_y, mirr_mis);
	m->composite_mirror_dim->mirror_sub_2_angle = mirror_sub_2_angle + mirr_mis->rot_angle*asin(1)/90;

 
 	///*--------------------------------------------------*/
 	/// Submirror #3
 
    g3->SetPoint(g3->GetN(), mirror_sub_3_x_start_mis, mirror_sub_3_y_start_mis);
    g3->SetPoint(g3->GetN(),  mirror_sub_3_x_end_mis, mirror_sub_3_y_end_mis);

	m->composite_mirror_dim->mirror_sub_3_x     = mirror_box_misalignment_x(mirror_sub_3_x, mirror_sub_3_y, mirr_mis); 
	m->composite_mirror_dim->mirror_sub_3_y     = mirror_box_misalignment_y(mirror_sub_3_x, mirror_sub_3_y, mirr_mis);
	m->composite_mirror_dim->mirror_sub_3_angle = mirror_sub_3_angle + mirr_mis->rot_angle*asin(1)/90;







	//cout << mirror_sub_2_x + mirror_width*sin(mirror_sub_2_angle) << "     " << endl;






// 
//  	g_1->SetPoint(g_win->GetN(), m->Fx + PMT_SIZE*sin(m->phi), m->Fy - PMT_SIZE*cos(m->phi));
//  
// 
//  	g_2->SetPoint(g_win->GetN(), m->Fx - PMT_SIZE*sin(m->phi), m->Fy + PMT_SIZE*cos(m->phi));
//  	g_2->SetPoint(g_win->GetN(), m->Fx + PMT_SIZE*sin(m->phi), m->Fy - PMT_SIZE*cos(m->phi));
// 
// 
//  	g_2->SetPoint(g_win->GetN(), m->Fx - PMT_SIZE*sin(m->phi), m->Fy + PMT_SIZE*cos(m->phi));
//  	g_2->SetPoint(g_win->GetN(), m->Fx + PMT_SIZE*sin(m->phi), m->Fy - PMT_SIZE*cos(m->phi));

//	g1->SetPoint(0, m->X1x, m->X1y);
//	g1->SetPoint(1, m->X2x, m->X2y);









	/*--------------------------------------------------*/
	/// Flat mirrors


	cout << m->flat_mirror_dim->x_pos << endl;

	/// m->flat_mirror_dim->x_pos = 7.7442  + global_offset_x - 0.2;
	m->flat_mirror_dim->x_pos = 10.3071  + global_offset_x - 0.2;

//  	m->flat_mirror_dim->y_pos = 29.6946 + global_offset_y;
  	m->flat_mirror_dim->y_pos = 45.043 + global_offset_y;

  	m->flat_mirror_dim->width = 40.2    ;	
 
// 	m->flat_mirror_dim->angle = (180.0 ) * asin(1.0)/90  ;	

 	m->flat_mirror_dim->angle = (90.0 ) * asin(1.0)/90  ;	

//  	m->flat_mirror_dim->angle = (175.0 ) * asin(1.0)/90  ;	
   
  	Double_t flat_x_cen = m->flat_mirror_dim->x_pos;
  	Double_t flat_y_cen = m->flat_mirror_dim->y_pos;
  	Double_t flat_width = m->flat_mirror_dim->width;
  	Double_t flat_angle = m->flat_mirror_dim->angle;
  
 
 
//       for(Float_t flat_itt = flat_y_cen - flat_width/2; flat_itt <= flat_y_cen + flat_width/2; flat_itt = flat_itt + 0.1) {
//   
//           x = flat_x_cen;
//           y = flat_itt;
//   
//   		cout << x << "   " << y  << endl;
//   	
//   		flat_mirror->SetPoint(flat_mirror->GetN(), x, y);
//    
//       }
 

//	mirror_box_misalignment_x(flat_x_cen - flat_width/2*sin(flat_angle), flat_y_cen + flat_width/2*cos(flat_angle), mirr_mis);

	Double_t flat_x_start = flat_x_cen - flat_width/2*cos(flat_angle);
	Double_t flat_y_start = flat_y_cen + flat_width/2*sin(flat_angle);
 
	Double_t flat_x_end   = flat_x_cen + flat_width/2*cos(flat_angle);
	Double_t flat_y_end   = flat_y_cen - flat_width/2*sin(flat_angle);
 
	Double_t flat_x_start_mis = mirror_box_misalignment_x(flat_x_start, flat_y_start, mirr_mis);
	Double_t flat_y_start_mis = mirror_box_misalignment_y(flat_x_start, flat_y_start, mirr_mis);

	Double_t flat_x_end_mis = mirror_box_misalignment_x(flat_x_end, flat_y_end, mirr_mis);
	Double_t flat_y_end_mis = mirror_box_misalignment_y(flat_x_end, flat_y_end, mirr_mis);



  	flat_mirror->SetPoint(flat_mirror->GetN(), flat_x_start_mis, flat_y_start_mis);
  	flat_mirror->SetPoint(flat_mirror->GetN(), flat_x_end_mis, flat_y_end_mis);

	cout << endl;
	cout << "asdasdada  " << endl;
	cout << "asf     " <<  m->flat_mirror_dim->x_pos << endl;


	m->flat_mirror_dim->x_pos = mirror_box_misalignment_x(flat_x_cen, flat_y_cen, mirr_mis); 
	m->flat_mirror_dim->y_pos = mirror_box_misalignment_y(flat_x_cen, flat_y_cen, mirr_mis);
	m->flat_mirror_dim->angle = flat_angle + mirr_mis->rot_angle*asin(1)/90;
	
	cout << "asd    " <<  m->flat_mirror_dim->x_pos << endl;

	cout << " ++++++++++++++++++++++++ " << endl;

	cout << flat_x_start_mis << "   "  <<  flat_y_start_mis << endl;
	cout << flat_x_end_mis << "   "  <<  flat_y_end_mis << endl;


	cout << flat_angle << "     " << m->flat_mirror_dim->angle << endl;
	cout << " ++++++++++++++++++++++++ " << endl;

	flat_x_start = m->flat_mirror_dim->x_pos + flat_width/2*sin(m->flat_mirror_dim->angle);
	flat_y_start = m->flat_mirror_dim->y_pos + flat_width/2*cos(m->flat_mirror_dim->angle);
 
	flat_x_end   = m->flat_mirror_dim->x_pos - flat_width/2*sin(m->flat_mirror_dim->angle);
	flat_y_end   = m->flat_mirror_dim->y_pos - flat_width/2*cos(m->flat_mirror_dim->angle);

// 	flat_mirror->SetPoint(flat_mirror->GetN(), flat_x_start_mis, flat_y_start_mis);
// 	flat_mirror->SetPoint(flat_mirror->GetN(), flat_x_end_mis, flat_y_end_mis);

	
	cout << flat_x_start << "   "  <<  flat_y_start << endl;
	cout << flat_x_end << "   "  <<  flat_y_end << endl;

// 	flat_mirror->SetPoint(flat_mirror->GetN(), flat_x_start, flat_y_start);
// 	flat_mirror->SetPoint(flat_mirror->GetN(), flat_x_end  , flat_y_end);


	cout << " ++++++++++++++++++++++++ " << endl;

//	exit(0);


 
 	////*--------------------------------------------------*/
 	/// Drawing the Window
 	/// Window Width 
 
 	m->window_dim->x_pos = 2.5629  + global_offset_x ;
  	m->window_dim->y_pos = 15.3484  + global_offset_y;
  	m->window_dim->width = 12.0;	
  	m->window_dim->angle = 90.0 * asin(1.0)/90 ;	
    
  	Double_t win_x_cen = m->window_dim->x_pos;
  	Double_t win_y_cen = m->window_dim->y_pos;
  	Double_t win_width = m->window_dim->width;
 
 
 
 
 
     for(Float_t itt = win_y_cen - win_width/2; itt <= win_y_cen + win_width/2; itt = itt + 0.1){
 
         x = win_x_cen;
         y = itt;
 
 		g_win_1->SetPoint(g_win_1->GetN(), x, y);
  
     }

	g1->SetLineColor(4);
	g2->SetLineColor(4);
	g3->SetLineColor(4);

	flat_mirror->SetLineColor(2);

	g_win_1->SetMarkerColor(6);
	g_win_1->SetLineColor(6);
	g_win_1->SetLineWidth(1);

	g1->Draw("A*C");


	g1->GetXaxis()->SetLimits(-170, 60);

	g1->GetYaxis()->SetRangeUser(-200,110);

	g1->Draw("AC");

	g2->Draw("C");

	g3->Draw("C");

	c1->Update();

	flat_mirror->Draw("Csame");

	g_win_1->Draw("Csame");




	TGraph* g_origin = new TGraph();

	g_origin->SetPoint(0, 0, 0);

	g_origin->SetMarkerStyle(8);
	g_origin->SetMarkerSize(0.5);

	g_origin->Draw("p");
	

	fix_pin_gr->SetMarkerStyle(8);
	fix_pin_gr->SetMarkerSize(0.5);

	fix_pin_gr->Draw("p");




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




// 
//  	g_win->SetPoint(g_win->GetN(), m->Fx - PMT_SIZE*sin(m->phi), m->Fy + PMT_SIZE*cos(m->phi));
//  	g_win->SetPoint(g_win->GetN(), m->Fx + PMT_SIZE*sin(m->phi), m->Fy - PMT_SIZE*cos(m->phi));
// 



	
//	m->phi = 42.130 * asin(1.0)/90;
//	m->phi = 42.130 * asin(1.0)/90;


	double pmt_x, pmt_y, pmt_angle, PMT_window_width;	
	
//	m->pmt_window_dim->x_pos =  18.5099  + global_offset_x;

	m->pmt_window_dim->x_pos =  21.0728  + global_offset_x;

//  	m->pmt_window_dim->y_pos =  39.1432  + global_offset_y;

  	m->pmt_window_dim->y_pos =  54.4916  + global_offset_y;
//  	m->pmt_window_dim->angle =  42.130 * asin(1.0)/90 ;	

  	m->pmt_window_dim->angle =  (90 - 42.130) * asin(1.0)/90 ;	

  	m->pmt_window_dim->width =  39.4;	

	pmt_x            = m->pmt_window_dim->x_pos;
	pmt_y            = m->pmt_window_dim->y_pos; 
	pmt_angle        = m->pmt_window_dim->angle;
	PMT_window_width = m->pmt_window_dim->width;

 	g_win->SetPoint(g_win->GetN(), pmt_x - PMT_window_width/2*cos(pmt_angle), pmt_y + PMT_window_width/2*sin(pmt_angle));
 	g_win->SetPoint(g_win->GetN(), pmt_x + PMT_window_width/2*cos(pmt_angle), pmt_y - PMT_window_width/2*sin(pmt_angle));



	Double_t pmt_window_gradiate = -PMT_window_width*cos(pmt_angle) / PMT_window_width*sin(pmt_angle); 
	Double_t pmt_window_offset = pmt_y + PMT_window_width/2*cos(pmt_angle) - pmt_window_gradiate * (pmt_x - PMT_window_width/2*sin(pmt_angle)); 

	cout << "asdasd " << pmt_window_gradiate << "    " << pmt_window_offset << endl;
	
//	exit(0); 


	cout << pmt_x - PMT_window_width/2*sin(pmt_angle) << "   " << pmt_x - PMT_window_width/2*sin(pmt_angle) << endl;
	cout << reference_x << "   " << reference_y << endl;

//	exit(0);

	g_win->SetMarkerColor(3);
	g_win->SetLineColor(3);
	g_win->SetLineWidth(3);

	g_win->Draw("Csame");

	////*--------------------------------------------------*/
	/// Drawing horizontal Side Window

	TGraph* g_h_side_mirror = new TGraph();

	// m->side_honrizontal_mirror_dim->x_pos = 10.6250  + global_offset_x ;
	m->side_honrizontal_mirror_dim->x_pos = 13.1879  + global_offset_x;

    // m->side_honrizontal_mirror_dim->y_pos = -4.2042  + global_offset_y - 0.2;
	m->side_honrizontal_mirror_dim->y_pos = 11.1442 + global_offset_y - 0.2;

	m->side_honrizontal_mirror_dim->width = 18.560;
	m->side_honrizontal_mirror_dim->angle = 0.0 * asin(1.0)/90 ;

	Double_t h_side_x     = m->side_honrizontal_mirror_dim->x_pos;
	Double_t h_side_y     = m->side_honrizontal_mirror_dim->y_pos;
	Double_t h_side_width = m->side_honrizontal_mirror_dim->width; 
	Double_t h_side_angle = m->side_honrizontal_mirror_dim->angle; 


	Double_t h_side_x_start = h_side_x - h_side_width/2*cos(h_side_angle);
	Double_t h_side_y_start = h_side_y + h_side_width/2*sin(h_side_angle);
 
	Double_t h_side_x_end = h_side_x + h_side_width/2*cos(h_side_angle);
	Double_t h_side_y_end = h_side_y - h_side_width/2*sin(h_side_angle);
 
	Double_t h_side_x_start_mis = mirror_box_misalignment_x(h_side_x_start, h_side_y_start, mirr_mis);
	Double_t h_side_y_start_mis = mirror_box_misalignment_y(h_side_x_start, h_side_y_start, mirr_mis);

	Double_t h_side_x_end_mis = mirror_box_misalignment_x(h_side_x_end, h_side_y_end, mirr_mis);
	Double_t h_side_y_end_mis = mirror_box_misalignment_y(h_side_x_end, h_side_y_end, mirr_mis);




 	g_h_side_mirror->SetPoint(g_h_side_mirror->GetN(), h_side_x_start_mis, h_side_y_start_mis);
 	g_h_side_mirror->SetPoint(g_h_side_mirror->GetN(), h_side_x_end_mis, h_side_y_end_mis);

	g_h_side_mirror->Draw("Csame");


	m->side_honrizontal_mirror_dim->x_pos = mirror_box_misalignment_x(h_side_x, h_side_y, mirr_mis); 
	m->side_honrizontal_mirror_dim->y_pos = mirror_box_misalignment_y(h_side_x, h_side_y, mirr_mis);
	m->side_honrizontal_mirror_dim->angle = h_side_angle + mirr_mis->rot_angle*asin(1)/90;







	/*--------------------------------------------------*/
	/// Calculating the reference point

	// reference_x = 9.3215 + global_offset_x;
	reference_x = 11.8844 + global_offset_x;

	// reference_y = 53.0805 + global_offset_y;
	reference_y = 68.4289 + global_offset_y;

	TString coordinate;
	coordinate.Form("(%0.4f, %0.4f)", reference_x, reference_y);

	TText *t1 = new TText();

	t1->SetTextColor(2);

	t1->SetTextSize(0.02);
	t1->DrawText( reference_x +1, reference_y +1, coordinate);


	TGraph * g_ref = new TGraph();
	
	g_ref->SetPoint(0, reference_x, reference_y);

	g_ref->SetMarkerColor(2);

	g_ref->Draw("*");

	
	Double_t ref_gradiate = (- 1 / pmt_window_gradiate); 
	Double_t ref_offset =  reference_y -reference_x * ref_gradiate; 

	Double_t inter_x = - (pmt_window_offset- ref_offset)/ (pmt_window_gradiate - ref_gradiate);

	Double_t inter_y = inter_x* ref_gradiate +  ref_offset;


	cout << pmt_window_gradiate << "     " << ref_gradiate << "    " << pmt_window_offset << "    " << ref_offset << "   " << inter_x << "    " << inter_y << endl;

//	Double_t separation = inter_x


//	exit(0);



	////*--------------------------------------------------*/
	/// Drawing angled Side Window

	TGraph* g_a_side_mirror = new TGraph();

	m->side_reflector_dim->angle  = 150.0 * asin(1.0)/90;
	m->side_reflector_dim->width  = 6.6560;              

	/// m->side_reflector_dim->x_pos  = 4.5446 + global_offset_x - 0.2 * sin(m->side_reflector_dim->angle - asin(1.0));
	m->side_reflector_dim->x_pos  = 7.1075 + global_offset_x - 0.2 * sin(m->side_reflector_dim->angle - asin(1.0));

	// m->side_reflector_dim->y_pos  = 7.0287 + global_offset_y + 0.2 * cos(m->side_reflector_dim->angle - asin(1.0));
	m->side_reflector_dim->y_pos  = 22.3771 + global_offset_y + 0.2 * cos(m->side_reflector_dim->angle - asin(1.0));

	Double_t a_side_x     = m->side_reflector_dim->x_pos;
	Double_t a_side_y     = m->side_reflector_dim->y_pos;
	Double_t a_angle      = m->side_reflector_dim->angle;
	Double_t a_side_width = m->side_reflector_dim->width;              

//     m->Fx - PMT_SIZE*sin(m->phi), m->Fy + PMT_SIZE*cos(m->phi)
//     m->Fx + PMT_SIZE*sin(m->phi), m->Fy - PMT_SIZE*cos(m->phi)

	Double_t a_side_x_start = a_side_x - a_side_width/2*cos(a_angle);
	Double_t a_side_y_start = a_side_y + a_side_width/2*sin(a_angle);
 
	Double_t a_side_x_end = a_side_x + a_side_width/2*cos(a_angle);
	Double_t a_side_y_end = a_side_y - a_side_width/2*sin(a_angle);
 
	Double_t a_side_x_start_mis = mirror_box_misalignment_x(a_side_x_start, a_side_y_start, mirr_mis);
	Double_t a_side_y_start_mis = mirror_box_misalignment_y(a_side_x_start, a_side_y_start, mirr_mis);

	Double_t a_side_x_end_mis = mirror_box_misalignment_x(a_side_x_end, a_side_y_end, mirr_mis);
	Double_t a_side_y_end_mis = mirror_box_misalignment_y(a_side_x_end, a_side_y_end, mirr_mis);

 	g_a_side_mirror->SetPoint(g_a_side_mirror->GetN(), a_side_x_start_mis, a_side_y_start_mis);

 	g_a_side_mirror->SetPoint(g_a_side_mirror->GetN(), a_side_x_end_mis, a_side_y_end_mis);

	m->side_reflector_dim->x_pos = mirror_box_misalignment_x(a_side_x, a_side_y, mirr_mis); 
	m->side_reflector_dim->y_pos = mirror_box_misalignment_y(a_side_x, a_side_y, mirr_mis);
	m->side_reflector_dim->angle = a_angle + mirr_mis->rot_angle*asin(1)/90;

	g_a_side_mirror->Draw("Csame");

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







 
// void mirror_box_misalignment(Double_t mis_x, Double_t mis_y, Double_t rot_x, Double_t rot_y, Double_t angle) {
Double_t mirror_box_misalignment_x (Double_t mirror_cor_x, Double_t mirror_cor_y, MIRROR_Miss* mis_cor) {


	cout << mis_cor->mis_x << "    " << mis_cor->mis_y << "   " << mis_cor->rot_center_x << "  " << mis_cor->rot_center_y << "   " << mis_cor->rot_angle << endl;

//	cout << rot_x << "    " << rot_y << "   " << angle << endl;

	/// Rotation matrix
	///  x1 = cos(theta), x2 = -sin(theta)
	///  y1 = sin(theta), y2 =  cos(theta)

	mirror_cor_x = mirror_cor_x - mis_cor->rot_center_x;
	mirror_cor_y = mirror_cor_y - mis_cor->rot_center_y;

	Double_t theta = mis_cor->rot_angle * asin(1.0)/90;

   Double_t x1 =  cos(theta);
   Double_t x2 = -sin(theta);
   Double_t y1 =  sin(theta);
   Double_t y2 =  cos(theta);

	Double_t x_after_rot = mirror_cor_x*x1 + mirror_cor_y*y1;



	cout << mirror_cor_x << "   " << x1<<  "  "<< y1  << "   " << x_after_rot << endl;

//	exit(0);

	return x_after_rot + mis_cor->rot_center_x; 

}

 


// void mirror_box_misalignment(Double_t mis_x, Double_t mis_y, Double_t rot_x, Double_t rot_y, Double_t angle) {
Double_t mirror_box_misalignment_y (Double_t mirror_cor_x, Double_t mirror_cor_y, MIRROR_Miss* mis_cor) {


//	cout << mis_cor->mis_x << "    " << mis_cor->mis_y << "   " << mis_cor->rot_center_x << "  " << mis_cor->rot_center_y << "   " << mis_cor->rot_angle << endl;

//	cout << rot_x << "    " << rot_y << "   " << angle << endl;

	/// Rotation matrix
	///  x1 = cos(theta), x2 = -sin(theta)
	///  y1 = sin(theta), y2 =  cos(theta)

	mirror_cor_x = mirror_cor_x - mis_cor->rot_center_x;
	mirror_cor_y = mirror_cor_y - mis_cor->rot_center_y;



	Double_t theta = mis_cor->rot_angle * asin(1.0)/90;

    Double_t x1 =  cos(theta);
   Double_t x2 = -sin(theta);
   Double_t y1 =  sin(theta);
   Double_t y2 =  cos(theta);

	Double_t y_after_rot = mirror_cor_x*x2 + mirror_cor_y*y2;

	cout << mirror_cor_y << "   " << x1<<  "  "<< y1  << "   " << y_after_rot << endl;

//	exit(0);




	return y_after_rot +  mis_cor->rot_center_y;

}


