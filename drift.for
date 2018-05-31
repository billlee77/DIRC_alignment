c
c	reads in a 1st order transport matrix and outputs the new
c	matrix after a drift of distance DRFT
c
	dimension tr_mat(6,6),drift(6,6),tr_mat_dr(6,6)
	character*30 trp_in_file,trp_out_file
c
	write(6,'(a)')'$ Enter filename for input matrix >'
	read(5,'(q,a<nchar>)')nchar,trp_in_file
	write(6,'(a)')'$ Enter drift distance (m) >'
	read(5,*)drft
	trp_out_file = trp_in_file(1:nchar)//'_dr'
c
	open(unit=1,file=trp_in_file,status='old')
	do i=1,6
	   read(1,*)(tr_mat(i,j),j=1,6)
	   drift(i,i) = 1.0
	enddo
	close(unit=1)
c
	drift(1,2) = drft/10.
	drift(3,4) = drft/10.
c
	do i=1,6
	   do k=1,6
	      do j=1,6
		tr_mat_dr(i,k) = tr_mat_dr(i,k) + drift(i,j)*tr_mat(j,k)
	      enddo
	   enddo
	enddo
c
	open(unit=2,file=trp_out_file,status='new')
	do i=1,6
	  write(2,100)(tr_mat_dr(i,j),j=1,6)
100	  format(6x,6(f8.5,3x))
	enddo
	close(unit=2)
	stop
	end
