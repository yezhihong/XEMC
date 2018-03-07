#-------------------------------------------
# Makefile for any C program with ROOT lib
# Zhihong Ye, 01/09/2009
#-------------------------------------------

PROGRAM = Check_XS
CFLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags)
LIBS   = $(shell $(ROOTSYS)/bin/root-config --libs)
GLIBS  = $(shell $(ROOTSYS)/bin/root-config --glibs)
XEM_DIR = ./SRC

CFLAGS += -Wall -g
INCLUDE := -I${ROOTSYS}/include -I$(XEM_DIR)
RTLIBS := -L${ROOTSYS}/lib -lCore -lgfortran # /usr/lib/libg2c.so.0 #use /usr/lib64/ for ifarm
all: $(PROGRAM)

GFORTRAN := gfortran
FFLAGS = -C -g -m64 -fbounds-check -finit-local-zero -fno-automatic # use -m64 on ifarm, which is a 64bit system

${XEM_DIR}/F1F209.o: ${XEM_DIR}/F1F209.f 
	rm -f $@
	cd ${XEM_DIR} ; $(GFORTRAN) $(FFLAGS) -c F1F209.f;

#$(PROGRAM): $(PROGRAM).o
	#g++ -o $(PROGRAM) $(PROGRAM).o $(CFLAGS) $(LIBS) $(RTLIBS)

$(PROGRAM): $(PROGRAM).o $(XEM_DIR)/F1F209.o
	g++ -o $(PROGRAM) $(PROGRAM).o $(CFLAGS) $(LIBS) $(RTLIBS) $(XEM_DIR)/F1F209.o 

#$(PROGRAM): $(PROGRAM).o F1F209.o
	#g++ -o $(PROGRAM) $(PROGRAM).o $(CFLAGS) $(LIBS) $(RTLIBS) F1F209.o 


$(PROGRAM).o: $(PROGRAM).C
	g++ $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).C ${INCLUDE}

clean:
	rm -f *.o ./SRC/*.o	
