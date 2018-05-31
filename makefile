# ######################	raytr   ######################
# 
#  raytr:  raytr.o set_main_mirror.o draw_mirror.o get_next_ray.o intersect_main_mirror.o \
#  follow_ray_out.o hit_PMT.o reposition_fpoint.o 
# 	g++ -lm -o raytr raytr.o set_main_mirror.o draw_mirror.o get_next_ray.o intersect_main_mirror.o follow_ray_out.o hit_pmt.o reposition_fpoint.o 
# 
# raytr.o: raytr.c
# 	cc -c raytr.c
# 	
# set_main_mirror.o: set_main_mirror.c
# 	cc -c set_main_mirror.c
# 	
# draw_mirror.o: draw_mirror.c
# 	cc -c draw_mirror.c
# 	
# get_next_ray.o: get_next_ray.c
# 	cc -c get_next_ray.c
# 	
# intersect_main_mirror.o: intersect_main_mirror.c
# 	cc -c intersect_main_mirror.c
# 	
# follow_ray_out.o: follow_ray_out.c
# 	cc -c follow_ray_out.c
# 	
# hit_PMT.o: hit_pmt.c
# 	cc -c hit_pmt.c
# 	
# reposition_fpoint.o: reposition_fpoint.c
# 	cc -c reposition_fpoint.c

CC=g++
CFLAGS=-lm `root-config --cflags  --glibs`
EXECUTABLE=raytr

#SOURCES= raytr.c set_main_mirror.c  draw_mirror.c get_next_ray.c intersect_main_mirror.c follow_ray_out.c hit_pmt.c reposition_fpoint.c

SOURCES= raytr.c draw_mirror.c set_main_mirror.c get_next_ray.c intersect_main_mirror.c follow_ray_out.c flat_ref_mirror.c hit_pmt.c


OBJECTS = $(SOURCES:.c=.o)


all: $(EXECUTABLE) 

raytr: $(OBJECTS)
	$(CC) -o raytr $(OBJECTS) $(CFLAGS)

#
#draw_mirror.o: draw_mirror.c
#	$(CC) -c $(CFLAGS) draw_mirror.c



# 

# raytr.o: raytr.c
# 	$(CC) -o $@ raytr.c $(CFLAGS)

# 	
# set_main_mirror.o: set_main_mirror.c
# 	$(CC) -c $(CFLAGS) set_main_mirror.c
# 	

# 	
# get_next_ray.o: get_next_ray.c
# 	$(CC) -c $(CFLAGS) get_next_ray.c
# 	
# intersect_main_mirror.o: intersect_main_mirror.c
# 	$(CC) -c $(CFLAGS) intersect_main_mirror.c
# 	
# follow_ray_out.o: follow_ray_out.c
# 	$(CC) -c $(CFLAGS) follow_ray_out.c
# 	
# hit_PMT.o: hit_pmt.c
# 	$(CC) -c $(CFLAGS) hit_pmt.c
# 	
# reposition_fpoint.o: reposition_fpoint.c
# 	$(CC) -c $(CFLAGS) reposition_fpoint.c

clean:
	rm $(EXECUTABLE) *.o
