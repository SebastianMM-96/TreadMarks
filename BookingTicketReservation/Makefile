LIBDIR=/home/sebastian/Tmk/lib.i386_linux2
INCLUDE_DIR=/home/sebastian/Tmk/include
LIB=Tmk_udp

bookingCinema:
	gcc -m32 bookingCinema.c -o bookingCinema -L$(LIBDIR) -I$(INCLUDE_DIR) -l$(LIB)
	
clean:
	rm -f bookingCinema 