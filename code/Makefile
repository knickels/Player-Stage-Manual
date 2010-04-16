# Makefile for compiling Player projects! 
# to run this script and copile your code type "make all clean" (no quotes)
# into the terminal, or "make all" if you don't want the .o files cleaned away.
# Jennifer Owen 28/05/2009
# jowen@cs.york.ac.uk

# change this stuff as you need to:

# the name you want to give the executable
TARGET = bigbob

# the code files you want to compile
CFILES = bigbob.cc

# the directory where all your code is stored
MAIN_DIR =.

# the folder where header files are stored
HEADERS = $(MAIN_DIR)


#############################################################
################## DON'T CHANGE CODE BELOW ##################
#############################################################

# which compiler to use 
CC = g++
STRIP = strip

# turns the names of the code files into names of objects. It replaces the suffix
# also can be done by $(CFILES:%.cc = %.o) I think.
OBJS = $(CFILES:.cc=.o)

# where to find all the header files. -I tells the compiler these folders 
# contain things that are included in your code
INCLUDES = -I$(MAIN_DIR) -I$(HEADERS)

# This links the object files together into a binary. It's dependancy is
# the $(OBJS) bit, so that gets done first.
all: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) `pkg-config --libs playerc++`
	$(STRIP) $(TARGET)


# this is run before the make. It puts together object files without linking
# them together into a binary executable	
$(OBJS): 
	$(CC) `pkg-config --cflags playerc++` $*.cc  -c $(INCLUDES) 


# removes all the object files. Not automatically done by a call to make,
# need to type "make clean" (without the quotes) into the terminal.	
# or "make all clean"
clean:
	rm -f *.o
