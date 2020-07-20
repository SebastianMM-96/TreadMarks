LIBDIR=/home/<user>/Tmk/lib.i386_linux2

INCLUDE_DIR=/home/<user>/Tmk/include

LIB=Tmk_udp

test_tmk:
	gcc -m32 test_tmk.c -o test_tmk -L$(LIBDIR) -I$(INCLUDE_DIR) -l$(LIB)
	
clean:
	rm -f test_tmk
