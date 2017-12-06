%{
#include <stdio.h>
#include "analyseur_csharp.h"
	boolean debug=true;
%}
%option noyywrap
%option yylineno
%option stack

DIGIT 	[0-9]
IDFF	[A-Za-z_@][A-Za-z0-9_]*
letter    = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_".
cr        = '\u000d'. /*13 = CR*/
eol       = '\u000a'. /*10 = LF*/
tab       = '\u0009'. /*9*/

%%
" "									{}
[\n]*								{}
[\t]*								{}
";"							{return PVIRG;}
"??"						{return NULLCOALESCING;}
"?"							{return POINTINTER;}
":"							{return DOUBLEDOT;}
","							{return VIRG;}
{DIGIT}+"."{DIGIT}*			{if (debug) printf ("%s ",yytext);	return DOUBLENUMBER;}
{DIGIT}+					{if (debug) printf ("%s ",yytext);	return INTNUMBER;}
"abstract"					{if (debug) printf ("%s ",yytext);	return ABSTRACT;}
"as"						{if (debug) printf ("%s ",yytext);	return AS;}
"base"						{if (debug) printf ("%s ",yytext);	return BASE;}
"bool"						{if (debug) printf ("%s ",yytext);	return BOOL;}
"break"						{if (debug) printf ("%s ",yytext);	return BREAK;}
"byte"						{if (debug) printf ("%s ",yytext);	return BYTE;}
"case"						{if (debug) printf ("%s ",yytext);	return CASE;}
"catch"						{if (debug) printf ("%s ",yytext);	return CATCH;}
"char" 						{if (debug) printf ("%s ",yytext);	return CHAR;}
"checked"					{if (debug) printf ("%s ",yytext);	return CHECKED;}
"class"						{if (debug) printf ("%s ",yytext);	return CLASS;}
"const"						{if (debug) printf ("%s ",yytext);	return CONST;}
"continue"					{if (debug) printf ("%s ",yytext);	return CONTINUE;}
"decimal"					{if (debug) printf ("%s ",yytext);	return DECIMAL;}
"default"					{if (debug) printf ("%s ",yytext);	return DEFAULT;}	
"delegate"					{if (debug) printf ("%s ",yytext);	return DELEGATE;}
"do"						{if (debug) printf ("%s ",yytext);	return DO;}	
"double"					{if (debug) printf ("%s ",yytext);	return DOUBLE;}
"else"						{if (debug) printf ("%s ",yytext);	return ELSE;}
"enum"						{if (debug) printf ("%s ",yytext);	return ENUM;}
"event"						{if (debug) printf ("%s ",yytext);	return EVENT;}
"explicit"					{if (debug) printf ("%s ",yytext);	return EXPLICIT;}
"extern"					{if (debug) printf ("%s ",yytext);	return EXTERN;}
"false"						{if (debug) printf ("%s ",yytext);	return FALSE;}
"finally"					{if (debug) printf ("%s ",yytext);	return FINALLY;} 	
"fixed"						{if (debug) printf ("%s ",yytext);	return FIXED;}
"float"						{if (debug) printf ("%s ",yytext);	return FLOAT;}
"for"						{if (debug) printf ("%s ",yytext);	return FOR;}
"foreach"					{if (debug) printf ("%s ",yytext);	return FOREACH;}
"goto"						{if (debug) printf ("%s ",yytext);	return GOTO;}
"if"						{if (debug) printf ("%s ",yytext);	return IF;}
"implicit"					{if (debug) printf ("%s ",yytext);	return IMPLICIT;}
"in"						{if (debug) printf ("%s ",yytext);	return IN;}
"int"						{if (debug) printf ("%s ",yytext);	return INT;}
"interface"					{if (debug) printf ("%s ",yytext);	return INTERFACE;}
"internal" 					{if (debug) printf ("%s ",yytext);	return INTERNAL;}	
"is"						{if (debug) printf ("%s ",yytext);	return IS;}
"lock"						{if (debug) printf ("%s ",yytext);	return LOCK;}
"long"						{if (debug) printf ("%s ",yytext);	return LONG;}
"namespace"					{if (debug) printf ("%s ",yytext);	return NAMESPACE;}
"new"						{if (debug) printf ("%s ",yytext);	return NEW;} 		
"null"						{if (debug) printf ("%s ",yytext);	return NNULL;}
"object"					{if (debug) printf ("%s ",yytext);	return OBJECT;}
"operator"					{if (debug) printf ("%s ",yytext);	return OPERATOR;}
"out"						{if (debug) printf ("%s ",yytext);	return OUT;}
"override"					{if (debug) printf ("%s ",yytext);	return OVERRIDE;}
"params" 					{if (debug) printf ("%s ",yytext);	return PARAMS;}
"private" 					{if (debug) printf ("%s ",yytext);	return PRIVATE;}
"protected" 				{if (debug) printf ("%s ",yytext);	return PROTECTED;}
"public"					{if (debug) printf ("%s ",yytext);	return PUBLIC;}
"readonly"					{if (debug) printf ("%s ",yytext);	return READONLY;}
"ref" 						{if (debug) printf ("%s ",yytext);	return REF;}
"return" 					{if (debug) printf ("%s ",yytext);	return RETURN;}	
"sbyte"						{if (debug) printf ("%s ",yytext);	return SBYTE;}
"sealed" 					{if (debug) printf ("%s ",yytext);	return SEALED;}	
"short" 					{if (debug) printf ("%s ",yytext);	return SHORT;}	
"sizeof" 					{if (debug) printf ("%s ",yytext);	return SIZEOF;}
"stackalloc"				{if (debug) printf ("%s ",yytext);	return STACKALLOC;}
"static" 					{if (debug) printf ("%s ",yytext);	return STATIC;}
"string"					{if (debug) printf ("%s ",yytext);	return STRING;}
"struct"					{if (debug) printf ("%s ",yytext);	return STRUCT;}
"switch"					{if (debug) printf ("%s ",yytext);	return SWITCH;}
"this" 						{if (debug) printf ("%s ",yytext);	return THIS;}
"throw"						{if (debug) printf ("%s ",yytext);	return THROW;}
"true" 						{if (debug) printf ("%s ",yytext);	return TRUE;}
"try"						{if (debug) printf ("%s ",yytext);	return TRY;}
"typeof"					{if (debug) printf ("%s ",yytext);	return TYPEOF;}
"uint"						{if (debug) printf ("%s ",yytext);	return UINT;}
"ulong"						{if (debug) printf ("%s ",yytext);	return ULONG;}
"unchecked"					{if (debug) printf ("%s ",yytext);	return UNCHECKED;}
"unsafe" 					{if (debug) printf ("%s ",yytext);	return UNSAFE;}
"ushort"					{if (debug) printf ("%s ",yytext);	return USHORT;}
"using"						{if (debug) printf ("%s ",yytext);	return USING;}
"virtual" 					{if (debug) printf ("%s ",yytext);	return VIRTUAL;}
"void" 						{if (debug) printf ("%s ",yytext);	return VOID;}
"volatile" 					{if (debug) printf ("%s ",yytext);	return VOLATILE;}
"while"						{if (debug) printf ("%s ",yytext);	return WHILE;}
"["							{if (debug) printf ("["); return LEFTBRACKET;}
"]"							{if (debug) printf ("]"); return RIGHTBRACKET;}
"("							{if (debug) printf ("("); return POPEN;}
")"							{if (debug) printf (")"); return PCLOSE;}		
"{"							{if (debug) printf ("{"); return BOPEN;}
"}"							{if (debug) printf ("}"); return BCLOSE;}
"="							{if (debug) printf ("="); return EQ;}
"+"							{if (debug) printf ("+"); return PLUS;}
"-"							{if (debug) printf ("-"); return MINUS;}
"*"							{if (debug) printf ("*"); return MULT;}
"/"							{if (debug) printf ("/"); return DIV;}
"%"							{if (debug) printf ("/"); return MOD;}
"+="  						{if (debug) printf ("+="); return PLUSEQ; }
"-="  						{if (debug) printf ("-="); return MINUSEQ; }
"*="  						{ return STAREQ; }
"/="  						{ return DIVEQ; }
"%="  						{ return MODEQ; }
"^"  						{ return XOR; }
"^="  						{ return XOREQ; }
"&"  						{ return AND; }
"&="  						{ return ANDEQ; }
"|"  						{ return OR; }
"|="  						{ return OREQ; }
"<"  						{ return LT; }
">"  						{ return GT; }
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
"var"						{if (debug) printf ("/"); return VAR;}		
{IDFF}						{if (debug) printf ("identifier");	return IDF;}
.							{ printf( "ERRORLEX(%s) ", yytext );}

%%
