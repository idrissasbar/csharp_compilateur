
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"analyseur_csharp.h"

extern boolean debug;

extern int yylex();
extern int yylineno;
extern char *yytext;


typetoken token;

//varvalueType var;

boolean follow_token=false;

typetoken _lire_token(){

	if(follow_token){
		follow_token = false; 
		return token; 
	}else{
	return (typetoken) yylex();
	}
}

/*
type =
	value_type
	 | reference_type
	 | type_parameter
	 | type_unsafe.
*/

boolean _type(){
	boolean result;

	if (_value_type())	
	{
		result=true;
	}else{
		
		result=false;

	}
	return result;
}

/*
value_type =
	struct_type
	 | enum_type.*/
boolean _value_type(){
	boolean result;

	if (_struct_type())
	{
		result=true;
	}else{

		result=false;
	}

	return result;
}

/*
struct_type =
	type_name
	 | simple_type
	 | nullable_type.*/
boolean _struct_type(){
	boolean result;

	if (_simple_type())
	{
		result=true;	
	}else{
		result=false;
	}

	return result;
}

/*
simple_type =
	numeric_type
	 | 'bool'.*/
boolean _simple_type(){
	boolean result;

		if (token==BOOL)
		{
			result=true;
		}else{
			if (_numeric_type())
			{
				result=true;
			}else{
				result=false;
			}
		}
	return result;
}

/*
numeric_type =
	integral_type
	 | floating_point_type
	 | 'decimal'.*/
boolean _numeric_type(){
	boolean result;

	if (token==DECIMAL)
	{
		result=true;
	}else{
		if (_integral_type())
		{
			result=true;
		}else{
			if (_floating_point_type())
			{
				result=true;
			}else{

				result=false;
				
			}
			
		}
	}

	return result;
}

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
boolean _integral_type(){
	boolean result;
     
    switch(token){
    	case SBYTE : result = true; 

    				break;
    	case BYTE : result = true;

    				break;
    	case SHORT : result = true;

    				break;
    	case USHORT : result = true;

    				break;
    	case INT : result = true;

    				break;
    	case UINT : result = true;

    				break;
    	case LONG : result = true;

    				break;
    	case ULONG : result = true;

    				break;
    	case CHAR : result = true;

    				break;
    	default : result = false;

    }

	return result;
}

/*floating_point_type =
	'float'
	 | 'double'.*/
boolean _floating_point_type(){
	boolean result;
	if (token == FLOAT) {
		result = true;
	}else{
		if (token == DOUBLE) {
			result = true;
		}else{
			result = false;
		} 
	}

	return result;
}

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

boolean _declaration_statement(){
	boolean result;
	if (debug) printf ("%s \n ","dec");
	if (_local_variable_declaration())
	{
		token=_lire_token();
		if (token==PVIRG)
		{
			result=true;
		}else{

			result=false;
		}
	}else{
		result=false;
	}
	return result;
}

/*
local_variable_declaration =
	local_variable_type local_variable_declarators.*/


boolean _local_variable_declaration(){
	boolean result;
	if (debug) printf ("%s \n ","loc_var_dec");
	if (_local_variable_type())
	{
		token=_lire_token();
		if (_local_variable_declarators())
		{
			result=true;
		}else{
			result=false;
		}
	}else{
		result=false;
	}
	return result;
}
/*
local_variable_type =
	type
	 | 'var'.*/

boolean _local_variable_type(){
	boolean result;
		if (debug) printf ("%s \n ","loc_var_type");
		if (token==VAR)
		{
			result=true;
		}else{
			if (_type())
			{				
				result=true;
			}else{
				result=false;
			}
		}
	return result;
}

/*
local_variable_declarators =
	local_variable_declarator local_variable_declarators_aux .*/

boolean _local_variable_declarators(){
	boolean result;
	if (debug) printf ("%s \n ","loc_var_dec_aux");

	if (_local_variable_declarator())
	{
		token=_lire_token();

		if (_local_variable_declarators_aux())
		{		
			result=true;
		}else{

			result=false;
		}

	}else{
		result=false;
	}
	return result;
}
/*local_variable_declarators_aux = 
	',' local_variable_declarator local_variable_declarators_aux | eps .*/

boolean _local_variable_declarators_aux(){
	boolean result;
if (debug) printf ("%s \n ","local_variable_declarators_aux");
	if (token==PVIRG)
	{ 
		result=true;
		follow_token=true;
	}else{
		if (token==VIRG)
		{
		
		token=_lire_token();
		if (_local_variable_declarator())	
		{
			token=_lire_token();
			if (_local_variable_declarators())
			{
				result=true;
			}else{
				result=false;
			}

		}else{
			result=false;
		}
		}else{
			result=false;
		}
	}
	return result;
}

/*local_variable_declarator =
	identifier
	 | identifier '=' local_variable_initializer.*/

boolean _local_variable_declarator(){
	boolean result;
if (debug) printf ("%s \n ","_local_variable_declarator");
	if (token==PVIRG || token==VIRG)
	{
		follow_token=true;
		result=true;
	}else{
	if (token==IDF)
	{
		token=_lire_token();
		if (token==EQ)
		{
			token=_lire_token();
			if (_local_variable_initializer())
			{
				result=true;
			}else{
				result=false;
			}
			
		}else{
			follow_token=true;
			result=true;
		}
		
	}else{
		result=false;
	}
}
	return result;
}

/*
local_variable_initializer =
	expression
	 | array_initializer
	 | local_variable_initializer_unsafe.*/

boolean _local_variable_initializer(){
	boolean result;
if (debug) printf ("%s \n ","_local_variable_initializer");
	if (_expression())	
	{
		result=true;
	}else{
		result=false;
	}
	return result;
}

/*
expression =
	non_assignment_expression
	 | assignment;*/
boolean _expression(){
	boolean result;
if (debug) printf ("%s \n ","_expression");
	if (_assignment())
	{
		result=true;
	}else{
		result=false;
	}
	return result;
}

/*
assignment =
	unary_expression, assignment_operator, expression;
*/

boolean _assignment(){
	boolean result;
if (debug) printf ("%s \n ","_assignment");
	if (_unary_expression())
	{
		token=_lire_token();
		if (_assignment_operator())
		{
			token=_lire_token();
			if (_expression())
			{
				result=true;
			}else{
				result=false;
			}
		}
	}
	return result;
}

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


boolean _assignment_operator(){
	boolean result;
if (debug) printf ("%s \n ","_assignment_operator");
	switch(token){
		case EQ : result =true;
					break;
		case PLUSEQ : result =true;
					break;
		case MINUSEQ : result =true;
					break;
		case STAREQ : result =true;
					break;
		case DIVEQ : result =true;
					break;
		case MODEQ : result =true;
					break;
		case ANDEQ : result =true;
					break;
		case OREQ : result =true;
					break;
		case XOREQ : result =true;
					break;
		case LTLTEQ : result =true;
					break;
		case GTGTEQ : result =true;
					break;
		default : result =false ;

	}


	return result;
}
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

boolean _unary_expression(){
	boolean result;
if (debug) printf ("%s \n ","_unary_expression");
	if (_primary_expression())
	{
		result=true;
	}else{
		result=false;
	}
	return result;
}

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

boolean _primary_expression(){
	boolean result;
if (debug) printf ("%s \n ","_primary_expression");
	if (_primary_no_array_creation_expression())	
	{
		result=true;
	}else{
		result=false;
	}
	return result;
}
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

boolean _primary_no_array_creation_expression(){
	boolean result;
if (debug) printf ("%s \n ","_primary_no_array_creation_expression");
	if (_literal())
	{
		result=true;
	}else{
		result=false;
	}

	return result;
}
/*
literal =
	boolean_literal
	 | integer_literal
	 | real_literal
	 | character_literal
	 | string_literal
	 | null_literal;
*/
boolean _literal(){
	boolean result;
if (debug) printf ("%s \n ","_literal");

	if (token==FALSE)
	{
		result=true;
	}else{
		if (token==TRUE)
		{
			result=true;
		}else{
			if (token==INTNUMBER)
			{
				result=true;
			}else{
				if (token==DOUBLENUMBER)
				{
					result=true;
				}else{
					result=false;
				}

			}
		}
	}


	return result;
}

/*  driss asbar ______________________________________________*/

/*expression =
	non_assignment_expression
	 | assignment.
non_assignment_expression =
	conditional_expression
	 | lambda_expression
	 | query_expression.
constant_expression =
	expression.
boolean_expression =
	expression.
*/

/***********************************************************************/
/*
literal =
	boolean_literal
	 | integer_literal
	 | real_literal
	 | character_literal
	 | string_literal
	 | null_literal.
boolean_literal =
	'true'
	 | 'false'.
integer_literal =
	decimal_integer_literal
	 | hexadecimal_integer_literal.
decimal_integer_literal =
	decimal_digits [integer_type_suffix].
decimal_digits =
	decimal_digit
	 | decimal_digits decimal_digit.
decimal_digit =
	'0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'.
integer_type_suffix =
	'U' | 'u' | 'L' | 'l' | 'UL' | 'Ul' | 'uL' | 'ul' | 'LU' | 'Lu' | 'lU' | 'lu'.
hexadecimal_integer_literal =
	'0x' hex_digits [integer_type_suffix]
	 | '0X' hex_digits [integer_type_suffix].
hex_digits =
	hex_digit
	 | hex_digits hex_digit.
hex_digit =
	'0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
	 | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f'.
real_literal =
	decimal_digits '.' decimal_digits [exponent_part] [real_type_suffix]
	 | '.' decimal_digits [exponent_part] [real_type_suffix]
	 | decimal_digits exponent_part [real_type_suffix]
	 | decimal_digits real_type_suffix.
exponent_part =
	'e' [sign] decimal_digits
	 | 'E' [sign] decimal_digits.
sign =
	'+' | '-'.
real_type_suffix =
	'F' | 'f' | 'D' | 'd' | 'M' | 'm'.
character_literal =
	"'" character "'".
character =
	single_character
	 | simple_escape_sequence
	 | hexadecimal_escape_sequence
	 | unicode_escape_sequence.
single_character = .

simple_escape_sequence =
	"\'" | '\"' | '\\' | '\0' | '\a' | '\b' | '\f' | '\n' | '\r' | '\t' | '\v'.

hexadecimal_escape_sequence =
	'\x' hex_digit [hex_digit] [hex_digit] [hex_digit].


string_literal =
	regular_string_literal
	 | verbatim_string_literal.

regular_string_literal =
	'"' [regular_string_literal_characters] '"'.

regular_string_literal_characters =
	regular_string_literal_character
	 | regular_string_literal_characters regular_string_literal_character.

regular_string_literal_character =
	single_regular_string_literal_character
	 | simple_escape_sequence
	 | hexadecimal_escape_sequence
	 | unicode_escape_sequence.

single_regular_string_literal_character = .
verbatim_string_literal =
	'@"' [verbatim_string_literal_characters] '"'.

verbatim_string_literal_characters =
	verbatim_string_literal_character
	 | verbatim_string_literal_characters verbatim_string_literal_character.

verbatim_string_literal_character =
	single_verbatim_string_literal_character
	 | quote_escape_sequence.

single_verbatim_string_literal_character = .
quote_escape_sequence =
	'""'.

null_literal =
	'null'.

/********************************************************************************/

 
/*statement =
	labeled_statement
	 | declaration_statement
	 | embedded_statement.*/

boolean _statement(){
	boolean result;

	
		if (_declaration_statement())
		{
			result=true;
		}else{
			if (_embedded_statement())
			{
				result=true;
			}else{

				result=false;
			}

		}


	return result;
}

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


boolean _embedded_statement(){
	boolean result;


	return result;
}

/*block =
	'{' [statement_list] '}'.*/

boolean 

/*statement_list =
	statement
	 | statement_list statement.*/

/*empty_statement = ';'.*/



/*labeled_statement = identifier ':' statement.*/

/*expression_statement =
	statement_expression ';'.*/


/*statement_expression =
	invocation_expression
	 | object_creation_expression
	 | assignment
	 | post_increment_expression
	 | post_decrement_expression
	 | pre_increment_expression
	 | pre_decrement_expression.*/











/* zakaria                               */

/*selection_statement =
	if_statement
	 | switch_statement.*/

/*if_statement =
	'if' '(' boolean_expression ')' embedded_statement
	 | 'if' '(' boolean_expression ')' embedded_statement 'else' embedded_statement.*/

/*switch_statement =
	'switch' '(' expression ')' switch_block.*/

/*switch_block =
	'{' [switch_sections] '}'.*/

/*switch_sections =
	switch_section
	 | switch_sections switch_section.*/

/*switch_section =
	switch_labels statement_list.*/

/******* switch_labels =
	   		switch_label
	 		| switch_labels switch_label.*/


/*switch_labels =
	   		switch_label switch_labels_aux
	 		*/

/*switch_labels_aux = switch_label switch_labels_aux | eps */

/*switch_label =
	'case' constant_expression ':'
	 | 'default' ':'.*/
	 

/*   idriss ait hafid ________________________________________________________________*/

/*iteration_statement =
	while_statement
	 | do_statement
	 | for_statement
	 | foreach_statement.*/

/*while_statement =
	'while' '(' boolean_expression ')' embedded_statement.*/

/*do_statement =
	'do' embedded_statement 'while' '(' boolean_expression ')' ';'.*/

/* abad mohamed zayd  ________________________________________________________________*/

/*for_statement =
	'for' '(' [for_initializer] ';' [for_condition] ';' [for_iterator] ')' embedded_statement.*/

boolean _for_statement(){
	
	boolean result = false; 
	
	token = _lire_token();
	
	if(token == FOR){
		
		token = _lire_token();
		
		if(token == POPEN){

			if(_for_initializer() || !_for_initializer()){

				token = _lire_token();

				if(token == PVIRG){

					if(_for_condition() || !_for_condition()){

						token = _lire_token();

						if(token == PVIRG){

							if(_for_iterator() || !_for_iterator()){

								token = _lire_token();

								if(token == PCLOSE){

									if(_embedded_statement()){

										result = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return result; 
}


/*for_initializer =
	local_variable_declaration
	 | statement_expression_list.*/

boolean _for_initializer(){

	boolean result = false;

	if(_local_variable_declaration()){

		result = true;
	}

	else{

		if(_statement_expression_list()){

			result = true; 
		}
	}

	return result; 
}

/*for_condition =
	boolean_expression.*/

boolean _for_condition(){

	boolean result = false; 

	if(_boolean_expression()){ //boolean_expression ma3reftch finahiya 

		result = true; 
	}

	return result; 
}

/*for_iterator =
	statement_expression_list.*/

boolean _for_iterator(){

	boolean result = false; 

	if(_statement_expression_list()){

		result = true; 
	}

	return result; 

}

/*statement_expression_list =
	statement_expression
	 | statement_expression_list ',' statement_expression.

	En éliminant la récursivité gauche, j'ai obtenu : 

	statement_expression_list = statement_expression statement_expression_list_aux
	statement_expression_list_aux = ',' statement_expression statement_expression_list_aux
											| statement_expression

	*/

boolean _statement_expression_list(){

	boolean result = false;

	if(_statement_expression()){

		if(_statement_expression_list_aux()){

			result = true; 

		}
	}

	return result; 
}

boolean _statement_expression_list_aux(){

	boolean result = false; 

	token  = _lire_token();

	if(_statement_expression()){

		result = true; 
	}
	else{
		if(token == VIRG){

			if(_statement_expression()){

				if(_statement_expression_list_aux()){

					result = true; 
				}
			}
		}
	}

	return result; 
	
}

int main(){
	token=_lire_token();
	if(_declaration_statement()){
		printf("ok\n");
	}else{
		printf("nno\n");
	}
}

