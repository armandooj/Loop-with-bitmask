	subroutine fortranZero(tab, bitmasque, nb, somme)
	implicit none
	integer, intent(in) :: nb
	real*8, dimension(nb,3) :: tab
	integer*1, dimension(nb) :: bitmasque
	real*8, intent(out) :: somme
	integer :: i
	somme = 0
	do i=1,nb
	   somme = somme + bitmasque(i) * tab(i, 1); 
	enddo
	end

	subroutine fortranBlocZero(tab, bitmasque, nb, somme)
	implicit none
	integer, intent(in) :: nb
	real*4, dimension(nb) :: tab
	integer*1, dimension(nb) :: bitmasque
	real*8, intent(out) :: somme
	integer :: i
	somme = 0
	do i=1,nb
	   somme = somme + bitmasque(i) * tab(i); 
	enddo
	end


	subroutine fortranIf(tab, bitmasque, nb, somme)
	implicit none
	integer, intent(in) :: nb
	real*8, dimension(nb,3) :: tab
	integer*1, dimension(nb) :: bitmasque
	real*8, intent(out) :: somme
	integer :: i
	somme = 0
	do i=1,nb
	   if (bitmasque(i) == 1) then
	      somme = somme + tab(i, 1);
	   end if
	enddo
	end
