#-------------------------------------------
# Makefile for any C program with ROOT lib
# Zhihong Ye, 01/09/2009
#-------------------------------------------

PROGRAM = Check_XS
CFLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags)
LIBS   = $(shell $(ROOTSYS)/bin/root-config --libs)
GLIBS  = $(shell $(ROOTSYS)/bin/root-config --glibs)

#XEMCDIR=/work/halla/e08014/disk1/yez/XEMC
XEMCDIR=./

CFLAGS += -Wall -g
INCLUDE := -I${ROOTSYS}/include -I$(XEMCDIR)/SRC
RTLIBS := -L${ROOTSYS}/lib -lCore 

all: $(PROGRAM)


$(PROGRAM): $(PROGRAM).o $(XEMCDIR)/SRC/XEM_TGT.o
	g++ -o $(PROGRAM) $(PROGRAM).o $(XEMCDIR)/SRC/XEM_TGT.o $(CFLAGS) $(LIBS) $(RTLIBS) 
	#clang++ -o $(PROGRAM) $(PROGRAM).o $(XEMCDIR)/SRC/XEM_TGT.o $(CFLAGS) $(LIBS) $(RTLIBS) 

$(PROGRAM).o: $(PROGRAM).C
	g++ $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).C ${INCLUDE}
	#clang++ $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).C ${INCLUDE}

$(XEMCDIR)/SRC/XEM_TGT.o: $(XEMCDIR)/SRC/XEM_TGT.C
	g++ $(CFLAGS) -c -o $(XEMCDIR)/XEM_TGT.o $(XEMCDIR)/SRC/XEM_TGT.C ${INCLUDE}
	#clang++ $(CFLAGS) -c -o $(XEMCDIR)/SRC/XEM_TGT.o $(XEMCDIR)/SRC/XEM_TGT.C ${INCLUDE}


clean:
	rm -f *.o ./SRC/*.o	
