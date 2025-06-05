CC = g++
CFLAGS = -std=c++11
YACC = yacc
LEX = flex

all: parser

parser: y.tab.o lex.yy.o
	$(CC) $(CFLAGS) -o parser y.tab.o lex.yy.o

y.tab.c y.tab.h: simple.y
	$(YACC) -d simple.y

lex.yy.c: simple.l y.tab.h
	$(LEX) simple.l

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -c y.tab.c

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

clean:
	rm -f *.o y.tab.c y.tab.h lex.yy.c parser

.PHONY: all clean 