
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

	if (debug) printf ("%s \n ","_type");


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

	if (debug) printf ("%s \n ","_value_type");

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

			if (debug) printf ("%s \n ","_struct_type");

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

			if (debug) printf ("%s \n ","_simple_type");


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

	if (debug) printf ("%s \n ","_numeric_type");

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
     
		if (debug) printf ("%s \n ","_integral_type");


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

		if (debug) printf ("%s \n ","_floating_point_type");


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
	if (debug) printf ("%s \n ","_declaration_statement");
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
	if (debug) printf ("%s \n ","_local_variable_declaration");
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
			if (_local_variable_declarators())	
			{
				/*token=_lire_token();
				if (_local_variable_declarators())
				{*/
					result=true;
				/*}else{
					result=false;
				}*/

			}else{
				result=false;
			}
		}else{
			result=false;
		}
	}
	return result;
}

/******************local_variable_declarator =
					identifier
	 				|identifier '=' local_variable_initializer.*/



/*local_variable_declarator = identifier local_variable_declarator_aux*/

boolean _local_variable_declarator(){
	boolean result;
if (debug) printf ("%s \n ","_local_variable_declarator");
	
	if (token==IDF){

		token=_lire_token();

		if (_local_variable_declarator_aux())
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


/*local_variable_declarator_aux= '=' local_variable_initializer | eps*/

boolean _local_variable_declarator_aux(){
	boolean result;

	if (debug) printf ("%s \n ","_local_variable_declarator_aux");

	if (token==VIRG || token==PVIRG)
	{
		result=true;
		follow_token=true;
	}else{

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

if (debug) printf ("%s \n ","FIN _local_variable_initializer");

	return result;
}

/*
expression =
	non_assignment_expression
	 | assignment;*/
boolean _expression(){
	boolean result;
if (debug) printf ("%s \n ","_expression");
	if (_non_assignment_expression())
	{
		result=true;
	}else{

		if (_assignment())
		{
			result=true;
		}else{

		result=false;
			
		}
	}

	if (debug) printf ("%s \n ","FIN _expression");

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

		if (_simple_name())
		{
			result=true;
		}else{

			if (_parenthesized_expression())
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



/*simple_name =
	identifier [type_argument_list]. */

boolean 	_simple_name(){
	boolean result;

	if (debug) printf ("%s \n ","_simple_name");

			if (token==IDF)
			{
				result=true;
			}else{

				result=false;
			}
	return result;
}

/*parenthesized_expression =
	'(' expression ')'. */


boolean 	_parenthesized_expression(){
	boolean result;

		if (debug) printf ("%s \n ","_parenthesized_expression");


	if (token==POPEN)
	{
		token=_lire_token();

		if (_expression())
		{
			token=_lire_token();

			if (token==PCLOSE)
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


	return result;
}

/*  driss asbar ______________________________________________*/



/*
non_assignment_expression =
	conditional_expression
	 | lambda_expression
	 | query_expression.*/

boolean _non_assignment_expression(){
	boolean result;

		if (debug) printf ("%s \n ","non_assignment_expression");


		if (_conditional_expression())
		{
			result=true;
		}else{

			result=false;

		}
	return result;
}


/*************multiplicative_expression =
								unary_expression
								 | multiplicative_expression '*' unary_expression
								 | multiplicative_expression '/' unary_expression
								 | multiplicative_expression '%' unary_expression.*/

/*multiplicative_expression = unary_expression  multiplicative_expression_aux*/

boolean 	_multiplicative_expression(){
	boolean result;


			if (debug) printf ("%s \n ","_multiplicative_expression");


		if (_unary_expression())
		{
			token=_lire_token();
			if (_multiplicative_expression_aux())
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

/*multiplicative_expression_aux =
							'*' unary_expression multiplicative_expression_aux
							|'/' unary_expression multiplicative_expression_aux
							|'%' unary_expression multiplicative_expression_aux
							|eps*/

boolean _multiplicative_expression_aux(){
	boolean result;

			if (debug) printf ("%s \n ","_multiplicative_expression_aux");


		if (token==PVIRG || token==PCLOSE || token==VIRG)
		{
			result=true;
			follow_token=true;
		}else{

			if (token==MULT)
			{
				token=_lire_token();

				if (_multiplicative_expression())
				{
					result=true;
				}else{

					result=false;
				}
			}else{

					if (token==DIV)
						{
							token=_lire_token();

								if (_multiplicative_expression())
								{
									result=true;
								}else{

									result=false;
								}
						}else{
								if (token==MOD)
								{
									token=_lire_token();

									if (_multiplicative_expression())
									{
											result=true;
									}else{

											result=false;
									}
								}else{


									result=false;

								}
				
						}
			}
		}

	return result;
}

/********************additive_expression =
								multiplicative_expression
								 | additive_expression '+' multiplicative_expression
								 | additive_expression '-' multiplicative_expression.*/

/* additive_expression = multiplicative_expression additive_expression_aux*/


boolean 	_additive_expression(){
	boolean result;

		if (debug) printf ("%s \n ","_additive_expression");

		if (_multiplicative_expression())
		{
			token=_lire_token();

			if (_additive_expression_aux())
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

/*additive_expression_aux =
						 '+' multiplicative_expression additive_expression_aux
						|'-' multiplicative_expression additive_expression_aux
						|eps*/

boolean 	 _additive_expression_aux(){
	boolean result;

			if (debug) printf ("%s \n ","_additive_expression_aux");


		if (token==PVIRG || token==PCLOSE || token==VIRG)
		{
			result=true;
			follow_token=true;
		}else{

			if (token==PLUS)
			{
				token=_lire_token();

					if (_additive_expression())
					{
						result=true;
					}else{

						result=false;
					}
			}else{
					if (token==MINUS)
					{
						token=_lire_token();

						if (_additive_expression())
						{
								result=true;
						}else{

								result=false;
						}
					}else{


						result=false;

					}
				}
			}

	return result;
}

/*******************shift_expression =
									additive_expression
									 | shift_expression '<<' additive_expression
									 | shift_expression right_shift additive_expression.*/

/*shift_expression = additive_expression shift_expression_aux */


boolean 	_shift_expression(){
	boolean result;

			if (debug) printf ("%s \n ","_shift_expression");


		if (_additive_expression())
		{
			token=_lire_token();

			if (_shift_expression_aux())
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

/*shift_expression_aux = 
					'<<' additive_expression shift_expression_aux
					'>>' additive_expression shift_expression_aux
					|eps*/

boolean _shift_expression_aux(){
	boolean result;

			if (debug) printf ("%s \n ","_shift_expression_aux");


		if (token==PVIRG || token==PCLOSE || token==VIRG)
		{
			result=true;
			follow_token=true;
			
		}else{
			if (token==LTLT)
			{
				token=_lire_token();

					if (_shift_expression())
					{
						result=true;
					}else{

						result=false;
					}
			}else{
					if (token==GTGT)
					{
						token=_lire_token();

						if (_shift_expression())
						{
								result=true;
						}else{

								result=false;
						}
					}else{


						result=false;

					}
				}
		}

	return result;
}

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

boolean 	_relational_expression(){
	boolean result;

		if (debug) printf ("%s \n ","_relational_expression");


		if (_shift_expression())
		{
			token=_lire_token();

			if (_relational_expression_aux())
			{
				result=true;
			}else{
				result=false;
			}
		}else{

			if (_type())
			{
				
				token=_lire_token();

				if (_relational_expression_aux_aux())
				{
					result=true;
				}else{

					result=false;
				}
			}else{

				result=false;
			}
		}

	return result;
}

/* relational_expression_aux =
						   '<' shift_expression relational_expression_aux
					 	|  '>' shift_expression relational_expression_aux
					 	|  '<=' shift_expression relational_expression_aux
					 	|  '>=' shift_expression relational_expression_aux
					 	| eps */

boolean 	_relational_expression_aux(){
	boolean result;

		if (debug) printf ("%s \n ","_relational_expression_aux");


	if (token==PVIRG || token==PCLOSE || token==VIRG) /** follows **/
	{
		result=true;
		follow_token=true;
	}else{

		if (token==LT)
		{
			token=_lire_token();

			if (_relational_expression())
			{
				result=true;
			}else{

					result=false;
			}
		}else{

			if (token==GT)
			{
				token=_lire_token();

				if (_relational_expression())
				{
					result=true;
				}else{

					result=false;
				}
			}else{


				if (token==LEQ)
				{
					token=_lire_token();

					if (_relational_expression())
					{
						result=true;
					}else{

						result=false;
					}
				}else{

							if (token==GEQ)
							{
								token=_lire_token();

								if (_relational_expression())
								{
									result=true;
								}else{

									result=false;
								}
							}else{
									result=false;
								}
					}

			}
		}
	}

	return result;
}

/* relational_expression_aux_aux =
							 	|  'is' type relational_expression_aux_aux
						 		|  'as' type relational_expression_aux_aux
						 		| eps */

boolean 	_relational_expression_aux_aux(){
	boolean result;



	return result;
}

/*******************************************equality_expression =
														relational_expression
														 | equality_expression '==' relational_expression
														 | equality_expression '!=' relational_expression.*/


/* equality_expression = relational_expression equality_expression_aux */

boolean 	_equality_expression(){
	boolean result;

			if (debug) printf ("%s \n ","_equality_expression");


		if (_relational_expression())
		{
			token=_lire_token();

			if (_equality_expression_aux())
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


/* equality_expression_aux =
							|  '==' relational_expression equality_expression_aux
							|  '!=' relational_expression equality_expression_aux
							| eps */

boolean 	_equality_expression_aux(){
	boolean result;

		if (debug) printf ("%s \n ","_equality_expression_aux");


		if (token==PVIRG || token==PCLOSE || token==VIRG)
		{
			result=true;
			follow_token=true;
		}else{

			if (token==EQEQ)
			{
				token=_lire_token();

				if (_equality_expression())
				{
					result=true;
				}else{
					result=false;
				}
			}else{

				if (token==NOTEQ)
				{
					token=_lire_token();

					if (_equality_expression())
					{
						result=true;
					}else{
						result=false;
					}
				}else{

					result=false;
				}
			}
		}

	return result;
}


/*****************************************and_expression =
													equality_expression
													 | and_expression '&' equality_expression.*/

/*	and_expression = equality_expression and_expression_aux */

boolean 	_and_expression(){
	boolean result;

		if (debug) printf ("%s \n ","_and_expression");

		if (_equality_expression())
		{
			token=_lire_token();

			if (_and_expression_aux())
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

/* and_expression_aux =
						'&'	equality_expression and_expression_aux
						| eps */

boolean 	_and_expression_aux(){
	boolean result;

			if (debug) printf ("%s \n ","_and_expression_aux");


		if (token==PVIRG || token==PCLOSE || token==VIRG)
		{
			result=true;
			follow_token=true;
		}else{

			if (token==AND)
			{
				token=_lire_token();

				if (_and_expression())
				{
					result=true;
				}else{

					result=false;
				}
			}else{

				result=false;
			}
		}

	return result;
}

/****************************************exclusive_or_expression =
																and_expression
																 | exclusive_or_expression '^' and_expression.*/

/* exclusive_or_expression = and_expression exclusive_or_expression_aux */


boolean 	_exclusive_or_expression(){
	boolean result;

		if (debug) printf ("%s \n ","_exclusive_or_expression");

		if (_and_expression())
		{
			token=_lire_token();

			if (_exclusive_or_expression_aux())
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

/* exclusive_or_expression_aux =
								'^' and_expression exclusive_or_expression_aux
								| eps */
boolean 	_exclusive_or_expression_aux(){
	boolean result;

		if (debug) printf ("%s \n ","exclusive_or_expression_aux");

		if (token==PVIRG || token==PCLOSE || token==VIRG)
		{
			result=true;
			follow_token=true;
		}else{

			if (token==XOR)
			{
				token=_lire_token();

				if (_exclusive_or_expression())
				{
					result=true;
				}else{

					result=false;
				}
			}else{

				result=false;
			}
		}

	return result;
}

/***************************************inclusive_or_expression =
																exclusive_or_expression
																 | inclusive_or_expression '|' exclusive_or_expression.*/



/*	inclusive_or_expression = exclusive_or_expression inclusive_or_expression_aux */

boolean 	_inclusive_or_expression(){
	boolean result;

			if (debug) printf ("%s \n ","_inclusive_or_expression");


		if (_exclusive_or_expression())
		{
			token=_lire_token();

			if (_inclusive_or_expression_aux())
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

/* inclusive_or_expression_aux = 
								'|' exclusive_or_expression inclusive_or_expression_aux
								| eps */

boolean 	_inclusive_or_expression_aux(){
	boolean result;

			if (debug) printf ("%s \n ","_inclusive_or_expression_aux");


		if (token==PVIRG || token==PCLOSE || token==VIRG)
		{
			result=true;
			follow_token=true;
		}else{

			if (token==OR)
			{
				token=_lire_token();

				if (_inclusive_or_expression())
				{
					result=true;
				}else{

					result=false;
				}
			}else{

				result=false;
			}
		}

	return result;
}

/***********************conditional_and_expression =
												inclusive_or_expression
												 | conditional_and_expression '&&' inclusive_or_expression.*/

/* conditional_and_expression = inclusive_or_expression conditional_and_expression_aux */

boolean 	_conditional_and_expression(){
	boolean result;
		if (debug) printf ("%s \n ","_conditional_and_expression");

		if (_inclusive_or_expression())
		{
			token=_lire_token();

			if (_conditional_and_expression_aux())
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

/* conditional_and_expression_aux = 
									'&&' inclusive_or_expression conditional_and_expression_aux
									| eps */

boolean 	_conditional_and_expression_aux(){
	boolean result;
		if (debug) printf ("%s \n ","_conditional_and_expression_aux");

			if (token==PVIRG || token==PCLOSE || token==VIRG)
			{
				result=true;
				follow_token=true;
			}else{

				if (token==ANDAND)
				{
					token=_lire_token();

					if (_conditional_and_expression())
					{
						result=true;
					}else{
						result=false;
					}
				}else{
					result=false;
				}

			}
	return result;
}

/***************conditional_expression =
					null_coalescing_expression
	 				| null_coalescing_expression '?' expression ':' expression.*/


/*conditional_expression = null_coalescing_expression conditional_expression_aux*/

boolean 	_conditional_expression(){
	boolean result;

			if (debug) printf ("%s \n ","_conditional_expression");


	 	if (_null_coalescing_expression())
	 	{
	 		token=_lire_token();
	 		if (_conditional_expression_aux())
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

/*conditional_expression_aux='?' expression ':' expression | eps */

boolean _conditional_expression_aux(){
	boolean result;

		if (debug) printf ("%s \n ","_conditional_expression_aux");

	if (token==PVIRG || token==VIRG	|| token==PCLOSE)
	{
		result=true;
		follow_token=true;
	}else{
	if (token==POINTINTER)
	{
		token=_lire_token();

		if (_expression())
		{
			token=_lire_token();
			if (token==DOUBLEDOT)
			{
				token=_lire_token();
				if (_expression())
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
}

	return result;
}

/***************	null_coalescing_expression =
						conditional_or_expression
	 					| conditional_or_expression '??' null_coalescing_expression.*/

/*null_coalescing_expression  = conditional_or_expression null_coalescing_expression_aux*/

boolean 	_null_coalescing_expression(){
	boolean result;

		if (debug) printf ("%s \n ","_null_coalescing_expression");

	if (_conditional_or_expression())
	{
		token=_lire_token();
		if (_null_coalescing_expression_aux())
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


/*null_coalescing_expression_aux= '??' null_coalescing_expression | eps.*/


boolean _null_coalescing_expression_aux(){
	boolean result;

			if (debug) printf ("%s \n ","_null_coalescing_expression_aux");


	if (token==POINTINTER || token==PVIRG || token==VIRG || token==PCLOSE)
	{
		follow_token=true;
		result=true;
	}else{

		if (token==NULLCOALESCING)
		{
			token=_lire_token();
			if (_null_coalescing_expression())
				{
					result=true;
				}else{

					result=false;
				}	
		}else{

			result=false;
		}
	}
	return result;
}





/****************conditional_or_expression =
					conditional_and_expression
	 				| conditional_or_expression '||' conditional_and_expression.*/


/*conditional_or_expression = conditional_and_expression conditional_or_expression_aux.*/

boolean 	_conditional_or_expression(){
	boolean result;

			if (debug) printf ("%s \n ","_conditional_or_expression");


		if (_conditional_and_expression())
		{
			token=_lire_token();
			if (_conditional_or_expression_aux())
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

/*conditional_or_expression_aux = 
								'||' conditional_and_expression conditional_or_expression_aux 
								| eps .*/

boolean 	_conditional_or_expression_aux(){
	boolean result;

			if (debug) printf ("%s \n ","_conditional_or_expression_aux");


		if (token==PVIRG || token==PCLOSE || token==VIRG)
		{
			result=true;
			follow_token=true;
		}else{


			if (token==OROR)
			{
				token=_lire_token();

				if (_conditional_or_expression())
				{
					result=true;
				}else{

					result=false;
				}
			}else{

				result=false;
			}
		}

	return result;
}

/*constant_expression =
	expression.*/

boolean _constant_expression(){
	boolean result;

			if (debug) printf ("%s \n ","_constant_expression");


	if (_expression())
	{
		result=true;
	}else{

		result=false;
	}

	return result;
}

/*boolean_expression =
	expression.
*/

boolean _boolean_expression(){
	boolean result;
		if (debug) printf ("%s \n ","_boolean_expression");

	if (_expression())
	{
		result=true;
	}else{

		result=false;
	}
	return result;
}

 
/*statement =
	labeled_statement
	 | declaration_statement
	 | embedded_statement.*/

boolean _statement(){
	boolean result;

			if (debug) printf ("%s \n ","_statement");

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

			if (debug) printf ("%s \n ","_embedded_statement");


		if (_block())
		{
			result=true;
		}else{

			if (_empty_statement())
			{
				result=true;
			}else{

				if (_expression_statement())
				{
					result=true;
				}else{
						
					if (_selection_statement())
					{
						result=true;
					}else{
						
						if (_iteration_statement())
						{
							result=true;
						}else{
						
							result=false;  /// les autres statements pour une autre version
			
						}
			
					}

			
				}
			
			}

		}

	return result;
}


/*block =
	'{' [statement_list] '}'.*/

boolean _block(){
	boolean result;
		if (debug) printf ("%s \n ","_block");

		if (token==BOPEN)
		{
			token=_lire_token();

			if (token=BCLOSE)
			{
				result=true;
			}else{

				if (_statement_list())
					{
						token=_lire_token();

						if (token==BCLOSE)
						{
							result=true;
						}else{
							result=false;
						}
					}else{
						result=false;
					}	

			}
		}else{
			result=false;
		}

	return result;
}

/******************************************statement_list =
														statement
														 | statement_list statement.*/

/* statement_list = statement statement_list_aux */

boolean 	_statement_list(){
	boolean result;

			if (debug) printf ("%s \n ","_statement_list");


		if (_statement())
		{
			token=_lire_token();

			if (_statement_list_aux())
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

/* statement_list_aux = 
						statement statement_list_aux
						| eps */

boolean 	_statement_list_aux(){
	boolean result;
		if (debug) printf ("%s \n ","_statement_list_aux");

		if (token==PVIRG || token==PCLOSE)
		{
			result=true;
			follow_token=true;
		}else{

			if (_statement_list())
			{
				result=true;
			}else{

				result=false;
			}
		}

	return result;
}

/*empty_statement = ';'.*/

boolean 	_empty_statement(){
	boolean result;

			if (debug) printf ("%s \n ","_empty_statement");


		if (token==PVIRG)
		{
			result=true;
		}else{

			result=false;
		}
	return result;
}

/*labeled_statement = identifier ':' statement.*/

/*expression_statement =
	statement_expression ';'.*/
boolean _expression_statement(){
	boolean result;
		if (debug) printf ("%s \n ","_expression_statement");

		if (_statement_expression())
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

/*statement_expression =
	invocation_expression
	 | object_creation_expression
	 | assignment
	 | post_increment_expression
	 | post_decrement_expression
	 | pre_increment_expression
	 | pre_decrement_expression.*/


boolean 	_statement_expression(){
	boolean result;
		if (debug) printf ("%s \n ","_statement_expression");

		if (_assignment())
		{
			result=true;

		}else{

			result=false; /// les autres statements pour une autre version
		}

	return result;
}


/* zakaria   ****************** DONE ********************    */

/*selection_statement =
	if_statement
	 | switch_statement.*/

boolean _selection_statement(){
	boolean result;
	if(_if_statement()){
		result=true;
	}else{
		if(_switch_statement()){
			result=true;
		}else{
			result=false;
		}
	}
	return result;
}


/*if_statement  = 'if' '(' boolean_expression ')' embedded_statement if_statement_aux
 */
boolean _if_statement(){
	boolean result;
	if(token==IF){
		token=_lire_token();
		if(token==POPEN){
			token=_lire_token();
			if(_boolean_expression()){
				token=_lire_token();
				if(token==PCLOSE){
					token=_lire_token();
					if(_embedded_statement()){
						token=_lire_token();
						if(_if_statement_aux()){
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
			}else{
				result=false;
			}
		}else{
			result=false;
		}
	}else{
		result=false;
	}

	return result;
}

/*if_statement_aux= 'else' embedded_statement | epsilon*/
boolean _if_statement_aux(){
	boolean result;
	if(token==ELSE){
		token=_lire_token();
		if(_embedded_statement()){
		 	result=true;	
		}else{
			result=false;
		}
	}else{
		result=true;
	}
	return result;
}

/*switch_statement =
	'switch' '(' expression ')' switch_block.*/

boolean _switch_statement(){
	boolean result;

	if(token==SWITCH){
		token=_lire_token();

		if(token==POPEN){
			token=_lire_token();

			if(_expression()){
				token=_lire_token();

				if(token==PCLOSE){
					token=_lire_token();

					if(_switch_block()){
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
		}else{
			result=false;
		}
	}else{
		result=false;
	}

	return result;
}

/*switch_block =
	'{' [switch_sections] '}'.*/

boolean _switch_block(){
	boolean result;
	if(token==BOPEN){
		token=_lire_token();
		if(_switch_sections() || !_switch_sections()){
			token=_lire_token();
			if(token==BCLOSE){
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
					
	return result;
}

/****** switch_sections =
	switch_section
	 | switch_sections switch_section.*/

/*switch_sections = switch_section switch_sections_aux.*/

boolean _switch_sections(){
	boolean result;
	if(_switch_section()){
		token=_lire_token();
		if(_switch_sections_aux()){
			result=true;
		}else{
			result=false;
		}
	}else{
		result=false;
	}
	
	return result;
}

/*switch_sections_aux = switch_section switch_sections_aux | eps */
	
boolean _switch_sections_aux(){
	boolean result;
	if(token==BCLOSE){
		result=true;
		follow_token=true;
	}else{
		if(_switch_section()){
			token=_lire_token();
			if(_switch_sections_aux()){
				result=true;
			}else{
				result=false;
			}
		}else{
			result=false;
		}
	}

	return result;
}

/*switch_section =
	switch_labels statement_list.*/

boolean _switch_section(){
	boolean result;
	if(_switch_labels()){
		token=_lire_token();
		if(_statement_list()){
			result=true;
		}else{
			result=false;
		}
	}else{
		result=false;
	}

	return  result;
}

/****** switch_labels =
	   		switch_label
	 		| switch_labels switch_label.*/

/*switch_labels =
	   		switch_label switch_labels_aux
	 		*/

boolean _switch_labels(){
	boolean result;
	if(_switch_label()){
		token=_lire_token();
		if(_switch_labels_aux()){
			result=true;
		}else{
			result=false;
		}
	}else{
		result=false;
	}
	
	return result;
}

/*switch_labels_aux = switch_label switch_labels_aux | eps */

boolean _switch_labels_aux(){
	boolean result;
	if(_statement_list()){
		result=true;
		follow_token=true;
	}else{
		if(_switch_label()){

			token=_lire_token();

			if(_switch_labels_aux())
			{
				result=true;
			}else{
				result=false;
			}
		}else{
			result=false;
		}
	}

	return result;
}

/*switch_label =
	'case' constant_expression ':'
	 | 'default' ':'.*/
	 
boolean _switch_label(){
	boolean result;
	if(token==CASE){
		token=_lire_token();
		if(_constant_expression()){
			token=_lire_token();
			if(token==DOUBLEDOT){
				result=true;
			}else{
				result=false;
			}
		}else{
			result=false;
		}
	}else{
		if(token==DEFAULT){
			token=_lire_token();
			if(token==DOUBLEDOT){
				result=true;
			}else{
				result=false;
			}
		}else{
			result=false;
		}		
	}
				
	return result;
}
/*  **************** Fin Zakaria ********************  */
	 

/*   idriss ait hafid ________________________________________________________________*/

/*iteration_statement =
	while_statement
	 | do_statement
	 | for_statement
	 | foreach_statement.*/

boolean _iteration_statement(){
	boolean result;
	if (_while_statement())
	{
		result=true;
	}else{
		if (_do_statement())
		{
			result=true;
		}else{
			if(_for_statement()){
				result=true;
			}
			else{
				result=false;
			}
		}
	}
	return result;
}

/*while_statement =
	'while' '(' boolean_expression ')' embedded_statement.*/

boolean _while_statement(){
	boolean result;

	if(token==WHILE){
		token=_lire_token();
		if(token==POPEN){
			token=_lire_token();
			if(_boolean_expression()){
				token=_lire_token();
				if(token==PCLOSE){
					token=_lire_token();
					if(_embedded_statement()){
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

		}else{
			result=false;
		}
	}else{
		result=false;
	}

	return result;
}
/*do_statement =
	'do' embedded_statement 'while' '(' boolean_expression ')' ';'.*/

boolean _do_statement(){
	boolean result;
	if(token==DO){
		token=_lire_token();
		if(_embedded_statement()){
			token=_lire_token();
			if(token==WHILE){
				token=_lire_token();
				if(token=POPEN){
					token=_lire_token();
					if(_boolean_expression()){
						token=_lire_token();
						if(token=PCLOSE){
							token=_lire_token();
							if(token=PVIRG){
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
				}else{
					result=false;
				}
			}else{
				result=false;
			}
		}else{
			result=false;
		}
	}else{
		result=false;
	}

	return result;
}


/* abad mohamed zayd  ________________________________________________________________*/

/*for_statement =
	'for' '(' [for_initializer] ';' [for_condition] ';' [for_iterator] ')' embedded_statement.

	for ( 				; 				; 					) embedded done

	for (     			;  	 			;   for_iterator 	) embedded done
	for (     			; for_condition ;   				) embedded done
	for (     			; for_condition ; for_iterator 		) embedded done


	for ( for_initial 	;   			;   				) embedded done
	for ( for_initiize 	; 				; for_iterator 		) embedded done
	for ( for_initiale 	; for_condition ; 					) embedded done
	for ( for_initialize; for_cond 		; fot_itira 		) embedded done



	*/

boolean _for_statement(){
	
<<<<<<< HEAD
	boolean result = false; 
	

=======
	boolean result; 
>>>>>>> master
	
	if (token == FOR){ // Si on trouve FOR 

		token = _lire_token();

<<<<<<< HEAD
			token=_lire_token();
			if(token==PVIRG){
=======
		if (token == POPEN){ //  FOR ( 

			token = _lire_token();

			if (token == PVIRG){ //  FOR ( ;

				token = _lire_token();

				if (token == PVIRG){ //  FOR ( ; ; 

					token = _lire_token();

					if (token == PCLOSE){ //  FOR ( ; ; )

						token = _lire_token();

						if(_embedded_statement()){ //  FOR ( ; ; ) embedded_statement -----------------------
							result = true;
						}
						else{
							result = false;
						}
					}

					else if (_for_iterator()){ // FOR ( ; ; for_iterator 

						token = _lire_token();

						if(token == PCLOSE){ // FOR ( ; ; for_iterator ) 

							token = _lire_token();

							if(_embedded_statement()){ // FOR ( ; ; for_iterator ) embedded_statement ------------------ 
							result = true;
							}
							else{
								result = false;
							}
						}
					}

					else{
						result = false;
					}
				}

				else if (_for_condition()){  // FOR ( ; FOR_CONDITION 

					token = _lire_token();

					if (token == PVIRG){ // FOR ( ; FOR_CONDITION ;

						token = _lire_token();

						if (token == PCLOSE){ //  FOR ( ; FOR_CONDITION ; )

							token = _lire_token();

							if(_embedded_statement()){ // FOR ( ; FOR_CONDITION ; ) embeddedd_statement --------------
								result = true;
							}
							else{
								result = false;
							}
						}

						else if(_for_iterator()){//  FOR ( ; FOR_CONDITION ; FOR_ITERATOR

							token = _lire_token();

							if (token == PCLOSE){ //  FOR ( ; FOR_CONDITION ; FOR_ITERATOR ) 

								token = _lire_token();

								if(_embedded_statement()){ // FOR ( ; FOR_CONDITION ; FOR_ITERATOR ) embedded_statement ----------------
									result = true; 
								}
								else{
									result = false;
								}
							}
							else{
								result = false;
							}
						}

						else{
							result = false;
						}
					}
					else{
						result = false;
					}
				} 

				else{
					result = false;
				}
			}

			else if (_for_initializer()) {  // FOR ( FOR_initializer 
>>>>>>> master

				token = _lire_token();

				if (token == PVIRG){   //  FOR ( FOR_initializer ; 

					token = _lire_token();

					if (token == PVIRG){ //  FOR ( FOR_initializer ; ;

						token = _lire_token();

						if (token == PCLOSE){ //  FOR ( FOR_initializer ; ; ) 

							token = _lire_token();

							if(_embedded_statement()){ //  FOR ( FOR_initializer ; ; ) embedded_statement ----------------
								result = true;
							}
							else{
								result = false;
							}
						}

						else if (_for_iterator()){ // FOR ( FOR_initializer ; ; FOR_ITERATOR 

							token = _lire_token();

							if(token == PCLOSE){ //  FOR ( FOR_initializer ; ; FOR_ITERATOR  ) 

								token = _lire_token();

								if(_embedded_statement()){ //  FOR ( FOR_initializer ; ; FOR_ITERATOR ) embedded_statement -----------------------
								result = true;
								}
								else{
									result = false;
								}
							}
						}

						else{
							result = false;
						}

					}

					else if (_for_condition()){  // FOR ( FOR_initializer ; FOR_CONDITION

						token = _lire_token();

						if (token == PVIRG){  // FOR ( FOR_initializer ; FOR_CONDITION ; 

							token = _lire_token();

							if (token == PCLOSE){  // FOR ( FOR_initializer ; FOR_CONDITION ; ) 

								token = _lire_token();

								if(_embedded_statement()){  // FOR ( FOR_initializer ; FOR_CONDITION ; ) embedded_statement ----------------------
									result = true;
								}
								else{
									result = false;
								}
							}

							else if(_for_iterator()){  // FOR ( FOR_initializer ; FOR_CONDITION ; FOR_IETRATOR 

								token = _lire_token();

								if (token == PCLOSE){ // FOR ( FOR_initializer ; FOR_CONDITION ; FOR_IETRATOR )

									token = _lire_token();

									if(_embedded_statement()){ // FOR ( FOR_initializer ; FOR_CONDITION ; FOR_IETRATOR ) embedded_statemnt --------------------
										result = true;
									}
									else{
										result = false;
									}
								}
								else{
									result = false;
								}
							}

							else{
								result = false;
							}
						}
						else{
							result = false;
						}  
					} 

					else{
						result = false;
					}
				}
				else{
					result = false;
				}
			}

			else{
				result = false;
			}
		}

		else{
			result = false;
		}

	}

	else{
		result=false;
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

	if(_statement()){
		printf("ok\n");
	}else{
		printf("nno\n");
	}
}

