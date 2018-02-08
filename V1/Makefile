all : analyseurout 

lex : analyseur_csharp.h analyseur_csharp.l
	flex -i analyseur_csharp.l
	gcc -c lex.yy.c
analyseur_csharp : analyseur_csharp.h analyseur_csharp.c
	gcc -c analyseur_csharp.c
analyseurout :lex analyseur_csharp 
	gcc -o csharpc lex.yy.o  analyseur_csharp.o -lfl
clean :
	rm *~
	rm *.yy.c
	rm *.exe
	rm csharpc 
	rm *.o