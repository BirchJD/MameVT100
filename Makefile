EXE = MameVT100

LIBDIRS = -L/usr/X11R6/lib -L/usr/local/lib
INCDIRS = -I/usr/include -I/usr/local/include

CC = gcc
CFLAGS = -g $(INCDIRS)
LIBS = -lX11

$(EXE) : $(EXE).o
	$(CC) $(CFLAGS) -c $(LIBDIRS) *.c $(LIBS)
	$(CC) $(CFLAGS) -o $(EXE) $(LIBDIRS) *.o $(LIBS)

clean:
	rm -f *.o

