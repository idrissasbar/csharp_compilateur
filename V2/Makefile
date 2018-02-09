classes : analyseur_csharp.h classes.h  classes.c
	gcc -c classes.c

start : analyseur_csharp.h start.h  start.c
	gcc -c start.c

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

analyseur_csharp : start.h classes.h types.h error.h types.h ast.h analyseur_csharp.h analyseur_csharp.c
	gcc -c analyseur_csharp.c

analyseurout :lex types error tableSymb  ast pseudocode pile vm classes start analyseur_csharp 
	gcc -o csharpc types.o ast.o error.o tablesymb.o pseudocode.o pile.o vm.o lex.yy.o classes.o start.o analyseur_csharp.o -lfl

all : analyseurout

clean :
	rm *~
	rm *.yy.c
	rm *.exe
	rm csharpc 
	rm *.o


