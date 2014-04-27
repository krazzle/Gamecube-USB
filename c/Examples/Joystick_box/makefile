INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib 

COMPILERFLAGS = -Wall
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 

# to produce, say, lesson1:
#
# 1. compile the thing.  uses the variables defined above.
# 
box_tutorial : box_tutorial.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) GamecubeController.c $< $(LIBRARIES)  

clean:
	rm box_tutorial *.o

