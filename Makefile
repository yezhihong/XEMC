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
RTLIBS := -L${ROOTSYS}/lib -lCore -lgfortran # /usr/lib/libg2c.so.0 #use /usr/lib64/ for ifarm
#RTLIBS := -L${ROOTSYS}/lib -lCore ${x2}/mylib/libg2c.so.0 # /usr/lib/libg2c.so.0 #use /usr/lib64/ for ifarm
#RTLIBS := -L${ROOTSYS}/lib -lCore /usr/lib64/libg2c.so.0 # /usr/lib/libg2c.so.0 #use /usr/lib64/ for ifarm
#RTLIBS := -L${ROOTSYS}/lib -lCore  /usr/lib/libg2c.so.0 #use /usr/lib64/ for ifarm
all: $(PROGRAM)

$(PROGRAM): $(PROGRAM).o
	g++ -o $(PROGRAM) $(PROGRAM).o $(CFLAGS) $(LIBS) $(RTLIBS) 
	#clang++ -o $(PROGRAM) $(PROGRAM).o $(CFLAGS) $(LIBS) $(RTLIBS) 

$(PROGRAM).o: $(PROGRAM).C
	g++ $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).C ${INCLUDE}
	#clang++ $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).C ${INCLUDE}

clean:
	rm -f *.o ./SRC/*.o	
