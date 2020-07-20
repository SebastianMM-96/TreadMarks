LIBDIR=/home/<user>/Tmk/lib.i386_linux2

INCLUDE_DIR=/home/<user>/Tmk/include

LIB=Tmk_udp
	
suma_tmk:
	gcc -m32 suma_tmk.c -o suma_tmk -L$(LIBDIR) -I$(INCLUDE_DIR) -l$(LIB)
	
clean:
	rm -f suma_tmk
