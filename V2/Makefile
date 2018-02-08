pile : pile.h types.h pile.c
	gcc -c pile.c

types : pseudocode.h ast.h types.h tablesymb.h types.c
	gcc -c types.c

vm : vm.h pseudocode.h pile.h
	gcc -c vm.c

error : error.h error.c
	gcc -c error.c

tableSymb : tablesymb.h  types.h tablesymb.c
	gcc -c tablesymb.c

ast : ast.h ast.c pseudocode.h
	gcc -c ast.c

pseudocode : pseudocode.h pseudocode.c
	gcc -c pseudocode.c

lex : analyseur_csharp.h analyseur_csharp.l
	flex -i analyseur_csharp.l
	gcc -c lex.yy.c

analyseur_csharp : types.h error.h types.h ast.h analyseur_csharp.h analyseur_csharp.c
	gcc -c analyseur_csharp.c

analyseurout :lex types error tableSymb  ast pseudocode pile vm analyseur_csharp 
	gcc -o csharpc types.o ast.o error.o tablesymb.o pseudocode.o pile.o vm.o lex.yy.o  analyseur_csharp.o -lfl

all : analyseurout

clean :
	rm *~
	rm *.yy.c
	rm *.exe
	rm csharpc 
	rm *.o


