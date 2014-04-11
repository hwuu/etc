#$Id: makefile 5444 2012-03-11 11:41:41Z haowu $

include ../makefile.inc

all: etc-util.a

etc-util.a: etc-util.a(heap.o search.o timer.o util.o vbe.o raw_query.o)

heap.o      : heap.h
search.o    : search.h
timer.o     : timer.h
util.o      : util.h
vbe.o       : vbe.h
raw_query.o : raw_query.h

.PHONY : clean

clean :
	-rm *.a *.o
