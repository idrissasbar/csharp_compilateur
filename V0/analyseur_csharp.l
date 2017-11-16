%{
#include <stdio.h>
#include "analyseur_csharp.h"
%}
%option noyywrap
%option yylineno
%option stack

DIGIT 	[0-9]
IDFF	[A-Za-z_][A-Za-z0-9_]*

%%
" "									{}
[\n]*								{}
[\t]*								{}
";"						{return PVIRG;}
{DIGIT}+"."{DIGIT}*				{return DNUMBER;}
{DIGIT}+					{return INUMBER;}
"int"						{return INT;}
"double"  					{return DOUBLE;}
"bool"						{return BOOL;}
"true"						{return TRUE;}
"false"						{return FALSE;}	
"("							{return POPEN;}	
")"							{return PCLOSE;}		
{IDFF}						{return IDF;}
"+="  						{ return PLUSEQ; }
"-="  						{ return MINUSEQ; }
"*="  						{ return STAREQ; }
"/="  						{ return DIVEQ; }
"%="  						{ return MODEQ; }
"^="  						{ return XOREQ; }
"&="  						{ return ANDEQ; }
"|="  						{ return OREQ; }
"<<"  						{ return LTLT; }
">>"  						{ return GTGT; }
">>=" 						{ return GTGTEQ; }
"<<=" 						{ return LTLTEQ; }
"=="  						{ return EQEQ; }
"!="  						{ return NOTEQ; }
"<="  						{ return LEQ; }
">="  						{ return GEQ; }
"&&"  						{ return ANDAND; }
"||"  						{ return OROR; }
"++"  						{ return PLUSPLUS; }
"--"  						{ return MINUSMINUS; }
.							{ printf( "ERRORLEX(%s) ", yytext );}

%%
