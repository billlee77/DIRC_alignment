/* Second reflector	*/

#include "raytr.h"

using namespace std;

int flat_reflect( mirror_stats* m, RAY* r, TCanvas* c1) {


// 
 	cout << reference_x << "   " << reference_y << endl;

//	exit(0);


	///*--------------------------------------------------*/
	/// Reflect off the first mirror

     double dx,dy,x,y,b,c,dis,t1,t2,nx,ny,phi;




	///*--------------------------------------------------*/
	//  Starting point of the ray tracing

  	TGraph* traj = new TGraph();
  	traj->SetPoint(traj->GetN(), r->x, r->y);
 
	cout << "/*--------------------------------------------------*/" << endl;
	cout << "Tracing Started: " << endl;
	cout << r->x << "   " << r->y << "    " << r->theta << endl;
	cout << x << "   " << y << "    " << r->theta << endl;
 

	Float_t angle = r->theta*90/asin(1); 

	TString coordinate1;
	coordinate1.Form("(%0.2f, %0.2f)  %0.2f", r->x, r->y, angle);
	
	TText *tt = new TText();

	tt->SetTextSize(0.015);
	tt->DrawText(r->x+4, r->y, coordinate1);


	///*--------------------------------------------------*/
	// Reflecting the side flat mirror

// 	x = m->flat_mirror_dim->x_pos;
// 	y = r->y - tan(-r->theta)* (r->x - x);
// 
//  	r->x = x;   
//  	r->y = y;   
//  	r->theta = PI/2 + abs(r->theta) + PI/2;   

	cout << " check 1:  " << r->x << "    " << r->y << endl;

    long_flat_mirror_reflect(m->flat_mirror_dim->x_pos, m->flat_mirror_dim->y_pos, m->flat_mirror_dim->angle, r);

	cout << " mirror:  " << m->flat_mirror_dim->x_pos << "    " << m->flat_mirror_dim->y_pos << endl;
	cout << " check 2:  " << r->x << "    " << r->y << endl;

//	exit(0);

	traj->SetPoint(traj->GetN(), r->x, r->y);

 	cout << "Angle " << r->theta << "  " << r->theta - 0.5*PI << endl;
 
	///*--------------------------------------------------*/
	// Which of the composite mirror?

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



 	if (fitting_mirror_flat_mirror(mirror_sub_1_x, mirror_sub_1_y, mirror_sub_1_angle, mirror_width, r)) {
 		
 		cout << "mirror 1 reflect " << endl;
 		composite_mirror_reflect_mod(mirror_sub_1_x, mirror_sub_1_y, mirror_sub_1_angle, r);
 
 	} else if (fitting_mirror_flat_mirror(mirror_sub_2_x, mirror_sub_2_y, mirror_sub_2_angle, mirror_width, r)) {

		cout << "mirror 2 reflect " << endl;
		composite_mirror_reflect_mod(mirror_sub_2_x, mirror_sub_2_y, mirror_sub_2_angle, r);

		cout << "mirror 2 exit" << endl;

//		exit(0);
		

	} else if (fitting_mirror_flat_mirror(mirror_sub_3_x, mirror_sub_3_y, mirror_sub_3_angle, mirror_width, r)) {

		cout << "mirror 3 reflect " << endl;
		composite_mirror_reflect_mod(mirror_sub_3_x, mirror_sub_3_y, mirror_sub_3_angle, r);

	}

  	traj->SetPoint(traj->GetN(), r->x, r->y);
	
	///*--------------------------------------------------*/	
	// Double reflection on the flat mirror

	cout << "Angle : :::    " << r->theta << "      " << (r->theta)*90.0/asin(1) << endl;
		
	cout << fitting_mirror(m->flat_mirror_dim->x_pos, m->flat_mirror_dim->y_pos, m->flat_mirror_dim->angle, m->flat_mirror_dim->width, r) << endl;

	if(fitting_mirror(m->flat_mirror_dim->x_pos, m->flat_mirror_dim->y_pos, m->flat_mirror_dim->angle, m->flat_mirror_dim->width, r)) {

		cout << "double refection" << endl;
	
		x = m->flat_mirror_dim->x_pos;
		y = r->y - tan(-r->theta)* (r->x - x);

 	 	traj->SetPoint(traj->GetN(), r->x, r->y);
  		traj->SetPoint(traj->GetN(), x, y);

		r->x = x;   
		r->y = y;   
		r->theta = PI/2 + fabs(r->theta) + PI/2;   

//		exit(0);

		if (fitting_mirror(mirror_sub_1_x, mirror_sub_1_y, mirror_sub_1_angle, mirror_width, r)) {
		
			cout << "mirror 1 reflect " << endl;
			composite_mirror_reflect(mirror_sub_1_x, mirror_sub_1_y, mirror_sub_1_angle, r);

		} else if (fitting_mirror(mirror_sub_2_x, mirror_sub_2_y, mirror_sub_2_angle, mirror_width, r)) {

			cout << "mirror 2 reflect " << endl;

			composite_mirror_reflect(mirror_sub_2_x, mirror_sub_2_y, mirror_sub_2_angle, r);

		} else if (fitting_mirror(mirror_sub_3_x, mirror_sub_3_y, mirror_sub_3_angle, mirror_width, r)) {

			cout << "mirror 3 reflect " << endl;

			composite_mirror_reflect(mirror_sub_3_x, mirror_sub_3_y, mirror_sub_3_angle, r);

		}

  		traj->SetPoint(traj->GetN(), r->x, r->y);




	}







	///*--------------------------------------------------*/
	/// Reflect off the side mirror
	Double_t a_side_x     =  m->side_reflector_dim->x_pos  ;
	Double_t a_side_y     =  m->side_reflector_dim->y_pos  ;
	Double_t a_angle      =  m->side_reflector_dim->angle  ;
	Double_t a_side_width =  m->side_reflector_dim->width  ;

	if (fitting_mirror_flat_mirror(a_side_x, a_side_y, a_angle, a_side_width, r)) {

		cout << "Reflecting off the side mirror" << endl;
		side_flat_mirror_reflect(a_side_x, a_side_y, a_angle, r);

  		traj->SetPoint(traj->GetN(), r->x, r->y);

	} else {

		cout << "Did not hit the side angled mirror." << endl;

	}

//	exit(0);



	///*--------------------------------------------------*/
	/// Reflect off the honrizontal mirror
	Double_t h_x     =  m->side_honrizontal_mirror_dim->x_pos  ;
	Double_t h_y     =  m->side_honrizontal_mirror_dim->y_pos  ;
	Double_t h_angle      =  m->side_honrizontal_mirror_dim->angle  ;
	Double_t h_side_width =  m->side_honrizontal_mirror_dim->width  ;

	if (fitting_mirror_flat_mirror(h_x, h_y, h_angle, h_side_width, r)) {

		cout << "Reflecting off the side mirror" << endl;

// 		y = h_y;
// 		x = r->x - (1/tan(-r->theta))* (r->y - y);
// 
// 		r->x = x;   
// 		r->y = y;   
// 
// 		r->theta = PI/2 - (PI/2 - abs(r->theta)) ;   
// 
// 		cout << r->theta * 90/asin(1) << endl;

 
		cout << "Horizontal mirror: " << endl;  

		side_flat_mirror_reflect(h_x, h_y, h_angle, r);

 		traj->SetPoint(traj->GetN(), r->x, r->y);

		cout << "exiting ? " << endl;
//		exit(0);

	} 



//	exit(0);










	///*--------------------------------------------------*/
	/// Reflect to the window

	
// 	x = 0.0;
// 	y = r->y - tan(-r->theta)* (r->x-0.0);
// 
//  	traj->SetPoint(traj->GetN(), x, y);
// 
// 
// 	cout << "cccccc   " << r->theta * 90 / asin(1) << endl; 








	/*--------------------------------------------------*/
	/// far projection
	

	x = -157.8;
	y = r->y - tan(-r->theta)* (r->x - x);

 	traj->SetPoint(traj->GetN(), x, y);


	cout << "cccccc   " << r->theta * 90 / asin(1) << endl; 




  	traj->SetLineStyle(2);
  		
  	traj->DrawClone("*l");




	TString coordinate;
	coordinate.Form("(%0.2f, %0.2f)", x, y);

	
	TText *t = new TText();

	t->SetTextSize(0.02);
	t->DrawText(x+5, y-1, coordinate);



	
    delete traj;

	return 1;


}











/*--------------------------------------------------*/

bool fitting_mirror(Double_t mirror_sub_2_x, Double_t mirror_sub_2_y, Double_t mirror_sub_2_angle, Double_t mirror_width, RAY* r) {

//	Double_t mirror_width;
//	mirror_width = 9.6/2;

	Double_t mid_h_edge, mid_l_edge;
	Double_t h_mid_h_edge, h_mid_l_edge;
	Double_t m_mid_h_edge_x, m_mid_h_edge_y, m_mid_l_edge_x, m_mid_l_edge_y;
	Double_t l_mid_h_edge, l_mid_l_edge;

	m_mid_l_edge_x = mirror_sub_2_x - mirror_width/2*sin(mirror_sub_2_angle);
	m_mid_l_edge_y = mirror_sub_2_y + mirror_width/2*cos(mirror_sub_2_angle);

	m_mid_h_edge_x = mirror_sub_2_x + mirror_width/2*sin(mirror_sub_2_angle);
	m_mid_h_edge_y = mirror_sub_2_y - mirror_width/2*cos(mirror_sub_2_angle);

	


	cout << endl;

	cout << "Ray position: " << r->x << "    " << r-> y << endl;
	cout << mirror_sub_2_angle <<  "    " << mirror_sub_2_angle * 90/asin(1) << "    " << mirror_sub_2_y  << "    " << m_mid_h_edge_y<< endl;
	cout << "Mirror position: " << m_mid_l_edge_x << "    " << m_mid_l_edge_y << "    " << m_mid_h_edge_x << "     " << m_mid_h_edge_y << endl;
	

	Double_t diff_ll_h, diff_x_h, diff_y_h;
	Double_t diff_ll_l, diff_x_l, diff_y_l;
	Double_t diff_angle_h;
	Double_t diff_angle_l;


	if ( r->theta*90/asin(1) > 180 && r->theta*90/asin(1) < 270 ) {

		diff_x_l =  r->x - m_mid_l_edge_x;
		diff_y_l =  r->y - m_mid_l_edge_y;
		diff_ll_l = sqrt(diff_x_l * diff_x_l + diff_y_l * diff_y_l);
		diff_angle_l = asin(diff_y_l/diff_ll_l) + PI;


		diff_x_h =  r->x - m_mid_h_edge_x;
		diff_y_h =  r->y - m_mid_h_edge_y;
		diff_ll_h = sqrt(diff_x_h * diff_x_h + diff_y_h * diff_y_h);
		diff_angle_h = asin(diff_y_h/diff_ll_h) + PI;

	} else if (r->theta*90/asin(1) > -90 && r->theta*90/asin(1) < 0) {


// 		if ( m_mid_h_edge_x > r->x) {
// 			diff_x_l  =   m_mid_l_edge_x + r->x;
// 		} else {
// 			diff_x_l  =   m_mid_l_edge_x - r->x;
// 		}
// 

		diff_x_l  =   m_mid_l_edge_x - r->x;

		diff_y_l  = m_mid_l_edge_y - r->y ;



		diff_ll_l = sqrt(diff_x_l * diff_x_l + diff_y_l * diff_y_l);
		diff_angle_l = asin(diff_y_l/diff_ll_l);


// 		if ( m_mid_h_edge_x > r->x) {
// 			diff_x_h  =   m_mid_h_edge_x + r->x;
// 		} else {
// 			diff_x_h  =   m_mid_h_edge_x - r->x;
// 		}
// 

 		diff_x_h  =   m_mid_h_edge_x - r->x;

		diff_y_h  =   m_mid_h_edge_y - r->y;
		diff_ll_h = sqrt(diff_x_h * diff_x_h + diff_y_h * diff_y_h);
		diff_angle_h = asin(diff_y_h/diff_ll_h);

		cout << "xxooxx  " << diff_x_h << "   " << diff_y_h << "   "  << diff_x_l << "   " << diff_y_l << "   " << m_mid_l_edge_x << "    " << m_mid_h_edge_x << "   "<< r->x << "    " << r->y  << endl;


//		if ()



		cout << "Angle: " << diff_angle_l * 90.0 / asin(1) << "    " << diff_angle_h * 90.0/ asin(1) << endl;

		
//  		if ( m_mid_h_edge_x > r->x) {
// 			
// 			diff_angle_h = -PI + abs(diff_angle_h);
// 
// 		} 



		cout << "Angle: " << diff_angle_l * 90.0 / asin(1) << "    " << diff_angle_h * 90.0/ asin(1) << endl;


    
	} else if ((r->theta*90/asin(1) < 90 && r->theta*90/asin(1) > 0) ) {


		diff_x_l = m_mid_l_edge_x - r->x;
		diff_y_l = m_mid_l_edge_y - r->y;
		diff_ll_l = sqrt(diff_x_l * diff_x_l + diff_y_l * diff_y_l);
		diff_angle_l = asin(diff_y_l/diff_ll_l);


		diff_x_h =  m_mid_h_edge_x - r->x;
		diff_y_h =  m_mid_h_edge_y - r->y  ;
		diff_ll_h = sqrt(diff_x_h * diff_x_h + diff_y_h * diff_y_h);
		diff_angle_h = asin(diff_y_h/diff_ll_h);


		cout << "AAAAngle: " << diff_angle_l * 90.0 / asin(1) << "    " << diff_angle_h * 90.0/ asin(1) << endl;

	}


	if (m_mid_h_edge_x > r->x && m_mid_l_edge_x < r->x) {

		diff_angle_h = -PI + fabs(diff_angle_h);
		
	}
	
	cout << "ooxx  " << diff_x_h << "   " << diff_y_h << "   "  << diff_x_l << "   " << diff_y_l << "   " << m_mid_l_edge_x << "    " << m_mid_l_edge_y << "    " << m_mid_h_edge_x << "   " << m_mid_h_edge_y << "   " << r->x << "    " << r->y  << endl;

	cout << "Check reflection angle:   "  << diff_angle_l*90/asin(1) << "      " <<  diff_angle_h*90/asin(1)  << "    "  << r->theta << "      "<< r->theta * 90/asin(1) << endl;

//	cout << ">>>>>>>>>>>>   ????????? " << endl;

	if (diff_angle_l < 0 && diff_angle_h <0 && diff_angle_l > diff_angle_h) {

		Double_t temp_l = diff_angle_l;

		diff_angle_l = diff_angle_h;

		diff_angle_h = temp_l;

//		cout << ">>>>>>>>>>>>   ????????? " << endl;

	}





	bool within_mirror = false;

	if (r->theta*90/asin(1) > diff_angle_l*90/asin(1) && r->theta*90/asin(1) < diff_angle_h*90/asin(1)) {

		within_mirror = true;

		cout << "here???? " << endl;

	} else {

		within_mirror = false;

	}

	return within_mirror;

} 



/*--------------------------------------------------*/

bool fitting_mirror_flat_mirror(Double_t mirror_sub_2_x, Double_t mirror_sub_2_y, Double_t mirror_sub_2_angle, Double_t mirror_width, RAY* r) {

//	Double_t mirror_width;
//	mirror_width = 9.6/2;

	Double_t mid_h_edge, mid_l_edge;
	Double_t h_mid_h_edge, h_mid_l_edge;
	Double_t m_mid_h_edge_x, m_mid_h_edge_y, m_mid_l_edge_x, m_mid_l_edge_y;
	Double_t l_mid_h_edge, l_mid_l_edge;

	m_mid_l_edge_x = mirror_sub_2_x - mirror_width/2*cos(mirror_sub_2_angle);
	m_mid_l_edge_y = mirror_sub_2_y + mirror_width/2*sin(mirror_sub_2_angle);

	m_mid_h_edge_x = mirror_sub_2_x + mirror_width/2*cos(mirror_sub_2_angle);
	m_mid_h_edge_y = mirror_sub_2_y - mirror_width/2*sin(mirror_sub_2_angle);

	
	cout << endl;

	cout << "Ray position: " << r->x << "    " << r-> y << "    " <<  r->theta*90/asin(1) << endl;
	cout << mirror_sub_2_angle <<  "    " << mirror_sub_2_angle * 90/asin(1) << "    " << mirror_sub_2_y  << "    " << m_mid_h_edge_y<< endl;
	cout << "Mirror position: " << m_mid_l_edge_x << "    " << m_mid_l_edge_y << "    " << m_mid_h_edge_x << "     " << m_mid_h_edge_y << endl;

	cout << endl;


	Double_t diff_ll_h, diff_x_h, diff_y_h;
	Double_t diff_ll_l, diff_x_l, diff_y_l;
	Double_t diff_angle_h;
	Double_t diff_angle_l;



	if ( r->theta*90/asin(1) > 180 && r->theta*90/asin(1) < 270 ) {

		diff_x_l =  r->x - m_mid_l_edge_x;
		diff_y_l =  r->y - m_mid_l_edge_y;
		diff_ll_l = sqrt(diff_x_l * diff_x_l + diff_y_l * diff_y_l);
		diff_angle_l = asin(diff_y_l/diff_ll_l) + PI;


		diff_x_h =  r->x - m_mid_h_edge_x;
		diff_y_h =  r->y - m_mid_h_edge_y;
		diff_ll_h = sqrt(diff_x_h * diff_x_h + diff_y_h * diff_y_h);
		diff_angle_h = asin(diff_y_h/diff_ll_h) + PI;

		cout << "xxooxxl:  " << diff_x_h << "   " << diff_y_h << "   "  << diff_x_l << "   " << diff_y_l << "   " << m_mid_l_edge_x << "    " << m_mid_h_edge_x << "   "<< r->x << "    " << r->y  << endl;

		cout << "aaaaaa Angle: " << diff_angle_l * 90.0 / asin(1) << "    " << diff_angle_h * 90.0/ asin(1) << endl;



	} else if ((r->theta*90/asin(1) > -90 && r->theta*90/asin(1) < 0) || (r->theta*90/asin(1) < 360 && r->theta*90/asin(1) > 270) ) {

		diff_x_l  =   m_mid_l_edge_x - r->x;

		diff_y_l  = m_mid_l_edge_y - r->y ;

		diff_ll_l = sqrt(diff_x_l * diff_x_l + diff_y_l * diff_y_l);
		diff_angle_l = asin(diff_y_l/diff_ll_l);

 		diff_x_h  =   m_mid_h_edge_x - r->x;

		diff_y_h  =   m_mid_h_edge_y - r->y;
		diff_ll_h = sqrt(diff_x_h * diff_x_h + diff_y_h * diff_y_h);
		diff_angle_h = asin(diff_y_h/diff_ll_h);

		cout << "xxooxxl:  " << diff_x_h << "   " << diff_y_h << "   "  << diff_x_l << "   " << diff_y_l << "   " << m_mid_l_edge_x << "    " << m_mid_h_edge_x << "   "<< r->x << "    " << r->y  << endl;

		cout << "Angle: " << diff_angle_l * 90.0 / asin(1) << "    " << diff_angle_h * 90.0/ asin(1) << endl;
    
	} else if ((r->theta*90/asin(1) < 90 && r->theta*90/asin(1) > 0)) {

		diff_x_l = m_mid_l_edge_x - r->x;
		diff_y_l = m_mid_l_edge_y - r->y;
		diff_ll_l = sqrt(diff_x_l * diff_x_l + diff_y_l * diff_y_l);
		diff_angle_l = asin(diff_y_l/diff_ll_l);

		diff_x_h =  m_mid_h_edge_x - r->x;
		diff_y_h =  m_mid_h_edge_y - r->y  ;
		diff_ll_h = sqrt(diff_x_h * diff_x_h + diff_y_h * diff_y_h);
		diff_angle_h = asin(diff_y_h/diff_ll_h);

		cout << "aaaaaa Angle: " << diff_angle_l * 90.0 / asin(1) << "    " << diff_angle_h * 90.0/ asin(1) << endl;

	}


	if (m_mid_h_edge_x > r->x && m_mid_l_edge_x < r->x) {

		diff_angle_h = -PI + fabs(diff_angle_h);
		
	}
	
	cout << "ooxx  " << diff_x_h << "   " << diff_y_h << "   "  << diff_x_l << "   " << diff_y_l << "   " << m_mid_l_edge_x << "    " << m_mid_l_edge_y << "    " << m_mid_h_edge_x << "   " << m_mid_h_edge_y << "   " << r->x << "    " << r->y  << endl;

	cout << "Check reflection angle:   "  << diff_angle_l*90/asin(1) << "      " <<  diff_angle_h*90/asin(1)  << "    "  << r->theta << "      "<< r->theta * 90/asin(1) << endl;

//	cout << ">>>>>>>>>>>>   ????????? " << endl;


	///*--------------------------------------------------*/
	/// Switching diff_angle_l and diff_angle_h in case diff_angle_l is larger than diff_angle_h

	// if (diff_angle_l < 0 && diff_angle_h <0 && diff_angle_l > diff_angle_h) {
	if (diff_angle_l > diff_angle_h) {

		Double_t temp_l = diff_angle_l;

		diff_angle_l = diff_angle_h;

		diff_angle_h = temp_l;

	}


	cout << "Angle: " << diff_angle_l * 90.0 / asin(1) << "    " << diff_angle_h * 90.0/ asin(1) << endl;


	bool within_mirror = false;

	if (r->theta*90/asin(1) > diff_angle_l*90/asin(1) && r->theta*90/asin(1) < diff_angle_h*90/asin(1)) {

		within_mirror = true;

		cout << "here???? " << endl;

	} else {

		within_mirror = false;

	}

//	cout << "EXIT" << endl;
//	exit(0);

	return within_mirror;

} 





/*--------------------------------------------------*/

void composite_mirror_reflect(Double_t mirror_sub_2_x, Double_t mirror_sub_2_y, Double_t mirror_sub_2_angle, RAY* r) {

	 Double_t lx, ly, ll;
	 Double_t psi, zeta, s, ll_pr;
	 Double_t x, y, phi;

     lx = mirror_sub_2_x - r->x;
     ly = mirror_sub_2_y - r->y;
 
     ll = sqrt( lx*lx + ly*ly );

     phi = fabs(asin(ly/ll));

     psi = r->theta - PI - phi;

//	 cout << "aNGLE: " << sin(r->theta) << "    " << cos(r->theta)  << "    " << r->theta/asin(1.0) * 90 << "   " << psi/asin(1) * 90 << "  aaa  " << r->theta/asin(1.0) * 90 - 180 - fabs(asin(ly/ll)/asin(1.0) * 90) << "     " << lx << "     " << ly << "    "<< ll  << "     " << psi/asin(1.0) * 90 << endl;


	  s = ll * sin(psi) / cos (phi  + psi - fabs(mirror_sub_2_angle));

      zeta = PI - atan(lx/fabs(ly)) - fabs(mirror_sub_2_angle);

      ll_pr = sqrt( s*s + ll*ll - 2.0 * s * ll * cos(zeta) );

      x = r->x - ll_pr*cos(r->theta);
      y = r->y + ll_pr*sin(r->theta);

//	 cout << atan(lx/fabs(ly))*90/asin(1)  << "     " <<  psi << "    " <<  fabs(mirror_sub_2_angle) << "    1111 " << cos(zeta) << "  " << zeta*90/asin(1) << "    bbbb  " << s << "   "  << ll << "     " <<  fabs(2.0*s*ll*cos(zeta))  << "    " <<  ll_pr << endl;

//	Double_t x_calib, y_calib;
//	x_calib = 30;
//	y_calib = r->y - tan(-r->theta)* (r->x - 30);

	r->x = x;
	r->y = y;

	r->theta =  (PI - r->theta) + 2 * fabs(mirror_sub_2_angle);

//	cout <<  "aaaaa     " << (r->theta - PI)*90/asin(1) << "    "<< r->theta*90/asin(1) << endl;

//	r->theta =  - ((PI/2 - (PI/2 - (r->theta - PI)) - fabs(mirror_sub_2_angle))  + (PI/2 - (r->theta - PI)) + (PI/2 - (PI/2 - (r->theta - PI)) - fabs(mirror_sub_2_angle)) - PI/2);


//	r->theta =  (PI-(PI-phi) - fabs(mirror_sub_2_angle)) + (PI-phi) + (PI - (PI-phi) - fabs(mirror_sub_2_angle)) ;

//	cout << "lx = " << lx  << "   ly = " << ly << "    ll = " << ll << "    beta = " << atan(fabs(ly)/lx)*90/asin(1)<< endl << "   psi " << psi* 90 / asin(1) << endl;   

//	cout << "lx = " << lx  << "   ly = " << ly << "    ll = " << ll << "    beta = " << atan(fabs(ly)/lx)*90/asin(1)<< endl << "   psi " << psi* 90 / asin(1) << "  s = " << s << endl;   


	cout <<  "aaaaa     " << (r->theta)*90/asin(1)  << endl;

//	cout << phi*90/asin(1) << "    " << 90 - (90-phi*90/asin(1)) - fabs(mirror_sub_2_angle*90/asin(1))  << "     " << r-> theta*90/asin(1) << endl;



//	exit(0);

}



/*--------------------------------------------------*/

void side_mirror_reflect(Double_t mirror_sub_2_x, Double_t mirror_sub_2_y, Double_t mirror_sub_2_angle, RAY* r) {

	 Double_t lx, ly, ll;
	 Double_t psi, zeta, s, ll_pr;
	 Double_t x, y, phi;

     lx = mirror_sub_2_x - r->x;
     ly = mirror_sub_2_y - r->y;
 
     ll = sqrt( lx*lx + ly*ly );

     phi = asin(ly/ll);

     psi = phi - r->theta;




//	 cout << "aNGLE: " << sin(r->theta) << "    " << cos(r->theta)  << "    " << r->theta/asin(1.0) * 90 << "   " << psi/asin(1) * 90 << "  aaa  " << r->theta/asin(1.0) * 90 - 180 - fabs(asin(ly/ll)/asin(1.0) * 90) << "     " << lx << "     " << ly << "    "<< ll  << "     " << psi/asin(1.0) * 90 << endl;



	 cout << "aNGLE: " << r->theta/asin(1.0) * 90 << "   " << phi/asin(1) * 90 << "  aaa  "  << psi/asin(1.0) * 90 << endl;



      zeta =  PI - (PI/2 - fabs(phi) - fabs(PI - (mirror_sub_2_angle-PI/2)));

	  s = ll * sin(psi) / cos (zeta - (PI/2- fabs(psi)));

      ll_pr = sqrt( s*s + ll*ll - 2.0 * s * ll * cos(zeta) );

      x = r->x - ll_pr*cos(r->theta);
      y = r->y + ll_pr*sin(r->theta);

	 cout << s << "    " << atan(lx/fabs(ly))*90/asin(1)  << "     " <<  psi << "    " <<  fabs(mirror_sub_2_angle) << "    1111 " << cos(zeta) << "  " << zeta*90/asin(1) << "    " << (zeta - (PI/2- fabs(psi))) *90/asin(1)<< "    bbbb  " << s << "   "  << ll << "     " <<  fabs(2.0*s*ll*cos(zeta))  << "    " <<  ll_pr << endl;

//	Double_t x_calib, y_calib;
//	x_calib = 30;
//	y_calib = r->y - tan(-r->theta)* (r->x - 30);

	r->x = x;
	r->y = y;

	r->theta =  (PI - r->theta) - 2 * fabs(mirror_sub_2_angle-PI/2);

//	cout <<  "aaaaa     " << (r->theta - PI)*90/asin(1) << "    "<< r->theta*90/asin(1) << endl;

//	r->theta =  - ((PI/2 - (PI/2 - (r->theta - PI)) - fabs(mirror_sub_2_angle))  + (PI/2 - (r->theta - PI)) + (PI/2 - (PI/2 - (r->theta - PI)) - fabs(mirror_sub_2_angle)) - PI/2);


//	r->theta =  (PI-(PI-phi) - fabs(mirror_sub_2_angle)) + (PI-phi) + (PI - (PI-phi) - fabs(mirror_sub_2_angle)) ;

//	cout << "lx = " << lx  << "   ly = " << ly << "    ll = " << ll << "    beta = " << atan(fabs(ly)/lx)*90/asin(1)<< endl << "   psi " << psi* 90 / asin(1) << endl;   

//	cout << "lx = " << lx  << "   ly = " << ly << "    ll = " << ll << "    beta = " << atan(fabs(ly)/lx)*90/asin(1)<< endl << "   psi " << psi* 90 / asin(1) << "  s = " << s << endl;   


	cout <<  "aaaaa     " << (r->theta)*90/asin(1)  << endl;

//	cout << phi*90/asin(1) << "    " << 90 - (90-phi*90/asin(1)) - fabs(mirror_sub_2_angle*90/asin(1))  << "     " << r-> theta*90/asin(1) << endl;



//	exit(0);

}




/*--------------------------------------------------*/

void long_flat_mirror_reflect(Double_t mirror_sub_2_x, Double_t mirror_sub_2_y, Double_t mirror_sub_2_angle, RAY* r) {

	 Double_t lx, ly, ll;
	 Double_t psi, zeta, s, ll_pr;
	 Double_t x, y, phi;

     lx = mirror_sub_2_x - r->x;
     ly = mirror_sub_2_y - r->y;
 


     ll = sqrt( lx*lx + ly*ly );

	
	 cout << " check 333    " << mirror_sub_2_x << "   " << mirror_sub_2_y << "    "  << lx << "   " << ly  << "    " << ll << endl; 

     phi = asin(ly/ll);

     psi = r->theta - phi;


// 	 if (fabs(r->theta) > (PI/2 - fabs(phi))) {
// 
// 		psi = psi;
// 
// 	 } else {
// 	
// 		psi = -psi;
// 
//      }


	

//	 cout << "aNGLE: " << sin(r->theta) << "    " << cos(r->theta)  << "    " << r->theta/asin(1.0) * 90 << "   " << psi/asin(1) * 90 << "  aaa  " << r->theta/asin(1.0) * 90 - 180 - fabs(asin(ly/ll)/asin(1.0) * 90) << "     " << lx << "     " << ly << "    "<< ll  << "     " << psi/asin(1.0) * 90 << endl;



	  s = fabs(ll * sin(psi) / cos (phi +  psi - (fabs(mirror_sub_2_angle)-PI/2)));
	
	  if ( fabs(r->theta) > fabs(phi) ) {

      	zeta = PI - atan(lx/ly) + (mirror_sub_2_angle - PI/2);

	  } else {
	  
        zeta =  atan(lx/ly) - (mirror_sub_2_angle - PI/2);

	  }

//	  cout << phi*90/asin(1) << "    " << r->theta*90/asin(1) << endl; 

//	  exit(0);


//      zeta =  atan(lx/ly) - (mirror_sub_2_angle - PI/2);


	  cout << "angle: " << phi*90/asin(1) << "   " << psi*90/asin(1) << "    " << phi  + psi - fabs(mirror_sub_2_angle) << "    " << zeta*90/asin(1) << "   " << s  << "   zeta  = " << zeta * 90/asin(1) << "    " << (fabs(mirror_sub_2_angle)-PI/2)  << "    " << (PI - phi  - (PI/2-psi) - (fabs(mirror_sub_2_angle)-PI/2)) /asin(1)*90<< endl;


      ll_pr = sqrt( s*s + ll*ll - 2.0 * s * ll * cos(zeta) );

      x = r->x - fabs(ll_pr*cos(r->theta));
      y = r->y - fabs(ll_pr*sin(r->theta));


	 cout << s << "    " << atan(lx/fabs(ly))*90/asin(1)  << "     " <<  psi << "    " <<  fabs(mirror_sub_2_angle) << "    1111 " << cos(zeta) << "  " << zeta*90/asin(1) << "    " << (zeta - (PI/2- fabs(psi))) *90/asin(1)<< "    bbbb  " << s << "   "  << ll << "     " <<  fabs(2.0*s*ll*cos(zeta))  << "    " <<  ll_pr << endl;

	r->x = x;
	r->y = y;


	cout <<  "aaaaa     " << (r->theta)*90/asin(1)  << "    " <<  fabs(mirror_sub_2_angle)*90/asin(1)<< endl;

//	r->theta =  ( 2 * PI - r->theta) - 2 * fabs(mirror_sub_2_angle);

 	r->theta = PI/2 + fabs(r->theta) + mirror_sub_2_angle;   

//	cout <<  "bb     " << (r->theta)*90/asin(1)  << endl;

}




/*--------------------------------------------------*/
/*--------------------------------------------------*/

void side_flat_mirror_reflect(Double_t mirror_sub_2_x, Double_t mirror_sub_2_y, Double_t mirror_sub_2_angle, RAY* r) {

	 Double_t lx, ly, ll;
	 Double_t psi, zeta, s, ll_pr;
	 Double_t x, y, phi;

     lx = mirror_sub_2_x - r->x;
     ly = mirror_sub_2_y - r->y;
 


     ll = sqrt( lx*lx + ly*ly );

	
	 cout << " check 333    " << mirror_sub_2_x << "   " << mirror_sub_2_y << "    "  << lx << "   " << ly  << "    " << ll << endl; 

     phi = asin(ly/ll);

     psi = r->theta - phi;


// 	 if (fabs(r->theta) > (PI/2 - fabs(phi))) {
// 
// 		psi = psi;
// 
// 	 } else {
// 	
// 		psi = -psi;
// 
//      }


	

//	 cout << "aNGLE: " << sin(r->theta) << "    " << cos(r->theta)  << "    " << r->theta/asin(1.0) * 90 << "   " << psi/asin(1) * 90 << "  aaa  " << r->theta/asin(1.0) * 90 - 180 - fabs(asin(ly/ll)/asin(1.0) * 90) << "     " << lx << "     " << ly << "    "<< ll  << "     " << psi/asin(1.0) * 90 << endl;



	  s = fabs(ll * sin(psi) / cos (phi +  psi - (fabs(mirror_sub_2_angle)-PI/2)));
	
	  if ( fabs(r->theta) > fabs(phi) ) {

      	zeta = PI - atan(lx/ly) + (mirror_sub_2_angle - PI/2);

	  } else {
	  
        zeta =  atan(lx/ly) - (mirror_sub_2_angle - PI/2);

	  }

//	  cout << phi*90/asin(1) << "    " << r->theta*90/asin(1) << endl; 

//	  exit(0);


//      zeta =  atan(lx/ly) - (mirror_sub_2_angle - PI/2);


	  cout << "angle: " << phi*90/asin(1) << "   " << psi*90/asin(1) << "    " << phi  + psi - fabs(mirror_sub_2_angle) << "    " << zeta*90/asin(1) << "   " << s  << "   zeta  = " << zeta * 90/asin(1) << "    " << (fabs(mirror_sub_2_angle)-PI/2)  << "    " << (PI - phi  - (PI/2-psi) - (fabs(mirror_sub_2_angle)-PI/2)) /asin(1)*90<< endl;


      ll_pr = sqrt( s*s + ll*ll - 2.0 * s * ll * cos(zeta) );

      x = r->x - fabs(ll_pr*cos(r->theta));
      y = r->y - fabs(ll_pr*sin(r->theta));


	 cout << s << "    " << atan(lx/fabs(ly))*90/asin(1)  << "     " <<  psi << "    " <<  fabs(mirror_sub_2_angle) << "    1111 " << cos(zeta) << "  " << zeta*90/asin(1) << "    " << (zeta - (PI/2- fabs(psi))) *90/asin(1)<< "    bbbb  " << s << "   "  << ll << "     " <<  fabs(2.0*s*ll*cos(zeta))  << "    " <<  ll_pr << endl;

	r->x = x;
	r->y = y;


	cout <<  "aaaaa     " << (r->theta)*90/asin(1)  << "    " <<  fabs(mirror_sub_2_angle)*90/asin(1)<< endl;

//	r->theta =  ( 2 * PI - r->theta) - 2 * fabs(mirror_sub_2_angle);

// 	r->theta = PI/2 + fabs(r->theta) + mirror_sub_2_angle;   

 	r->theta = PI/2 - (PI/2 - (fabs(r->theta) + mirror_sub_2_angle)) + mirror_sub_2_angle;   

	cout <<  "aaaaa     " << (r->theta)*90/asin(1)  << "    " <<  fabs(mirror_sub_2_angle)*90/asin(1)<< endl;

//	exit(0);

//	cout <<  "bb     " << (r->theta)*90/asin(1)  << endl;

}




/*--------------------------------------------------*/

void composite_mirror_reflect_mod(Double_t mirror_sub_2_x, Double_t mirror_sub_2_y, Double_t mirror_sub_2_angle, RAY* r) {


	 Double_t lx, ly, ll;
	 Double_t psi, zeta, s, ll_pr;
	 Double_t x, y, phi;

     lx = mirror_sub_2_x - r->x;
     ly = mirror_sub_2_y - r->y;

     ll = sqrt( lx*lx + ly*ly );


	 cout <<  endl;
	 cout <<  endl;
	 cout <<  endl;
	 cout <<  endl;
	
	 cout << " check 333    " << mirror_sub_2_x << "   " << mirror_sub_2_y << "    "  << lx << "   " << ly  << "    " << ll  << "   theta = " << r->theta*90/asin(1) << "     " << mirror_sub_2_angle * 90/asin(1)<< endl; 

     phi = fabs(asin(ly/ll));

     psi = r->theta - phi - PI;

	 cout << "phi = " << phi * 90/asin(1) << "    psi = " << psi *90/asin(1)<< endl;

	 Double_t alpha = PI - (PI/2 - phi) - (PI/2 - psi) - (PI/2- fabs(mirror_sub_2_angle));
 
	 cout  << PI * 90/asin(1) << "    " << (PI/2-phi) *90/asin(1) << "    " << (PI/2-psi)*90/asin(1) << "    " << (PI/2- fabs(mirror_sub_2_angle)) *90/asin(1) << "        alpha = " << alpha * 90/asin(1) << endl;


     s =  ll * sin(psi) / cos(alpha);
	
     if ( fabs(r->theta) > fabs(phi) ) {

    	zeta = PI - ( (PI/2- phi) + (mirror_sub_2_angle + PI/2));

	 } else {
	  
        zeta =  (PI/2 - phi) + (mirror_sub_2_angle + PI/2);

	  }
 
// 	 cout << "aNGLE: " << sin(r->theta) << "    " << cos(r->theta)  << "    " << r->theta/asin(1.0) * 90 << "   " << psi/asin(1) * 90 << "  aaa  " << r->theta/asin(1.0) * 90 - 180 - fabs(asin(ly/ll)/asin(1.0) * 90) << "     " << lx << "     " << ly << "    "<< ll  << "     " << psi/asin(1.0) * 90  << "    " << phi/asin(1.0) * 90<< endl;
// 
// 	  cout << phi*90/asin(1) << "    " << r->theta*90/asin(1) << endl; 
// 
// //      zeta =  atan(lx/ly) - (mirror_sub_2_angle - PI/2);
// 

 	  cout << "angle: " << phi*90/asin(1) << "   " << psi*90/asin(1) << "    " << phi  + psi - fabs(mirror_sub_2_angle) << "    " << zeta*90/asin(1) << "   " << s  << "   zeta  = " << zeta * 90/asin(1) << "    " << phi *90/asin(1) << "    " << (PI/2 - asin(ll * sin(psi) / s))*90/asin(1) << "    " << s << endl;
// 

	  cout << "angle " << ( PI - (PI/2-phi) - (PI/2 - psi) - (PI/2- fabs(mirror_sub_2_angle)))*90/asin(1) << "         " << 90 - ( PI - (PI/2-phi) - (PI/2 - psi) - (PI/2- fabs(mirror_sub_2_angle)))*90/asin(1) << endl;


	  cout << (PI - zeta - psi) * 90/asin(1) << endl;

//	  exit(0);

      ll_pr = sqrt( s*s + ll*ll - 2.0 * s * ll * cos(zeta) );

	  if (r->theta*90/asin(1) >= 0 && r->theta*90/asin(1) < 90) {

      	x = r->x - fabs(ll_pr*cos(r->theta));
      	y = r->y + fabs(ll_pr*sin(r->theta));

	  }  else if (r->theta*90/asin(1) >= 90 && r->theta*90/asin(1) < 180) {
		
      	x = r->x + fabs(ll_pr*cos(r->theta));
      	y = r->y + fabs(ll_pr*sin(r->theta));

	  }  else if (r->theta*90/asin(1) >= 180 && r->theta*90/asin(1) < 270) {

      	x = r->x + fabs(ll_pr*cos(r->theta-PI));
      	y = r->y - fabs(ll_pr*sin(r->theta-PI));

	  }  else if (r->theta*90/asin(1) >= 270 && r->theta*90/asin(1) < 360) {
	
     	x = r->x - fabs(ll_pr*cos(r->theta));
      	y = r->y - fabs(ll_pr*sin(r->theta));

	  } 


    cout << s << "    " << atan(lx/fabs(ly))*90/asin(1)  << "     " <<  psi << "    " <<  fabs(mirror_sub_2_angle) << "    1111 " << cos(zeta) << "  " << zeta*90/asin(1) << "    " << (zeta - (PI/2- fabs(psi))) *90/asin(1)<< "    bbbb  " << s << "   "  << ll << "     " <<  fabs(2.0*s*ll*cos(zeta))  << "    " <<  ll_pr << endl;

	cout <<  "aaaaa     " << (r->theta)*90/asin(1)  << "    " <<  mirror_sub_2_angle*90/asin(1)<< endl;

	r->x = x;
	r->y = y;

	//r->theta = 3*PI/2 + (PI/2 - (PI/2 - fabs(r->theta - PI)) +  (PI/2 - fabs(mirror_sub_2_angle)));   

// 	r->theta = 3*PI/2 + alpha +  (PI/2 - fabs(mirror_sub_2_angle));   


//	r->theta =  ( PI - r->theta) ;

	r->theta =  (PI - r->theta) + 2 * (PI/2 - fabs(mirror_sub_2_angle));


//	cout <<  "aaaaa     " << 3*PI/2 *90 / asin(1) << "    " << (3 * PI / 2 - (fabs(r->theta) + (PI/2 - mirror_sub_2_angle))) *90/asin(1) << "    " << r->theta << "    " << (r->theta)*90/asin(1)  << "    " <<  fabs(mirror_sub_2_angle)*90/asin(1)<< endl;

	cout <<  "aaaaa     " << (r->theta)*90/asin(1)  << "    " <<  mirror_sub_2_angle*90/asin(1)<< endl;
	
//	exit(0);

}


