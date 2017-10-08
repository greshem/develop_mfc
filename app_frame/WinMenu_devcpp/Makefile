CC = mingw32-gcc  -g  -Wall 
CPP = mingw32-g++ -g  -Wall 
EXEC = main  
MAIN_OBJS= main.o  
NOMAIN_OBJS= WinMenu_private.res
RES_OBJS=
CFLAGS += -Wno-write-strings
LDFLAGS += 
LIBS +=  -mwindows  


all: $(EXEC)
$(EXEC): $(MAIN_OBJS)  $(NOMAIN_OBJS)  $(RES_OBJS)
	$(CPP) $(LDFLAGS) -o $@ $@.o $(NOMAIN_OBJS) $(LIBS)

vim: 
	vim main.cpp
exec: $(EXEC) 
	$(EXEC)
	./$@
log:
	 vim main.log
gdb: 
	gdb ./main
.PRECIOUS:%.cpp %.c %.C %.rc
.SUFFIXES:
.SUFFIXES:  .c .o .cpp .ecpp .pc .ec .C .rc

.cpp.o:
	$(CPP) -c -o $*.o $(CFLAGS) $(INCLUDEDIR)  $*.cpp
	$(CPP) -S   $(CFLAGS) $(INCLUDEDIR)  $*.cpp

.c.o:
	$(CC) -c -o $*.o $(CFLAGS) $(INCLUDEDIR) $*.c
	$(CC) -S   $(CFLAGS) $(INCLUDEDIR) $*.c

.C.o:
	$(CC) -c -o $*.o $(CFLAGS) $(INCLUDEDIR) $*.C	
	$(CC) -S   $(CFLAGS) $(INCLUDEDIR) $*.C	

.ecpp.C:
	$(ESQL) -e $(ESQL_OPTION) $(INCLUDEDIR) $*.ecpp 
	
.ec.c:
	$(ESQL) -e $(ESQL_OPTION) $(INCLUDEDIR) $*.ec
	
.pc.cpp:
	$(PROC)  CPP_SUFFIX=cpp $(PROC_OPTION)  $*.pc

.res.rc:
	mingw32-windres $*.rc -o $*.res -O coff
	

clean:
	-rm -f $(EXEC) *.o *.s *.log *.obj *.res
