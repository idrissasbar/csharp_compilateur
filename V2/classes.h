#ifndef CLASSES_H
#define CLASSES_H

#include"analyseur_csharp.h"


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types.h"
#include"error.h"
#include "tablesymb.h"

extern boolean debug;

extern int yylex();
extern int yylindeno;
extern char *yytext;



extern typetoken token;

//varvalueType var;

extern int localrangvar;

extern boolean follow_token;

extern varvalueType varattribute;
extern constvalueType constattribute;
extern typevalueType typeattribute;
extern instvalueType instattribute;
extern listinstvalueType listinstattribute;
extern tokenvalueType tokenattribute;

extern int rangvar;
extern boolean semanticerror ;


// variable_declarators =
// 	variable_declarator
// 	 | variable_declarators, ',', variable_declarator;

/* variable_declarators = variable_declarator variable_declarators_aux */

boolean _variable_declarators();
/*variable_declarators_aux = ',' variable_declarator variable_declarators_aux */

boolean _variable_declarators_aux();
// variable_declarator =
// 	identifier
// 	 | identifier, '=', variable_initializer;

/* variable_declarator = identifier variable_declarator_aux */

boolean _variable_declarator();

/* variable_declarator_aux = '=', variable_initializer | eps */

boolean _variable_declarator_aux();

// variable_initializer =
// 	expression
// 	 | array_initializer;

boolean _variable_initializer();
// field_declaration =
// 	[attributes], [field_modifiers], type, variable_declarators, ';';

boolean _field_declaration();
		// field_modifiers =
		// 	field_modifier
		// 	 | field_modifiers, field_modifier;
// field_modifiers = field_modifier field_modifiers_aux
boolean _field_modifiers();

//field_modifiers_aux = field_modifier field_modifiers_aux |eps

boolean _field_modifiers_aux();
// field_modifier =
// 	'new'
// 	 | 'public'
// 	 | 'protected'
// 	 | 'internal'
// 	 | 'private'
// 	 | 'static'
// 	 | 'readonly'
// 	 | 'volatile'
// 	 | field_modifier_unsafe;


boolean _field_modifier();
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




/***************************Définition des classes******************/
/*destructor_body =
	block
	 | ';'.*/
boolean _destructor_body();

/*
destructor_declaration =
	[attributes] ['extern'] '~' identifier '(' ')' destructor_body
	 | destructor_declaration_unsafe.

--> destructor_declaration = 
		attributes 'extern' '~' identifier '(' ')' destructor_body 
		|'extern' '~' identifier '(' ')' destructor_body 
		|'~' identifier '(' ')' destructor_body 
		|destructor_declaration_unsafe.
*/

boolean _attributes();

boolean _destructor_declaration();

/*static_constructor_body =
	block
	 | ';'.*/
boolean _static_constructor_body();

/*static_constructor_modifiers =
	['extern'] 'static'
	 | 'static' ['extern']
	 | static_constructor_modifiers_unsafe.

--> static_constructor_modifiers =
		'extern' 'static'
		|'static' 'extern'
		| 'static'
		| static_constructor_modifiers_unsafe.

*/
boolean _static_constructor_modifiers();

/*
static_constructor_declaration =
	[attributes] static_constructor_modifiers identifier '(' ')' static_constructor_body.

--> static_constructor_declaration =
	attributes static_constructor_modifiers identifier '(' ')' static_constructor_body
	|static_constructor_modifiers identifier '(' ')' static_constructor_body.
*/
boolean _static_constructor_declaration();
/*constructor_body =
	block
	 | ';'.*/
boolean _constructor_body();

/*constructor_initializer =
	':' 'base' '(' [argument_list] ')'
	 | ':' 'this' '(' [argument_list] ')'.

constructor_initializer =':' constructor_initializer_aux '(' constructor_initializer_aux_aux ')'
constructor_initializer_aux = 'base' | 'this' 
constructor_initializer_aux_aux = argument_list  | eps .
*/
boolean _constructor_initializer_aux_aux();
boolean _constructor_initializer_aux();
boolean _constructor_initializer();

/*constructor_declarator = identifier '('  constructor_declarator_aux constructor_declarator_aux_aux.
	constructor_declarator_aux = formal_parameter_list ')' 
								| ')'.
	constructor_declarator_aux_aux= constructor_initializer | eps.         bopen|pvirg
*/
boolean _constructor_declarator_aux_aux();
boolean _constructor_declarator_aux();
boolean _constructor_declarator();


/*constructor_modifier =
	'public'
	 | 'protected'
	 | 'internal'
	 | 'private'
	 | 'extern'
	 | constructor_modifier_unsafe.*/
boolean _constructor_modifier();

/*constructor_modifiers =
	constructor_modifier
	 | constructor_modifiers constructor_modifier.

devient :
	constructor_modifiers =  constructor_modifier constructor_modifiers_aux.
	constructor_modifiers_aux =  constructor_modifier constructor_modifiers_aux
									| eps.    IDF 
*/
boolean _constructor_modifiers_aux();
boolean _constructor_modifiers();

/*constructor_declaration =	[attributes] [constructor_modifiers] constructor_declarator constructor_body.

constructor_declaration = attributes constructor_declaration_aux.
constructor_declaration_aux = constructor_modifiers constructor_declarator constructor_body 
								| constructor_declarator constructor_body.
*/
boolean _constructor_declaration_aux();
boolean _constructor_declaration();
/*
operator_body =
	block
	 | ';'.*/
boolean _operator_body();

/*conversion_operator_declarator =
	'implicit' 'operator' type '(' type identifier ')'
	 | 'explicit' 'operator' type '(' type identifier ')'.*/
boolean _conversion_operator_declarator();
/*overloadable_binary_operator =
	'+'
	 | '-'
	 | '*'
	 | '/'
	 | '%'
	 | '&'
	 | '|'
	 | '^'
	 | '<<'
	 | '>>'
	 | '=='
	 | '!='
	 | '>'
	 | '<'
	 | '>='
	 | '<='.*/
boolean _overloadable_binary_operator();
/*binary_operator_declarator = 	type 'operator' overloadable_binary_operator '(' type identifier ',' type identifier ')'.*/
boolean _binary_operator_declarator();

/*overloadable_unary_operator =
	'+' | '-' | '!' | '~' | '++' | '--' | 'true' | 'false'.*/
boolean _overloadable_unary_operator();

/*unary_operator_declarator =
	type 'operator' overloadable_unary_operator '(' type identifier ')'.
*/
boolean _unary_operator_declarator();

/*operator_declarator =
	unary_operator_declarator
	 | binary_operator_declarator
	 | conversion_operator_declarator.
*/
boolean _operator_declarator();

/*operator_declarator =
	unary_operator_declarator
	 | binary_operator_declarator
	 | conversion_operator_declarator.*/
boolean _operator_declarator();

/*operator_modifier =
	'public'
	 | 'static'
	 | 'extern'
	 | operator_modifier_unsafe.*/
boolean _operator_modifier();

/*operator_modifiers =
	operator_modifier
	 | operator_modifiers operator_modifier.
devient : 
operator_modifiers = operator_modifier operator_modifiers_aux
operator_modifiers_aux = operator_modifier operator_modifiers_aux | eps
*/
boolean _operator_modifiers_aux();
boolean _operator_modifiers();

/*operator_declaration =
	attributes operator_modifiers operator_declarator operator_body
	| operator_modifiers operator_declarator operator_body.
*/
boolean _operator_declaration();
/*indexer_declarator =
	type 'this' '[' formal_parameter_list ']'
	 | type interface_type '.' 'this' '[' formal_parameter_list ']'.*/
boolean _indexer_declarator();

/*indexer_modifier =
	'new'
	 | 'public'
	 | 'protected'
	 | 'internal'
	 | 'private'
	 | 'virtual'
	 | 'sealed'
	 | 'override'
	 | 'abstract'
	 | 'extern'
	 | indexer_modifier_unsafe.*/
boolean _indexer_modifier();

/*indexer_modifiers =
	indexer_modifier
	 | indexer_modifiers indexer_modifier.

indexer_modifiers =  indexer_modifier indexer_modifiers_aux
indexer_modifiers_aux = indexer_modifier indexer_modifiers_aux |eps 
*/
boolean _indexer_modifiers_aux();
boolean _indexer_modifiers();

/*indexer_declaration =
	[attributes] [indexer_modifiers] indexer_declarator '{' accessor_declarations '}'.*/
boolean _indexer_declaration();
//class_declaration = [attributes] [class_modifiers] ['partial'] 'class' identifier [type_parameter_list] [class_base] [type_parameter_constraints_clauses] class_body [';'].
boolean _class_declaration();

/*class_modifiers =
	class_modifier
	 | class_modifiers class_modifier.*/
boolean _class_modifiers_aux();

boolean _class_modifiers();

/*class_modifier =
	'new'
	 | 'public'
	 | 'protected'
	 | 'internal'
	 | 'private'
	 | 'abstract'
	 | 'sealed'
	 | 'static'
	 | class_modifier_unsafe.*/
boolean _class_modifier();

/*class_base =
	':' class_type
	 | ':' interface_type_list
	 | ':' class_type ',' interface_type_list.
*/
boolean _class_base();

/*class_type =
	type_name
	 | 'object'
	 | 'dynamic'
	 | 'string'.*/
boolean _class_type();

boolean _type_name();

/*
class_member_declarations =
	class_member_declaration
	 | class_member_declarations class_member_declaration.

*/

boolean _class_member_declarations_aux();
boolean _class_member_declaration();

/*class_member_declaration =
	constant_declaration-----------me
	 | field_declaration--------me
	 | method_declaration--------
	 | property_declaration--------
	 | event_declaration
	 | indexer_declaration
	 | operator_declaration
	 | constructor_declaration---------
	 | destructor_declaration----------
	 | static_constructor_declaration
	 | type_declaration.*/

boolean _class_member_declaration();

/*constant_declaration =
	[attributes] [constant_modifiers] 'const' type constant_declarators ';'.*/
boolean _constant_declaration();

/*constant_modifiers =
	constant_modifier
	 | constant_modifiers constant_modifier.*/
boolean _constant_modifiers();

/*
constant_modifier =
	'new'
	 | 'public'
	 | 'protected'
	 | 'internal'
	 | 'private'.
constant_declarators =
	constant_declarator
	 | constant_declarators ',' constant_declarator.
constant_declarator =
	identifier '=' constant_expression.
*/

/*remove_accessor_declaration = attributes 'remove' block.
								|'remove' block
*/
boolean _remove_accessor_declaration();

/*add_accessor_declaration = attributes 'add' block.
							|'add' block*/

boolean _add_accessor_declaration();

/*event_accessor_declarations =
	add_accessor_declaration remove_accessor_declaration
	 | remove_accessor_declaration add_accessor_declaration.*/
boolean _event_accessor_declarations();

/*event_modifier =
	'new'
	 | 'public'
	 | 'protected'
	 | 'internal'
	 | 'private'
	 | 'static'
	 | 'virtual'
	 | 'sealed'
	 | 'override'
	 | 'abstract'
	 | 'extern'
	 | event_modifier_unsafe.*/

boolean _event_modifier();

/*event_modifiers =
	event_modifier
	 | event_modifiers event_modifier.*/
boolean _event_modifiers();
/*event_declaration =
	attributes event_modifiers 'event' type variable_declarators ';'
	| event_modifiers 'event' type variable_declarators ';'
	|	'event' type variable_declarators ';'
	| attributes event_modifiers 'event' type member_name '{' event_accessor_declarations '}'.
	| event_modifiers 'event' type member_name '{' event_accessor_declarations '}'
	| 'event' type member_name '{' event_accessor_declarations '}'


boolean _event_declaration(){
	boolean result;
	if(_attributes()){
		token=_lire_token();
		if(_event_modifiers()){
			token=_lire_token();
			if(token=EVENT){

			}else{
				result=false;
			}
		}else{
			result=false;
		}
	}
	return result;
}*/

/*type_parameter_list = '<' type_parameters '>'.*/

boolean _type_parameter_list();
/*type_parameters =
	attributes type_parameter
	| type_parameter
	 | type_parameters ',' type_parameters_aux

*/

boolean _type_parameters();

/*type_parameters_aux = attributes type_parameter
						| type_parameter*/
boolean _type_parameters_aux();

/*type_parameter =
	identifier.*/

boolean _type_parameter();

/*constructor_constraint =
	'new' '(' ')'.*/

boolean _constructor_constraint();

/*class_body =
	'{' class_member_declarations '}'.
	|'{' '}' */
boolean _class_body();
/*method_declaration =
	method_header method_body.*/
boolean _method_declaration();

/*method_header =
	[attributes] [method_modifiers] ['partial'] return_type member_name [type_parameter_list] '(' [formal_parameter_list] ')' [type_parameter_constraints_clauses].
	| [method_modifiers] ['partial'] return_type member_name [type_parameter_list] '(' [formal_parameter_list] ')' [type_parameter_constraints_clauses].
	|['partial'] return_type member_name [type_parameter_list] '(' [formal_parameter_list] ')' [type_parameter_constraints_clauses].
	| return_type member_name [type_parameter_list] '(' [formal_parameter_list] ')' [type_parameter_constraints_clauses].
	*/

/*method_header =
	[attributes], [method_modifiers], ['partial'], return_type, member_name, [type_parameter_list], '(', [formal_parameter_list], ')', [type_parameter_constraints_clauses];
	*/

	boolean _method_header();
	// method_modifiers =
	// method_modifier
	//  | method_modifiers, method_modifier;
/*
method_modifiers = method_modifier method_modifiers_aux */

boolean _method_modifiers();

/*method_modifiers_aux = method_modifier method_modifiers_aux | eps */
boolean _method_modifiers_aux();
/*method_modifier =
	'new'
	 | 'public'
	 | 'protected'
	 | 'internal'
	 | 'private'
	 | 'static'
	 | 'virtual'
	 | 'sealed'
	 | 'override'
	 | 'abstract'
	 | 'extern'
	 | method_modifier_unsafe;*/


boolean _method_modifier();

/*return_type =
	type
	 | 'void';*/


boolean _return_type();

/*member_name =
	identifier
	 | interface_type, '.', identifier;*/
boolean _member_name();


/*method_body =
	block
	 | ';';	*/

boolean _method_body();



#endif
