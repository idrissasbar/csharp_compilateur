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
	VAR,
	POINTINTER,
	DOUBLEDOT,
	NULLCOALESCING,
	GT,
	LT,
	OR,
	AND,
	XOR,
	MOD,
	EXCL,
	TILDE,
	POINT,
	PARTIAL,
	DYNAMIC,
	REMOVE,
	END_OF_FILE




} typetoken;






typetoken _lire_token();

/*
type =
	value_type
	 | reference_type
	 | type_parameter
	 | type_unsafe.
*/



/*********************argument_list =
									argument
									 | argument_list, ',', argument;*/
/* argument_list = argument argument_list_aux*/

boolean _argument_list();

/*argument_list_aux = ',' argument argument_list_aux | eps */

boolean _argument_list_aux();
/*argument =
	[argument_name], argument_value;*/
/*
argument = argument_name argument_value | argument_value */

boolean _argument();

/*argument_name =
	identifier, ':';*/
boolean _argument_name();

/*argument_value =
	expression
	 | 'ref', variable_reference
	 | 'out', variable_reference;*/

boolean _argument_value();

boolean _variable_reference();
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
nullable_type =
	non_nullable_value_type '?'.
non_nullable_value_type =
	type.
enum_type =
	type_name.
reference_type =
	class_type
	 | interface_type
	 | array_type
	 | delegate_type.
class_type =
	type_name
	 | 'object'
	 | 'dynamic'
	 | 'string'.
interface_type =
	type_name.
delegate_type =
	type_name.
type_argument_list =
	'<' type_arguments '>'.
type_arguments =
	type_argument
	 | type_arguments ',' type_argument.
type_argument =
	type.
*/
/**************************************************************************/
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

/******************local_variable_declarator =
					identifier
	 				|identifier '=' local_variable_initializer.*/



/*local_variable_declarator = identifier local_variable_declarator_aux*/

boolean _local_variable_declarator();


/*local_variable_declarator_aux= '=' local_variable_initializer | eps*/

boolean _local_variable_declarator_aux();

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


/*simple_name =
	identifier [type_argument_list]. */

boolean 	_simple_name();

/*parenthesized_expression =
	'(' expression ')'. */


boolean 	_parenthesized_expression();

/*  driss asbar ______________________________________________*/



/*
non_assignment_expression =
	conditional_expression
	 | lambda_expression
	 | query_expression.*/

boolean _non_assignment_expression();

/*************multiplicative_expression =
								unary_expression
								 | multiplicative_expression '*' unary_expression
								 | multiplicative_expression '/' unary_expression
								 | multiplicative_expression '%' unary_expression.*/

/*multiplicative_expression = unary_expression  multiplicative_expression_aux*/

boolean 	_multiplicative_expression();

/*multiplicative_expression_aux =
							'*' unary_expression multiplicative_expression_aux
							|'/' unary_expression multiplicative_expression_aux
							|'%' unary_expression multiplicative_expression_aux
							|eps*/

boolean _multiplicative_expression_aux();

/********************additive_expression =
								multiplicative_expression
								 | additive_expression '+' multiplicative_expression
								 | additive_expression '-' multiplicative_expression.*/

/* additive_expression = multiplicative_expression additive_expression_aux*/


boolean 	_additive_expression();

/*additive_expression_aux =
						 '+' multiplicative_expression additive_expression_aux
						|'-' multiplicative_expression additive_expression_aux
						|eps*/

boolean 	 _additive_expression_aux();

/*******************shift_expression =
									additive_expression
									 | shift_expression '<<' additive_expression
									 | shift_expression right_shift additive_expression.*/

/*shift_expression = additive_expression shift_expression_aux */


boolean 	_shift_expression();

/*shift_expression_aux = 
					'<<' additive_expression shift_expression_aux
					'>>' additive_expression shift_expression_aux
					|eps*/

boolean _shift_expression_aux();

/******************************************relational_expression =
														shift_expression
														 | relational_expression '<' shift_expression
														 | relational_expression '>' shift_expression
														 | relational_expression '<=' shift_expression
														 | relational_expression '>=' shift_expression
														 | relational_expression 'is' type
														 | relational_expression 'as' type.*/


/* relational_expression = 
							  shift_expression relational_expression_aux
							| type relational_expression_aux_aux*/

boolean 	_relational_expression();

/* relational_expression_aux =
						   '<' shift_expression relational_expression_aux
					 	|  '>' shift_expression relational_expression_aux
					 	|  '<=' shift_expression relational_expression_aux
					 	|  '>=' shift_expression relational_expression_aux
					 	| eps */

boolean 	_relational_expression_aux();

/* relational_expression_aux_aux =
							 	|  'is' type relational_expression_aux_aux
						 		|  'as' type relational_expression_aux_aux
						 		| eps */

boolean 	_relational_expression_aux_aux();

/*******************************************equality_expression =
														relational_expression
														 | equality_expression '==' relational_expression
														 | equality_expression '!=' relational_expression.*/


/* equality_expression = relational_expression equality_expression_aux */

boolean 	_equality_expression();


/* equality_expression_aux =
							|  '==' relational_expression equality_expression_aux
							|  '!=' relational_expression equality_expression_aux
							| eps */

boolean 	_equality_expression_aux();


/*****************************************and_expression =
													equality_expression
													 | and_expression '&' equality_expression.*/

/*	and_expression = equality_expression and_expression_aux */

boolean 	_and_expression();

/* and_expression_aux =
						'&'	equality_expression and_expression_aux
						| eps */

boolean 	_and_expression_aux();

/****************************************exclusive_or_expression =
																and_expression
																 | exclusive_or_expression '^' and_expression.*/

/* exclusive_or_expression = and_expression exclusive_or_expression_aux */


boolean 	_exclusive_or_expression();
/* exclusive_or_expression_aux =
								'^' and_expression exclusive_or_expression_aux
								| eps */
boolean 	_exclusive_or_expression_aux();

/***************************************inclusive_or_expression =
																exclusive_or_expression
																 | inclusive_or_expression '|' exclusive_or_expression.*/



/*	inclusive_or_expression = exclusive_or_expression inclusive_or_expression_aux */

boolean 	_inclusive_or_expression();

/* inclusive_or_expression_aux = 
								'|' exclusive_or_expression inclusive_or_expression_aux
								| eps */

boolean 	_inclusive_or_expression_aux();

/***********************conditional_and_expression =
												inclusive_or_expression
												 | conditional_and_expression '&&' inclusive_or_expression.*/

/* conditional_and_expression = inclusive_or_expression conditional_and_expression_aux */

boolean 	_conditional_and_expression();

/* conditional_and_expression_aux = 
									'&&' inclusive_or_expression conditional_and_expression_aux
									| eps */

boolean 	_conditional_and_expression_aux();

/***************conditional_expression =
					null_coalescing_expression
	 				| null_coalescing_expression '?' expression ':' expression.*/


/*conditional_expression = null_coalescing_expression conditional_expression_aux*/

boolean 	_conditional_expression();

/*conditional_expression_aux='?' expression ':' expression | eps */

boolean _conditional_expression_aux();

/***************	null_coalescing_expression =
						conditional_or_expression
	 					| conditional_or_expression '??' null_coalescing_expression.*/

/*null_coalescing_expression  = conditional_or_expression null_coalescing_expression_aux*/

boolean 	_null_coalescing_expression();


/*null_coalescing_expression_aux= '??' null_coalescing_expression | eps.*/


boolean _null_coalescing_expression_aux();




/****************conditional_or_expression =
					conditional_and_expression
	 				| conditional_or_expression '||' conditional_and_expression.*/


/*conditional_or_expression = conditional_and_expression conditional_or_expression_aux.*/

boolean 	_conditional_or_expression();
/*conditional_or_expression_aux = '||' conditional_and_expression conditional_or_expression_aux | aps .*/

boolean 	_conditional_or_expression_aux();

/*constant_expression =
	expression.*/

boolean constant_expression();

/*boolean_expression =
	expression.
*/

boolean _boolean_expression();
 
/*statement =
	labeled_statement
	 | declaration_statement
	 | embedded_statement.*/

boolean _statement();

/*embedded_statement =
	block							*
	 | empty_statement				*
	 | expression_statement			*
	 | selection_statement			* 
	 | iteration_statement			*
	 | jump_statement				*
	 | try_statement
	 | checked_statement
	 | unchecked_statement
	 | lock_statement
	 | using_statement
	 | yield_statement
	 | embedded_statement_unsafe.*/


boolean _embedded_statement();


/*block =
	'{' [statement_list] '}'.*/

boolean _block();

/******************************************statement_list =
														statement
														 | statement_list statement.*/

/* statement_list = statement statement_list_aux */

boolean 	_statement_list();

/* statement_list_aux = 
						statement statement_list_aux
						| eps */

boolean 	_statement_list_aux();

/*empty_statement = ';'.*/

boolean 	_empty_statement();

/*labeled_statement = identifier ':' statement.*/

/*expression_statement =
	statement_expression ';'.*/
boolean _expression_statement();

/*statement_expression =
	invocation_expression
	 | object_creation_expression
	 | assignment
	 | post_increment_expression
	 | post_decrement_expression
	 | pre_increment_expression
	 | pre_decrement_expression.*/


boolean 	_statement_expression();


/* zakaria   ****************** DONE ********************    */

/*selection_statement =
	if_statement
	 | switch_statement.*/

boolean _selection_statement();


/*if_statement =
	'if' '(' boolean_expression ')' embedded_statement
	 | 'if' '(' boolean_expression ')' embedded_statement 'else' embedded_statement.*/

boolean _if_statement();
/*switch_statement =
	'switch' '(' expression ')' switch_block.*/
/*if_statement_aux= 'else' embedded_statement | epsilon*/
boolean _if_statement_aux();

boolean _switch_statement();
/*switch_block =
	'{' [switch_sections] '}'.*/

boolean _switch_block();

/****** switch_sections =
	switch_section
	 | switch_sections switch_section.*/

/*switch_sections = switch_section switch_sections_aux.*/

boolean _switch_sections();

/*switch_sections_aux = switch_section switch_sections_aux | eps */
	
boolean _switch_sections_aux();

/*switch_section =
	switch_labels statement_list.*/

boolean _switch_section();

/****** switch_labels =
	   		switch_label
	 		| switch_labels switch_label.*/

/*switch_labels =
	   		switch_label switch_labels_aux
	 		*/

boolean _switch_labels();

/*switch_labels_aux = switch_label switch_labels_aux | eps */

boolean _switch_labels_aux();


/*switch_label =
	'case' constant_expression ':'
	 | 'default' ':'.*/
	 
boolean _switch_label();
/*  **************** Fin Zakaria ********************  */
	 

/*   idriss ait hafid ________________________________________________________________*/

/*iteration_statement =
	while_statement
	 | do_statement
	 | for_statement
	 | foreach_statement.*/

boolean _iteration_statement();

/*while_statement =
	'while' '(' boolean_expression ')' embedded_statement.*/

boolean _while_statement();
/*do_statement =
	'do' embedded_statement 'while' '(' boolean_expression ')' ';'.*/

boolean _do_statement();


/* abad mohamed zayd  ________________________________________________________________*/

/*for_statement =
	'for' '(' [for_initializer] ';' [for_condition] ';' [for_iterator] ')' embedded_statement.*/

boolean _for_statement();


/*for_initializer =
	local_variable_declaration
	 | statement_expression_list.*/

boolean _for_initializer();
/*for_condition =
	boolean_expression.*/

boolean _for_condition();

/*for_iterator =
	statement_expression_list.*/

boolean _for_iterator();

/*statement_expression_list =
	statement_expression
	 | statement_expression_list ',' statement_expression.

	En éliminant la récursivité gauche, j'ai obtenu : 

	statement_expression_list = statement_expression statement_expression_list_aux
	
	statement_expression_list_aux = ',' statement_expression statement_expression_list_aux
											| statement_expression
	*/

boolean _statement_expression_list();

boolean _statement_expression_list_aux();

/*
flex -i --yylineno analyseur_csharp.l
gcc -c analyseur_csharp.c
gcc -c lex.yy.c
gcc -o csharpc lex.yy.o  analyseur_csharp.o -lfl
*/
void set_idf_attributes(char *name, int line);
void set_number_attributes(double value);
void set_token_attributes(int line);
#endif