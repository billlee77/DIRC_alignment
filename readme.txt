[nicholas.cerenkov.raytrace]
	This directory contains the source for the program to raytrace light
through the cerenkov detector. The details of the program are contained in
comments in the files. The .com file 'do.com' comtains the link commmand for
the programs. I include a copy here:

$set verify
$cc 'P1'
$link raytr,set_main_mirror,draw_mirror,get_next_ray,intersect_main_mirror, -
   follow_ray_out,hit_PMT,reposition_fpoint

The needed files here are:
	'hms1.dat', hms2.dat' : the first and second order TRANSPORT matrices
needed by RAYTR. 'hms2.dat' is the more recent of the two.

Also, there are some extra 'c' files that contain simple code for generating
'.com' files for batch runs. The batch runs are for things like generating the
tolerance plots (see TOLER.C).
