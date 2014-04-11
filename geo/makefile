#$Id: makefile 5444 2012-03-11 11:41:41Z haowu $

include ../makefile.inc

all: etc-geo.a

etc-geo.a: etc-geo.a(geo.o kmeans.o quadtree.o)

geo.o      : geo.h
kmeans.o   : kmeans.h
quadtree.o : quadtree.h

.PHONY : clean

clean :
	-rm *.a *.o
