example0: 
	lex token.l
	yacc -v example0.y
	g++ -o example0 y.tab.c -ll

all: example0 
clean:
	rm -f y.tab.c
	rm -f lex.yy.c
	rm -f example0
	rm -f y.output
	rm -f *~
	rm -f a.out
