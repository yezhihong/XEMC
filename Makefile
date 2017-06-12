#-------------------------------------------
# Makefile for any C program with ROOT lib
# Zhihong Ye, 01/09/2009
#-------------------------------------------

PROGRAM = Check_XS
CFLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags)
LIBS   = $(shell $(ROOTSYS)/bin/root-config --libs)
GLIBS  = $(shell $(ROOTSYS)/bin/root-config --glibs)

XEMCDIR=/work/halla/triton/yez/XEMC

CFLAGS += -Wall -g
INCLUDE := -I${ROOTSYS}/include -I$(XEMCDIR)/SRC
RTLIBS := -L${ROOTSYS}/lib -lCore 

all: $(PROGRAM)

$(PROGRAM): $(PROGRAM).o
	g++ -o $(PROGRAM) $(PROGRAM).o $(CFLAGS) $(LIBS) $(RTLIBS) 
	#clang++ -o $(PROGRAM) $(PROGRAM).o $(CFLAGS) $(LIBS) $(RTLIBS) 

$(PROGRAM).o: $(PROGRAM).C
	g++ $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).C ${INCLUDE}
	#clang++ $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).C ${INCLUDE}

clean:
	rm -f *.o ./SRC/*.o	
