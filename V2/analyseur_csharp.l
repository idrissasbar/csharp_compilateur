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
";"							{if (debug) printf ("; \n"); return PVIRG;}
"??"						{if (debug) printf ("?? \n");return NULLCOALESCING;}
"?"							{if (debug) printf ("? \n");return POINTINTER;}
":"							{if (debug) printf (": \n");return DOUBLEDOT;}
"."							{if (debug) printf (". \n");return POINT;}
","							{if (debug) printf (", \n");return VIRG;}
{DIGIT}+"."{DIGIT}*			{if (debug) printf ("%s \n",yytext); set_number_attributes(atof(yytext));	return DOUBLENUMBER;}
{DIGIT}+					{if (debug) printf ("%s \n",yytext); set_number_attributes((double)atoi(yytext));	return INTNUMBER;}
"abstract"					{if (debug) printf ("%s \n",yytext);	return ABSTRACT;}
"as"						{if (debug) printf ("%s \n",yytext);	return AS;}
"base"						{if (debug) printf ("%s \n",yytext);	return BASE;}
"bool"						{if (debug) printf ("%s \n",yytext);	return BOOL;}
"break"						{if (debug) printf ("%s \n",yytext);	return BREAK;}
"byte"						{if (debug) printf ("%s \n",yytext);	return BYTE;}
"case"						{if (debug) printf ("%s \n",yytext);	return CASE;}
"catch"						{if (debug) printf ("%s \n",yytext);	return CATCH;}
"char" 						{if (debug) printf ("%s \n",yytext);	return CHAR;}
"checked"					{if (debug) printf ("%s \n",yytext);	return CHECKED;}
"class"						{if (debug) printf ("%s \n",yytext);	return CLASS;}
"const"						{if (debug) printf ("%s \n",yytext);	return CONST;}
"continue"					{if (debug) printf ("%s \n",yytext);	return CONTINUE;}
"decimal"					{if (debug) printf ("%s \n",yytext);	return DECIMAL;}
"default"					{if (debug) printf ("%s \n",yytext);	return DEFAULT;}	
"delegate"					{if (debug) printf ("%s \n",yytext);	return DELEGATE;}
"do"						{if (debug) printf ("%s \n",yytext);	return DO;}	
"double"					{if (debug) printf ("%s \n",yytext);	return DOUBLE;}
"else"						{if (debug) printf ("%s \n",yytext);	return ELSE;}
"enum"						{if (debug) printf ("%s \n",yytext);	return ENUM;}
"event"						{if (debug) printf ("%s \n",yytext);	return EVENT;}
"explicit"					{if (debug) printf ("%s \n",yytext);	return EXPLICIT;}
"extern"					{if (debug) printf ("%s \n",yytext);	return EXTERN;}
"false"						{if (debug) printf ("%s \n",yytext);	return FALSE;}
"finally"					{if (debug) printf ("%s \n",yytext);	return FINALLY;} 	
"fixed"						{if (debug) printf ("%s \n",yytext);	return FIXED;}
"float"						{if (debug) printf ("%s \n",yytext);	return FLOAT;}
"for"						{if (debug) printf ("%s \n",yytext);	return FOR;}
"foreach"					{if (debug) printf ("%s \n",yytext);	return FOREACH;}
"goto"						{if (debug) printf ("%s \n",yytext);	return GOTO;}
"if"						{if (debug) printf ("%s \n",yytext);	return IF;}
"implicit"					{if (debug) printf ("%s \n",yytext);	return IMPLICIT;}
"in"						{if (debug) printf ("%s \n",yytext);	return IN;}
"int"						{if (debug) printf ("%s \n",yytext);	return INT;}
"interface"					{if (debug) printf ("%s \n",yytext);	return INTERFACE;}
"internal" 					{if (debug) printf ("%s \n",yytext);	return INTERNAL;}	
"is"						{if (debug) printf ("%s \n",yytext);	return IS;}
"lock"						{if (debug) printf ("%s \n",yytext);	return LOCK;}
"long"						{if (debug) printf ("%s \n",yytext);	return LONG;}
"namespace"					{if (debug) printf ("%s \n",yytext);	return NAMESPACE;}
"new"						{if (debug) printf ("%s \n",yytext);	return NEW;} 		
"null"						{if (debug) printf ("%s \n",yytext);	return NNULL;}
"object"					{if (debug) printf ("%s \n",yytext);	return OBJECT;}
"dynamic"					{if (debug) printf ("%s \n",yytext);	return DYNAMIC;}
"operator"					{if (debug) printf ("%s \n",yytext);	return OPERATOR;}
"out"						{if (debug) printf ("%s \n",yytext);	return OUT;}
"override"					{if (debug) printf ("%s \n",yytext);	return OVERRIDE;}
"params" 					{if (debug) printf ("%s \n",yytext);	return PARAMS;}
"private" 					{if (debug) printf ("%s \n",yytext);	return PRIVATE;}
"protected" 				{if (debug) printf ("%s \n",yytext);	return PROTECTED;}
"public"					{if (debug) printf ("%s \n",yytext);	return PUBLIC;}
"readonly"					{if (debug) printf ("%s \n",yytext);	return READONLY;}
"ref" 						{if (debug) printf ("%s \n",yytext);	return REF;}
"return" 					{if (debug) printf ("%s \n",yytext);	return RETURN;}	
"sbyte"						{if (debug) printf ("%s \n",yytext);	return SBYTE;}
"sealed" 					{if (debug) printf ("%s \n",yytext);	return SEALED;}	
"short" 					{if (debug) printf ("%s \n",yytext);	return SHORT;}	
"sizeof" 					{if (debug) printf ("%s \n",yytext);	return SIZEOF;}
"stackalloc"				{if (debug) printf ("%s \n",yytext);	return STACKALLOC;}
"static" 					{if (debug) printf ("%s \n",yytext);	return STATIC;}
"string"					{if (debug) printf ("%s \n",yytext);	return STRING;}
"struct"					{if (debug) printf ("%s \n",yytext);	return STRUCT;}
"switch"					{if (debug) printf ("%s \n",yytext);	return SWITCH;}
"this" 						{if (debug) printf ("%s \n",yytext);	return THIS;}
"throw"						{if (debug) printf ("%s \n",yytext);	return THROW;}
"true" 						{if (debug) printf ("%s \n",yytext);	return TRUE;}
"try"						{if (debug) printf ("%s \n",yytext);	return TRY;}
"typeof"					{if (debug) printf ("%s \n",yytext);	return TYPEOF;}
"uint"						{if (debug) printf ("%s \n",yytext);	return UINT;}
"ulong"						{if (debug) printf ("%s \n",yytext);	return ULONG;}
"unchecked"					{if (debug) printf ("%s \n",yytext);	return UNCHECKED;}
"unsafe" 					{if (debug) printf ("%s \n",yytext);	return UNSAFE;}
"ushort"					{if (debug) printf ("%s \n",yytext);	return USHORT;}
"using"						{if (debug) printf ("%s \n",yytext);	return USING;}
"virtual" 					{if (debug) printf ("%s \n",yytext);	return VIRTUAL;}
"void" 						{if (debug) printf ("%s \n",yytext);	return VOID;}
"volatile" 					{if (debug) printf ("%s \n",yytext);	return VOLATILE;}
"while"						{if (debug) printf ("%s \n",yytext);	return WHILE;}
"remove"					{if (debug) printf ("%s \n",yytext);	return REMOVE;}
"partial"					{if (debug) printf ("%s \n",yytext);	return PARTIAL;}
"["							{if (debug) printf ("[ \n"); return LEFTBRACKET;}
"]"							{if (debug) printf ("] \n"); return RIGHTBRACKET;}
"("							{if (debug) printf ("( \n"); return POPEN;}
")"							{if (debug) printf (") \n"); return PCLOSE;}		
"{"							{if (debug) printf ("{ \n"); return BOPEN;}
"}"							{if (debug) printf ("} \n"); return BCLOSE;}
"="							{if (debug) printf ("= \n"); return EQ;}
"+"							{if (debug) printf ("+ \n"); return PLUS;}
"-"							{if (debug) printf ("- \n"); return MINUS;}
"*"							{if (debug) printf ("* \n"); return MULT;}
"/"							{if (debug) printf ("/ \n"); return DIV;}
"%"							{if (debug) printf ("/ \n"); return MOD;}
"+="  						{if (debug) printf ("+= \n"); return PLUSEQ; }
"-="  						{if (debug) printf ("-= \n"); return MINUSEQ; }
"*="  						{if (debug) printf ("*= \n"); return STAREQ; }
"/="  						{if (debug) printf ("/= \n"); return DIVEQ; }
"%="  						{if (debug) printf ("MODEQ \n"); return MODEQ; }
"^"  						{if (debug) printf ("^ \n"); return XOR; }
"^="  						{if (debug) printf ("^= \n"); return XOREQ; }
"&"  						{if (debug) printf ("& \n"); return AND; }
"&="  						{if (debug) printf ("&= \n"); return ANDEQ; }
"~"  						{if (debug) printf ("~ \n"); return TILDE; }
"!"  						{if (debug) printf ("! \n"); return EXCL; }
"|"  						{if (debug) printf ("| \n"); return OR; }
"|="  						{if (debug) printf ("|= \n"); return OREQ; }
"<"  						{if (debug) printf ("< \n"); return LT; }
">"  						{if (debug) printf ("> \n"); return GT; }
"<<"  						{if (debug) printf ("<< \n"); return LTLT; }
">>"  						{if (debug) printf (">> \n"); return GTGT; }
">>=" 						{if (debug) printf (">>= \n"); return GTGTEQ; }
"<<=" 						{if (debug) printf ("<<= \n"); return LTLTEQ; }
"=="  						{if (debug) printf ("== \n"); return EQEQ; }
"!="  						{if (debug) printf ("!= \n"); return NOTEQ; }
"<="  						{if (debug) printf ("<= \n"); return LEQ; }
">="  						{if (debug) printf (">= \n"); return GEQ; }
"&&"  						{if (debug) printf ("&& \n"); return ANDAND; }
"||"  						{if (debug) printf ("|| \n"); return OROR; }
"++"  						{if (debug) printf ("++ \n"); return PLUSPLUS; }
"--"  						{if (debug) printf ("-- \n"); return MINUSMINUS; }	
"var"						{if (debug) printf ("VAR \n"); return VAR;}		
<<EOF>>     				{if (debug) printf ("EOF \n"); return END_OF_FILE;}
{IDFF}						{if (debug) printf ("identifier \n"); set_idf_attributes(yytext, yylineno);	return IDF;}
.							{if (debug) printf( "ERRORLEX(%s) ", yytext );set_token_attributes(yylineno);}

%%
