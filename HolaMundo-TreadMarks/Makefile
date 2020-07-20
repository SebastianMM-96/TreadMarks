LIBDIR=/home/<user>/Tmk/lib.i386_linux2

INCLUDE_DIR=/home/<user>/Tmk/include

LIB=Tmk_udp

hola_tmk:
	gcc -m32 hola_tmk.c -o hola_tmk -L$(LIBDIR) -I$(INCLUDE_DIR) -l$(LIB)
  
clean:
	rm -f hola_tmk
