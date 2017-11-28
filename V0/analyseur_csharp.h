#ifndef ANALYSEUR_CSHARP_H
#define ANALYSEUR_CSHARP_H
#include <stdio.h>
#include <stdlib.h>

typedef enum {false=0, true=1} boolean;

typedef enum{

	ABSTRACT,
	AS,
	BASE, 	
	BOOL,
	BREAK,
	BYTE, 	
	CASE, 	
	CATCH,
	CHAR, 	
	CHECKED, 	
	CLASS, 	
	CONST,
	CONTINUE, 	
	DECIMAL, 	
	DEFAULT, 	
	DELEGATE,
	DO, 	
	DOUBLE, 	
	ELSE, 	
	ENUM,
	EVENT, 	
	EXPLICIT, 	
	EXTERN, 	
	FALSE,
	FINALLY, 	
	FIXED, 	
	FLOAT, 	
	FOR,
	FOREACH, 	
	GOTO, 	
	IF, 	
	IMPLICIT,
	IN,	
	INT, 	
	INTERFACE,
	INTERNAL, 		
	IS, 	
	LOCK, 	
	LONG,
	NAMESPACE, 	
	NEW, 		
	NNULL, 	
	OBJECT,
	OPERATOR, 		
	OUT, 
	OVERRIDE,
	PARAMS, 	
	PRIVATE, 	
	PROTECTED, 	
	PUBLIC,
	READONLY, 	
	REF, 	
	RETURN, 	
	SBYTE,
	SEALED, 		
	SHORT, 	
	SIZEOF, 	
	STACKALLOC,
	STATIC, 	
	STRING,
	STRUCT,
	SWITCH,
	THIS, 	
	THROW, 	
	TRUE, 	
	TRY,
	TYPEOF, 	
	UINT, 	
	ULONG, 	
	UNCHECKED,
	UNSAFE, 	
	USHORT, 	
	USING, 	
	VIRTUAL, 	
	VOID, 	
	VOLATILE, 	
	WHILE,
	IDF,
	BOPEN,
	BCLOSE,
	EQEQ,
	EQ,
	PLUS,
	MINUS,
	MULT,
	DIV,
	PLUSEQ,
	MINUSEQ,
	LEFTBRACKET,
	RIGHTBRACKET,
	PVIRG,
	VIRG,
	PCLOSE,
	POPEN,
	STAREQ,
	DIVEQ,
	MODEQ,
	XOREQ,
	ANDEQ,
	OREQ,
	LTLT,
	GTGT,
	GTGTEQ,
	LTLTEQ,
	NOTEQ,
	LEQ,
	GEQ,
	ANDAND,
	OROR,
	PLUSPLUS,
	MINUSMINUS,
	DOUBLENUMBER,
	INTNUMBER,
	VAR


} typetoken;




/*
type =
	value_type
	 | reference_type
	 | type_parameter
	 | type_unsafe.
*/

boolean _type();
/*
value_type =
	struct_type
	 | enum_type.*/
boolean _value_type();
/*
struct_type =
	type_name
	 | simple_type
	 | nullable_type.*/
boolean _struct_type();

/*
simple_type =
	numeric_type
	 | 'bool'.*/
boolean _simple_type();

/*
numeric_type =
	integral_type
	 | floating_point_type
	 | 'decimal'.*/
boolean _numeric_type();
/*
integral_type =
	'sbyte'
	 | 'byte'
	 | 'short'
	 | 'ushort'
	 | 'int'
	 | 'uint'
	 | 'long'
	 | 'ulong'
	 | 'char'.*/
boolean _integral_type();

/*floating_point_type =
	'float'
	 | 'double'.*/
boolean _floating_point_type();

/*
declaration_statement =
	local_variable_declaration ';'
	 | local_constant_declaration ';'.*/

boolean _declaration_statement();
/*
local_variable_declaration =
	local_variable_type local_variable_declarators.*/


boolean _local_variable_declaration();
/*
local_variable_type =
	type
	 | 'var'.*/

boolean _local_variable_type();

/*
local_variable_declarators =
	local_variable_declarator local_variable_declarators_aux .*/

boolean _local_variable_declarators();
/*local_variable_declarators_aux = 
	',' local_variable_declarator local_variable_declarators_aux | eps .*/

boolean _local_variable_declarators_aux();

/*local_variable_declarator =
	identifier
	 | identifier '=' local_variable_initializer.*/

boolean _local_variable_declarator();

/*
local_variable_initializer =
	expression
	 | array_initializer
	 | local_variable_initializer_unsafe.*/

boolean _local_variable_initializer();

/*
expression =
	non_assignment_expression
	 | assignment;*/
boolean _expression();
/*
assignment =
	unary_expression, assignment_operator, expression;
*/

boolean _assignment();

/*assignment_operator =
	'='                                     EQ
	 | '+='									PLUSEQ
	 | '-='									MINUSEQ
	 | '*='									STAREQ
	 | '/='									DIVEQ
	 | '%='									MODEQ
	 | '&='									ANDEQ
	 | '|='									OREQ
	 | '^='									XOREQ
	 | '<<='								LTLTEQ
	 | right_shift_assignment;				GTGTEQ*/


boolean _assignment_operator();
/*unary_expression =
	primary_expression
	 | '+', unary_expression
	 | '-', unary_expression
	 | '!', unary_expression
	 | '~', unary_expression
	 | pre_increment_expression
	 | pre_decrement_expression
	 | cast_expression
	 | unary_expression_unsafe;*/

boolean _unary_expression();

/*
pre_increment_expression =
	'++', unary_expression;
pre_decrement_expression =
	'--', unary_expression;
cast_expression =
	'(', type, ')', unary_expression;*/


/*
primary_expression =
	primary_no_array_creation_expression
	 | array_creation_expression;*/

boolean _primary_expression();
/*
primary_no_array_creation_expression =
	literal
	 | simple_name
	 | parenthesized_expression
	 | member_access
	 | invocation_expression
	 | element_access
	 | this_access
	 | base_access
	 | post_increment_expression
	 | post_decrement_expression
	 | object_creation_expression
	 | delegate_creation_expression
	 | anonymous_object_creation_expression
	 | typeof_expression
	 | checked_expression
	 | unchecked_expression
	 | default_value_expression
	 | anonymous_method_expression
	 | primary_no_array_creation_expression_unsafe;*/

boolean _primary_no_array_creation_expression();
/*
literal =
	boolean_literal
	 | integer_literal
	 | real_literal
	 | character_literal
	 | string_literal
	 | null_literal;
*/
boolean _literal();

/*
flex -i --yylineno analyseur_csharp.l
gcc -c analyseur_csharp.c
gcc -c lex.yy.c
gcc -o csharpc lex.yy.o  analyseur_csharp.o -lfl
*/

#endif