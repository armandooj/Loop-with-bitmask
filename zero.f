	subroutine fortranZero(tab, bitmasque, nb, somme)
	implicit none
	integer, intent(in) :: nb
	real*8, dimension(nb,3) :: tab
	integer*1, dimension(nb) :: bitmasque
	real*8 :: somme
	integer :: i
	do i=1,nb
	   somme = somme + bitmasque(i) * tab(i, 1); 
	enddo
	end
