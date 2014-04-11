#$Id: makefile 5444 2012-03-11 11:41:41Z haowu $

include ../makefile.inc

all: etc-text.a

etc-text.a: etc-text.a(lexer.o dictionary.o doc_index.o table.o trie.o)

lexer.o      : lexer.h
dictionary.o : dictionary.h
doc_index.o  : doc_index.h
table.o      : table.h
trie.o       : trie.h

.PHONY : clean

clean :
	-rm *.a *.o
