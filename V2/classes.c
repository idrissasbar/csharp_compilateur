
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types.h"
#include"error.h"
#include "tablesymb.h"
#include "classes.h"

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

boolean _variable_declarators(){
	boolean result;

	if (_variable_declarator())
	{	
		token=_lire_token();

		if (_variable_declarators_aux())
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

/*variable_declarators_aux = ',' variable_declarator variable_declarators_aux */

boolean _variable_declarators_aux(){
	boolean result;

	if (token==VIRG)
	{	
		token=_lire_token();

		if (_variable_declarators())
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


// variable_declarator =
// 	identifier
// 	 | identifier, '=', variable_initializer;

/* variable_declarator = identifier variable_declarator_aux */

boolean _variable_declarator(){
	boolean result;

	if (token==IDF)
	{
		token=_lire_token();
		if (_variable_declarator_aux())
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

/* variable_declarator_aux = '=', variable_initializer | eps */

boolean _variable_declarator_aux(){
	boolean result;

		if(token){

		}else{

			if (token == EQ)
			{
				 token=_lire_token();

				 if (_variable_initializer())
				 {
				 	result=true;
				 }else{
				 	result=false;
				 }
			}
		}

	return result;
}


// variable_initializer =
// 	expression
// 	 | array_initializer;

boolean _variable_initializer() {
	boolean result;

	AST *past = (AST *) malloc(sizeof(AST)); // NEW
	(*past) = (AST) malloc(sizeof(struct Exp));


		if(_expression(past)){

			result=true;
		}else{
			result=false;
		}

	return result;
}

// field_declaration =
// 	[attributes], [field_modifiers], type, variable_declarators, ';';

boolean _field_declaration(){
	boolean result;

	if (_type())
	{
		token=_lire_token();
		if (_field_modifiers_aux())
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

		// field_modifiers =
		// 	field_modifier
		// 	 | field_modifiers, field_modifier;
// field_modifiers = field_modifier field_modifiers_aux
boolean _field_modifiers(){
	boolean result;

	if (_field_modifier())
	{
		token=_lire_token();
		if (_field_modifiers_aux())
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

//field_modifiers_aux = field_modifier field_modifiers_aux |eps

boolean _field_modifiers_aux(){
	boolean result;

	if (_type())
	{
		result=true;
		follow_token=true;
		
	}else{

	
		if (_field_modifiers())
		{
			result=true;
		}else{
			result=false;
		}
	}

	return result;
}


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


boolean _field_modifier(){
	boolean result;

	switch(token){
		case NEW : 
			result=true;

			break;
		case PUBLIC : 
			result=true;
			
			break;
		case PROTECTED : 

			result=true;
			break;
		case PRIVATE : 
			result=true;
			break;

		default : result=false;
	}

	return result;
}

/*********************argument_list =
									argument
									 | argument_list, ',', argument;*/
/* argument_list = argument argument_list_aux*/

boolean _argument_list(){
	boolean result;

		if (_argument())
		{
			token=_lire_token();

			if (_argument_list_aux())
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

/*argument_list_aux = ',' argument argument_list_aux | eps */

boolean _argument_list_aux(){
	boolean result;

		if (token==PCLOSE)
		{
			result=true;
			follow_token=true;

		}else{
			

			if (token==VIRG)
			{   
				token=_lire_token();
				if (_argument_list())
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


/*argument =
	[argument_name], argument_value;*/
/*
argument = argument_name argument_value | argument_value */

boolean _argument(){
	boolean result;

		if (_argument_name())
		{
			token=_lire_token();
			if (_argument_value())
			{
				result=true;
			}else{

				result=false;
			}
		}else{
			if (_argument_value())
			{
				result=true;
			}else{

				result=false;
			}
		}

	return result;
}

/*argument_name =
	identifier, ':';*/
boolean _argument_name(){
	boolean result;

	if (token==IDF)		
	{
		token=_lire_token();

		if (token==DOUBLEDOT)
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

/*argument_value =
	expression
	 | 'ref', variable_reference
	 | 'out', variable_reference;*/

boolean _argument_value(){
	boolean result;

		if (token==REF)
		{
			if (_variable_reference())
				{
					result=true;
				}else{

					result=false;
				}
		}else{

			if (token==OUT)
			{
				if (_variable_reference())
				{
					result=true;
				}else{

					result=false;
				}
			}else{
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

boolean _variable_reference(){
	boolean result;

				if (_expression())
				{
					result=true;
				}else{

					result=false;
				}
	return result;
}



/***************************Définition des classes******************/
/*destructor_body =
	block
	 | ';'.*/
boolean _destructor_body(){
	boolean result;
	if(_block()){
		result=true;
	}else{
		if(token==PVIRG){
			result=true;
		}else{
			result=false;
		}
	}
	return result;
}



// formal_parameter_list =
// 	fixed_parameters
// 	 | fixed_parameters, ',', parameter_array
// 	 | parameter_array;

boolean _formal_parameter_list(){
	boolean result=true;


	return result;
}


// fixed_parameters =
// 	fixed_parameter
// 	 | fixed_parameters, ',', fixed_parameter;


// fixed_parameter =
// 	[attributes], [parameter_modifier], type, identifier, [default_argument];


// default_argument =
// 	'=', expression;


// parameter_modifier =
// 	'ref'
// 	 | 'out'
// 	 | 'this';


// parameter_array =
// 	[attributes], 'params', array_type, identifier;

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

boolean _attributes(){return false;}

boolean _destructor_declaration(){
	boolean result;
	if(_attributes()){ //attributes 'extern' '~' identifier '(' ')' destructor_body
		token = _lire_token(); 
		if(token==EXTERN){
			token = _lire_token();
			if(token==TILDE){
				token = _lire_token();
				if(token==IDF){
					token = _lire_token();
					if(token==POPEN){
						token = _lire_token();
						if(token==PCLOSE){
							token = _lire_token();
							if(_destructor_body()){
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
	}else{ //'extern' '~' identifier '(' ')' destructor_body 
		if(token==EXTERN){
			token=_lire_token();
			if(token==TILDE){
				token=_lire_token();
				if(token==IDF){
					token = _lire_token();
					if(token==POPEN){
						token = _lire_token();
						if(token==PCLOSE){
							token = _lire_token();
							if(_destructor_body()){
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
		}else{//'~' identifier '(' ')' destructor_body 
			if(token==TILDE){
				token=_lire_token();
				if(token==IDF){
					token = _lire_token();
					if(token==POPEN){
						token = _lire_token();
						if(token==PCLOSE){
							token = _lire_token();
							if(_destructor_body()){
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
			}else{//destructor_declaration_unsafe.
				//if(_destructor_declaration_unsafe()){
				//	result=true;
				//}else{
					result=false;
				//}
			}
		}
	}
	return result;
}

/*static_constructor_body =
	block
	 | ';'.*/
boolean _static_constructor_body(){
	boolean result;
	if(_block()){
		result=true;
	}else{
		if(token==PVIRG){
			result=true;
		}else{
			result=false;
		}
	}
	return result;
}

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
boolean _static_constructor_modifiers(){
	boolean result;
	if(token==EXTERN){
		token=_lire_token();
		if(token==STATIC){
			result=true;
		}else{
			result=false;
		}
	}else{
		if(token==STATIC){
			token=_lire_token();
			if(token==EXTERN){
				result=true;
			}else{
				result=false;
			}
		}else{
			if(token==STATIC){
				result=true;
			}else{
				//if(_static_constructor_modifiers_unsafe()){
				// 	result=true;
				// }else{
					result=false;
				// }
			}
		}
	}
	return result; 
}


/*
static_constructor_declaration =
	[attributes] static_constructor_modifiers identifier '(' ')' static_constructor_body.

--> static_constructor_declaration =
	attributes static_constructor_modifiers identifier '(' ')' static_constructor_body
	|static_constructor_modifiers identifier '(' ')' static_constructor_body.
*/
boolean _static_constructor_declaration(){
	boolean result;
	if(_attributes()){//attributes static_constructor_modifiers identifier '(' ')' static_constructor_body
		token=_lire_token();
		if(_static_constructor_modifiers()){
			token=_lire_token();
			if(token==IDF){
				token=_lire_token();
				if(token==POPEN){
					token=_lire_token();
					if(token==PCLOSE){
						token=_lire_token();
						if(_static_constructor_body()){
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
	}else{//static_constructor_modifiers identifier '(' ')' static_constructor_body
		if(_static_constructor_modifiers()){
			token=_lire_token();
			if(token==IDF){
				token=_lire_token();
				if(token==POPEN){
					token=_lire_token();
					if(token==PCLOSE){
						token=_lire_token();
						if(_static_constructor_body()){
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
	}
	return result;
}

/*constructor_body =
	block
	 | ';'.*/
boolean _constructor_body(){
	boolean result;
	if(_block()){
		result=true;
	}else{
		if(token==PVIRG){
			result=true;
		}else{
			result=false;
		}
	}
	return result;
}

/*constructor_initializer =
	':' 'base' '(' [argument_list] ')'
	 | ':' 'this' '(' [argument_list] ')'.

constructor_initializer =':' constructor_initializer_aux '(' constructor_initializer_aux_aux ')'
constructor_initializer_aux = 'base' | 'this' 
constructor_initializer_aux_aux = argument_list  | eps .
*/
boolean _constructor_initializer_aux_aux(){
	boolean result;
	if(_argument_list()){result=true;}
	else{
		if(token==PCLOSE){result=true;}
		else{result=false;}
	}
	return result;
}
boolean _constructor_initializer_aux(){
	boolean result;
	if(token==BASE){result=true;}
	else{
		if(token==THIS){result=true;}
		else{result=false;}
	}
	return result;
}
boolean _constructor_initializer(){
	boolean result;
	if(token==DOUBLEDOT){
		token=_lire_token();
		if(_constructor_initializer_aux()){
			token=_lire_token();
			if(token==POPEN){
				token=_lire_token();
				if(_constructor_initializer_aux_aux()){
					token=_lire_token();
					if(token==PCLOSE){result=true;}
					else{result=false;}
				}else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}else{result=false;}
	return result;
}

/*constructor_declarator = identifier '('  constructor_declarator_aux constructor_declarator_aux_aux.
	constructor_declarator_aux = formal_parameter_list ')' 
								| ')'.
	constructor_declarator_aux_aux= constructor_initializer | eps.         bopen|pvirg
*/
boolean _constructor_declarator_aux_aux(){
	boolean result;
	if(token==BOPEN || token==PVIRG){
		result=true;
		follow_token=true;
	}else{
		if(_constructor_initializer()){
			result=true;
		}else{result=false;}
	}
	return result;
}
boolean _constructor_declarator_aux(){
	boolean result;
	if(token==PCLOSE){result=true;}
	else{
		if(_formal_parameter_list()){
			token=_lire_token();
			if(token==PCLOSE){result=true;}
			else{result=false;}
		}else{result=false;}
	}
	return result;
}
boolean _constructor_declarator(){
	boolean result;
	if(token==IDF){
		token=_lire_token();
		if(token==POPEN){
			token=_lire_token();
			if(_constructor_declarator_aux()){
				token=_lire_token();
				if(_constructor_declarator_aux_aux()){result=true;}
				else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}else{result=false;}
	return result;
}


/*constructor_modifier =
	'public'
	 | 'protected'
	 | 'internal'
	 | 'private'
	 | 'extern'
	 | constructor_modifier_unsafe.*/
boolean _constructor_modifier(){
	boolean result;
	if(token==PUBLIC){
		result=true;
	}else{
		if(token==PROTECTED){
			result=true;
		}else{
			if(token==INTERNAL){
				result=true;
			}else{
				if(token==PRIVATE){
					result=true;
				}else{
					if(token==EXTERN){
						result=true;
					}else{
						// if(_constructor_modifier_unsafe()){
							result=true;
						// }else{
						// 	result=false;
						// }
					}
				}
			}
		}
	}
	return result;
}

/*constructor_modifiers =
	constructor_modifier
	 | constructor_modifiers constructor_modifier.

devient :
	constructor_modifiers =  constructor_modifier constructor_modifiers_aux.
	constructor_modifiers_aux =  constructor_modifier constructor_modifiers_aux
									| eps.    IDF 
*/
boolean _constructor_modifiers_aux(){
	boolean result;
	if(_constructor_modifier()){
		token=_lire_token();
		if(_constructor_modifiers_aux()){
			result=true;
		}else{result=false;}
	}else{
		if(token==IDF){result=true;follow_token=true;}
		else{result=false;}
	}
	return result;
}
boolean _constructor_modifiers(){
	boolean result;
	if(_constructor_modifier()){
		token=_lire_token();
		if(_constructor_modifiers_aux()){result=true;}
		else{result=false;}
	}else{result=false;}
	return result;
}

/*constructor_declaration =	[attributes] [constructor_modifiers] constructor_declarator constructor_body.

constructor_declaration = attributes constructor_declaration_aux.
constructor_declaration_aux = constructor_modifiers constructor_declarator constructor_body 
								| constructor_declarator constructor_body.
*/
boolean _constructor_declaration_aux(){
	boolean result;
	if(_constructor_declarator()){
		token=_lire_token();
		if(_constructor_body()){result=true;}
		else{result=false;}
	}else{
		if(_constructor_modifiers()){
			token=_lire_token();
			if(_constructor_declarator()){
				token=_lire_token();
				if(_constructor_body()){result=true;}
				else{result=false;}
			}else{result=false;}
		}
	}
	return result;
}
boolean _constructor_declaration(){
	boolean result;
	if(_attributes()){
		token=_lire_token();
		if(_constructor_declaration_aux()){result=true;}
		else{result=false;}
	}else{result=false;}
	return result; 
}

/*
operator_body =
	block
	 | ';'.*/
boolean _operator_body(){
	boolean result;
	if(_block()){
		result=true;
	}else{
		if(token==PVIRG){
			result=true;
		}else{
			result=false;
		}
	}
	return result;
}

/*conversion_operator_declarator =
	'implicit' 'operator' type '(' type identifier ')'
	 | 'explicit' 'operator' type '(' type identifier ')'.*/
boolean _conversion_operator_declarator(){
	boolean result;
	if(token==IMPLICIT){
		token=_lire_token();
		if(token==OPERATOR){
			token=_lire_token();
			if(_type()){
				token=_lire_token();
				if(token==POPEN){
					token=_lire_token();
					if(_type()){
						token=_lire_token();
						if(token==IDF){
							token=_lire_token();
							if(token==PCLOSE){result=true;}
							else{result=false;}
						}else{result=false;}
					}else{result=false;}
				}else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}else{
		if(token==EXPLICIT){
			token=_lire_token();
			if(token==OPERATOR){
				token=_lire_token();
				if(_type()){
					token=_lire_token();
					if(token==POPEN){
						token=_lire_token();
						if(_type()){
							token=_lire_token();
							if(token==IDF){
								token=_lire_token();
								if(token==PCLOSE){result=true;}
								else{result=false;}
							}else{result=false;}
						}else{result=false;}
					}else{result=false;}
				}else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}
	return result;
}

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
boolean _overloadable_binary_operator(){
	boolean result;
	switch(token) {
		case PLUS : result=true; break;
		case MINUS : result=true; break;
		case MULT : result=true; break;
		case DIV : result=true; break;
		case MOD : result=true; break;
		case AND : result=true; break;
		case OR : result=true; break;
		case XOR : result=true; break;
		case LTLT : result=true; break;
		case GTGT : result=true; break;
		case EQEQ : result=true; break;
		case NOTEQ : result=true; break;
		case GT : result=true; break;
		case LT : result=true; break;
		case GEQ : result=true; break;
		case LEQ : result=true; break;
		default: result=false;
	}
	return result;
}

/*binary_operator_declarator = 	type 'operator' overloadable_binary_operator '(' type identifier ',' type identifier ')'.*/
boolean _binary_operator_declarator(){
	boolean result;
	if(_type()){
		token=_lire_token();
		if(token==OPERATOR){
			token=_lire_token();
			if(_overloadable_binary_operator()){
				token=_lire_token();
				if(token==POPEN){
					token=_lire_token();
					if(_type()){
						token=_lire_token();
						if(token==IDF){
							token=_lire_token();
							if(token==PVIRG){
								token=_lire_token();
								if(_type()){
									token=_lire_token();
									if(token==IDF){
										token=_lire_token();
										if(token==PCLOSE){result=true;}
										else{result=false;}
									}else{result=false;}
								}else{result=false;}
							}else{result=false;}
						}else{result=false;}
					}else{result=false;}
				}else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}else{result=false;}
	return result;
}

/*overloadable_unary_operator =
	'+' | '-' | '!' | '~' | '++' | '--' | 'true' | 'false'.*/
boolean _overloadable_unary_operator(){
	boolean result;
	switch(token){
		case PLUS : result=true; break;
		case MINUS : result=true; break;
		case EXCL : result=true; break;
		case TILDE : result=true; break;
		case PLUSPLUS : result=true; break;
		case MINUSMINUS : result=true; break;
		case TRUE : result=true; break;
		case FALSE : result=true; break;
		default: result=false;
	}
	return result; 
}

/*unary_operator_declarator =
	type 'operator' overloadable_unary_operator '(' type identifier ')'.
*/
boolean _unary_operator_declarator(){
	boolean result;
	if(_type()){
		token=_lire_token();
		if(token==OPERATOR){
			token=_lire_token();
			if(_overloadable_unary_operator()){
				token=_lire_token();
				if(token==POPEN){
					token=_lire_token();
					if(_type()){
						token=_lire_token();
						if(token==IDF){
							token=_lire_token();
							if(token==PCLOSE){result=true;}
							else{result=false;}
						}else{result=false;}
					}else{result=false;}
				}else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}else{result=false;}
	return result; 
}


/*operator_declarator =
	unary_operator_declarator
	 | binary_operator_declarator
	 | conversion_operator_declarator.*/
boolean _operator_declarator(){
	boolean result;
	if(_unary_operator_declarator()){result=true;}
	else{
		if(_binary_operator_declarator()){result=true;}
		else{
			if( _conversion_operator_declarator()){result=true;}
			else{result=false;}
		}
	}
	return result;
}

/*operator_modifier =
	'public'
	 | 'static'
	 | 'extern'
	 | operator_modifier_unsafe.*/
boolean _operator_modifier(){
	boolean result;
	if(token==PUBLIC){result=true;}
	else{
		if(token==STATIC){result=true;}
		else{
			if(token==EXTERN){result=true;}
			else{
				// if(_operator_modifier_unsafe()){result=true;}
				// else{
					result=false;
				// }
			}
		}
	}
	return result;
}

/*operator_modifiers =
	operator_modifier
	 | operator_modifiers operator_modifier.
devient : 
operator_modifiers = operator_modifier operator_modifiers_aux
operator_modifiers_aux = operator_modifier operator_modifiers_aux | eps
*/
boolean _operator_modifiers_aux(){
	boolean result;
	if(_operator_modifier()){
		token=_lire_token();
		if(_operator_modifiers_aux()){result=true;}
		else{result=false;}
	}else{
		if(_unary_operator_declarator()){result=true;}
		else{
			if(_binary_operator_declarator()){result=true;}
			else{
				if(_conversion_operator_declarator()){result=true;}
				else{result=false;}
			}
		}
	}
	return result;
}
boolean _operator_modifiers(){
	boolean result;
	if(_operator_modifier()){
		token=_lire_token();
		if(_operator_modifiers_aux()){result=true;}
		else{result=false;}
	}else{result=false;}
	return result;
}

/*operator_declaration =
	attributes operator_modifiers operator_declarator operator_body
	| operator_modifiers operator_declarator operator_body.
*/
boolean _operator_declaration(){
	boolean result;
	if(_operator_modifiers()){
		token=_lire_token();
		if(_operator_declarator()){
			token=_lire_token();
			if(_operator_body()){result=true;}
			else{result=false;}
		}else{result=false;}
	}else{
		if(_attributes()){
			token=_lire_token();
			if(_operator_modifiers()){
				token=_lire_token();
				if(_operator_declarator()){
					token=_lire_token();
					if(_operator_body()){result=true;}
					else{result=false;}
				}else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}
	return result;
}

/*indexer_declarator =
	type 'this' '[' formal_parameter_list ']'
	 | type interface_type '.' 'this' '[' formal_parameter_list ']'.*/
boolean _indexer_declarator(){
	boolean result;
	if(_type()){
		token=_lire_token();
		if(token==THIS){
			token=_lire_token();
			if(token==LEFTBRACKET){
				token=_lire_token();
				if(_formal_parameter_list()){
					token=_lire_token();
					if(token==RIGHTBRACKET){result=true;}
					else{result=false;}
				}else{result=false;}
			}else{result=false;}
		}else{
			// if(_interface_type()){
			// 	token=_lire_token();
			// 	if(token==POINT){
			// 		token=_lire_token();
			// 		if(token==THIS){
			// 			if(token==LEFTBRACKET){
			// 				token=_lire_token();
			// 				if(_formal_parameter_list()){
			// 					token=_lire_token();
			// 					if(token==RIGHTBRACKET){result=true;}
			// 					else{result=false;}
			// 				}else{result=false;}
			// 			}else{result=false;}
			// 		}else{result=false;}
			// 	}else{result=false;}
			// }else{result=false;}
		}
	}else{result=false;}
	return result; 
}

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
boolean _indexer_modifier(){
	boolean result;
	if(token==NEW){result=true;}
	else{
		if(token==PUBLIC){result=true;}
		else{
			if(token==PROTECTED){result=true;}
			else{
				if(token==INTERNAL){result=true;}
				else{
					if(token==PRIVATE){result=true;}
					else{
						if(token==VIRTUAL){result=true;}
						else{
							if(token==SEALED){result=true;}
							else{
								if(token==OVERRIDE){result=true;}
								else{
									if(token==ABSTRACT){result=true;}
									else{
										if(token==EXTERN){result=true;}
										else{
											// if(_indexer_modifier_unsafe())
											// 	{
													result=true;

												// }else{
												// 	result=false;
												// }
										}
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

/*indexer_modifiers =
	indexer_modifier
	 | indexer_modifiers indexer_modifier.

indexer_modifiers =  indexer_modifier indexer_modifiers_aux
indexer_modifiers_aux = indexer_modifier indexer_modifiers_aux |eps 
*/
boolean _indexer_modifiers_aux(){
	boolean result;
	if(_type()){
		result=true;
		follow_token=true;
	}else{
		if(_indexer_modifier()){
			token=_lire_token();
			if(_indexer_modifiers_aux()){result=true;}
			else{result=false;}
		}
	}
	return result;
}
boolean _indexer_modifiers(){
	boolean result;
	if(_indexer_modifier()){
		token=_lire_token();
		if(_indexer_modifiers_aux()){result=true;}
		else{result=false;}
	}else{result=false;}
	return result;
}

/*indexer_declaration =
	[attributes] [indexer_modifiers] indexer_declarator '{' accessor_declarations '}'.*/
boolean _indexer_declaration(){
	boolean result;
	// if(_attributes()){
	// 	token=_lire_token();
	// 	if(_indexer_modifiers()){
	// 		token=_lire_token();
	// 		if(_indexer_declarator()){
	// 			token=_lire_token();
	// 			if(token==BOPEN){
	// 				token=_lire_token();
	// 				if(_accessor_declarations()){
	// 					token=_lire_token();
	// 					if(token==BCLOSE){result=true;}
	// 					else{result=false;}
	// 				}else{result=false;}
	// 			}else{result=false;}
	// 		}else{result=false;}
	// 	}else{
	// 		if(_indexer_declarator()){
	// 			token=_lire_token();
	// 			if(token==BOPEN){
	// 				token=_lire_token();
	// 				if(_accessor_declarations()){
	// 					token=_lire_token();
	// 					if(token==BCLOSE){result=true;}
	// 					else{result=false;}
	// 				}else{result=false;}
	// 			}else{result=false;}
	// 		}else{result=false;}
	// 	}
	// }else{
	// 	if(_indexer_modifiers()){
	// 		token=_lire_token();
	// 		if(_indexer_declarator()){
	// 			token=_lire_token();
	// 			if(token==BOPEN){
	// 				token=_lire_token();
	// 				if(_accessor_declarations()){
	// 					token=_lire_token();
	// 					if(token==BCLOSE){result=true;}
	// 					else{result=false;}
	// 				}else{result=false;}
	// 			}else{result=false;}
	// 		}else{result=false;}
	// 	}else{
	// 		if(_indexer_declarator()){
	// 			token=_lire_token();
	// 			if(token==BOPEN){
	// 				token=_lire_token();
	// 				if(_accessor_declarations()){
	// 					token=_lire_token();
	// 					if(token==BCLOSE){result=true;}
	// 					else{result=false;}
	// 				}else{result=false;}
	// 			}else{result=false;}
	// 		}else{result=false;}
	// 	}
	// }
	return result;
}

//class_declaration = [attributes] [class_modifiers] ['partial'] 'class' identifier [_type_parameter_list] [class_base] [type_parameter_constraints_clauses] class_body [';'].
boolean _class_declaration(){
	boolean result;
	if(_attributes()){
		token=_lire_token();
		if(_class_modifiers()){
			token=_lire_token();
			if(token==PARTIAL){
				token=_lire_token();
				if(token==CLASS){
					token=_lire_token();
					if(token=IDF){
						token=_lire_token();
						if(_type_parameter_list()){
							token=_lire_token();
							if(_class_base()){
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}else{
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}
						}else{
							token=_lire_token();
							if(_class_base()){
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}else{
								//token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}
						}
					}
				}else{
					token=_lire_token();
					if(token==CLASS){
						token=_lire_token();
						if(token=IDF){
							token=_lire_token();
							if(_type_parameter_list()){
								token=_lire_token();
								if(_class_base()){
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}else{
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}
							}else{
								token=_lire_token();
								if(_class_base()){
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}else{
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}
							}
						}
					}
				}
			}
		}else{
			token=_lire_token();
			if(token==PARTIAL){
				token=_lire_token();
				if(token==CLASS){
					token=_lire_token();
					if(token=IDF){
						token=_lire_token();
						if(_type_parameter_list()){
							token=_lire_token();
							if(_class_base()){
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}else{
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}
						}else{
							token=_lire_token();
							if(_class_base()){
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}else{
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}
						}
					}
				}else{
					token=_lire_token();
					if(token==CLASS){
						token=_lire_token();
						if(token=IDF){
							token=_lire_token();
							if(_type_parameter_list()){
								token=_lire_token();
								if(_class_base()){
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}else{
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}
							}else{
								token=_lire_token();
								if(_class_base()){
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}else{
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}
							}
						}
					}
				}
			}
		}
	}else{
		token=_lire_token();
		if(_class_modifiers()){
			token=_lire_token();
			if(token==PARTIAL){
				token=_lire_token();
				if(token==CLASS){
					token=_lire_token();
					if(token=IDF){
						token=_lire_token();
						if(_type_parameter_list()){
							token=_lire_token();
							if(_class_base()){
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}else{
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}
						}else{
							token=_lire_token();
							if(_class_base()){
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}else{
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}
						}
					}
				}else{
					token=_lire_token();
					if(token==CLASS){
						token=_lire_token();
						if(token=IDF){
							token=_lire_token();
							if(_type_parameter_list()){
								token=_lire_token();
								if(_class_base()){
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}else{
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}
							}else{
								token=_lire_token();
								if(_class_base()){
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}else{
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}
							}
						}
					}
				}
			}
		}else{
			token=_lire_token();
			if(token==PARTIAL){
				token=_lire_token();
				if(token==CLASS){
					token=_lire_token();
					if(token=IDF){
						token=_lire_token();
						if(_type_parameter_list()){
							token=_lire_token();
							if(_class_base()){
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}else{
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}
						}else{
							token=_lire_token();
							if(_class_base()){
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}else{
								// token=_lire_token();
								// if(_type_parameter_constraints_clauses()){
								// 	token=_lire_token();
								// 	if(_class_body()){
								// 		token=_lire_token();
								// 		if(token==PVIRG){result=true;}
								// 		else{result=true;}
								// 	}else{result=false;}
								// }else{
									token=_lire_token();
									if(_class_body()){
										token=_lire_token();
										if(token==PVIRG){result=true;}
										else{result=true;}
									}else{result=false;}
								// }
							}
						}
					}
				}else{
					token=_lire_token();
					if(token==CLASS){
						token=_lire_token();
						if(token=IDF){
							token=_lire_token();
							if(_type_parameter_list()){
								token=_lire_token();
								if(_class_base()){
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}else{
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}
							}else{
								token=_lire_token();
								if(_class_base()){
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG){result=true;}
											else{result=true;}
										}else{result=false;}
									// }
								}else{
									// token=_lire_token();
									// if(_type_parameter_constraints_clauses()){
									// 	token=_lire_token();
									// 	if(_class_body()){
									// 		token=_lire_token();
									// 		if(token==PVIRG){result=true;}
									// 		else{result=true;}
									// 	}else{result=false;}
									// }else{
										token=_lire_token();
										if(_class_body()){
											token=_lire_token();
											if(token==PVIRG)
												{result=true;}
											else{result=true;}
										}else{result=false;}
									// }
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

/*class_modifiers =
	class_modifier
	 | class_modifiers class_modifier.*/
boolean _class_modifiers_aux(){
	boolean result;
	if(_class_modifiers()||token==PARTIAL){result=true;}
	else{
		if(_class_modifier()){
			token=_lire_token();
			if(_class_modifiers_aux()){result=true;}
			else{result=false;}
		}
	}
	return  result;
}

boolean _class_modifiers(){
	boolean result;
	if(_class_modifier()){
		token=_lire_token();
		if(_class_modifiers_aux()){result=true;}
		else{result=false;}
	}else{result=false;}
	return result;
}

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
boolean _class_modifier(){
	boolean result;
	if(token==NEW || token==PUBLIC || token==PROTECTED || token==INTERNAL || token==PRIVATE || token==ABSTRACT || token==SEALED || token==STATIC ){result=true;}
	else{result=false;}
	return result;
}

/*class_base =
	':' class_type
	 | ':' interface_type_list
	 | ':' class_type ',' interface_type_list.
*/
boolean _class_base(){
	boolean result; 
	if(token==DOUBLEDOT){
		token=_lire_token();
		if(_class_type()){result=true;}
		else{result=false;}
	}else{result=false;}
	return result; 
}

/*class_type =
	type_name
	 | 'object'
	 | 'dynamic'
	 | 'string'.*/
boolean _class_type(){
	boolean result;
	if(_type_name()){result=true;}
	else{
		if(token==OBJECT || token==DYNAMIC || token==STRING){result=true;}
		else{result=false;}
	}
	return result;
}

boolean _type_name(){return false;}

/*
class_member_declarations =
	class_member_declaration
	 | class_member_declarations class_member_declaration.

*/

boolean _class_member_declarations_aux(){
	boolean result;
	if(token==BCLOSE){
		result=true;
		follow_token=true;
	}else{
		if(_class_member_declaration()){
			token=_lire_token();
			if(_class_member_declarations_aux()){result=true;}
			else{result=false;}
		}
	}
	return result;
}
boolean _class_member_declarations(){
	boolean result;
	if(_class_member_declaration()){
		token=_lire_token();
		if(_class_member_declarations_aux()){result=true;}
		else{result=false;}
	}else{result=false;}
	return result;
}


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

boolean _class_member_declaration(){
	boolean result;
	// if(_constant_declaration()){result=true;}
	// else{
		if(_field_declaration()){result=true;}
		else{
			if(_method_declaration()){result=true;}
			else{
				// if(_property_declaration()){result=true;}
				// else{
					if(_constructor_declaration()){result=true;}
					else{
						if(_destructor_declaration()){result=true;}
						else{result=false;}
					}
				// }
			}
		}
	// }
	return result;
}

/*constant_declaration =
	[attributes] [constant_modifiers] 'const' type constant_declarators ';'.*/
// boolean _constant_declaration(){
// 	boolean result;
// 	if(_attributes()){
// 		token=_lire_token();
// 		if(_constant_modifiers()){
// 			token=_lire_token();
// 			if(token==CONST){
// 				token=_lire_token();
// 				if(_type()){
// 					token=_lire_token();
// 					if(_constant_declarators()){
// 						token=_lire_token();
// 						if(token==PVIRG){result=true;}
// 						else{result=false;}
// 					}else{result=false;}
// 				}else{result=false;}
// 			}else{result=false;}
// 		}else{
// 			token=_lire_token();
// 			if(token==CONST){
// 				token=_lire_token();
// 				if(_type()){
// 					token=_lire_token();
// 					if(_constant_declarators()){
// 						token=_lire_token();
// 						if(token==PVIRG){result=true;}
// 						else{result=false;}
// 					}else{result=false;}
// 				}else{result=false;}
// 			}else{result=false;}
// 		}
// 	}else{
// 		token=_lire_token();
// 		if(_constant_modifiers()){
// 			token=_lire_token();
// 			if(token==CONST){
// 				token=_lire_token();
// 				if(_type()){
// 					token=_lire_token();
// 					if(_constant_declarators()){
// 						token=_lire_token();
// 						if(token==PVIRG){result=true;}
// 						else{result=false;}
// 					}else{result=false;}
// 				}else{result=false;}
// 			}else{result=false;}
// 		}else{
// 			token=_lire_token();
// 			if(token==CONST){
// 				token=_lire_token();
// 				if(_type()){
// 					token=_lire_token();
// 					if(_constant_declarators()){
// 						token=_lire_token();
// 						if(token==PVIRG){result=true;}
// 						else{result=false;}
// 					}else{result=false;}
// 				}else{result=false;}
// 			}else{result=false;}
// 		}
// 	}
// 	return result;
// }

/*constant_modifiers =
	constant_modifier
	 | constant_modifiers constant_modifier.*/

// boolean _constant_modifiers(){
// 	boolean result;
// 	if(_constant_modifier()){result=true;}
// 	else{}
// 	return result;
// }

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
boolean _remove_accessor_declaration(){
	boolean result;
	if(_attributes()){
		token=_lire_token();
		if(token==REMOVE){
			token=_lire_token();
			if(_block()){
				result=true;
			}else{
				result=false;
			}
		}else{
			result=false;
		}
	}else if(token==REMOVE){
		token=_lire_token();
		if(_block()){
			result=true;
		}else{
			result=false;
		}
	}else{
		result=false;
	}

	return result;
}

/*add_accessor_declaration = attributes 'add' block.
							|'add' block*/

boolean _add_accessor_declaration(){
	boolean result;
	if(_attributes()){
		token=_lire_token();
		if(token==ADD){
			token=_lire_token();
			if(_block()){
				result=true;
			}else{
				result=false;
			}
		}else{
			result=false;
		}
	}else if(token==ADD){
		token=_lire_token();
		if(_block()){
				result=true;
		}else{
				result=false;
		}
	}else{
		result=false;
	}

	return result;
}

/*event_accessor_declarations =
	add_accessor_declaration remove_accessor_declaration
	 | remove_accessor_declaration add_accessor_declaration.*/
boolean _event_accessor_declarations(){
	boolean result;
	if(_add_accessor_declaration()){
		token=_lire_token();
		if(_remove_accessor_declaration()){
			result=true;
		}else{
			result=false;
		}
	}else if(_remove_accessor_declaration()){
		token=_lire_token();
		if(_add_accessor_declaration()){
			result=true;
		}else{
			result=false;
		}
	}else{
		result=false;
	}

	return result;
}

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

boolean _event_modifier(){
	boolean result;
	if(token=NEW){
		result=true;
	}else if(token==PUBLIC){
		result=true;
	}else if(token==PROTECTED){
		result=true;
	}else if(token==PRIVATE){
		result=true;
	}else if(token==STATIC){
		result=true;
	}else if(token==ABSTRACT){
		result=true;
	}else if(token==EXTERN){
		result=true;
	}else{
		result=false;
	}
	return result;
}

/*event_modifiers =
	event_modifier
	 | event_modifiers event_modifier.*/
boolean _event_modifiers(){
	boolean result;
	if(_event_modifier()){
		result=true;
	}else if(_event_modifiers()){
		token=_lire_token();
		if(_event_modifier()){
			result=true;
		}else{
			result=false;
		}
	}else{
		result=false;
	}
	return result;
}	 

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

/*_type_parameter_list = '<' type_parameters '>'.*/

boolean _type_parameter_list(){
	boolean result;
	if(token==LT){
		token=_lire_token();
		if(_type_parameters()){
			token=_lire_token();
			if(token==GT){
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

/*type_parameters =
	attributes type_parameter
	| type_parameter
	 | type_parameters ',' type_parameters_aux

*/

boolean _type_parameters(){
	boolean result;
	if(_attributes()){
		token=_lire_token();
		if(_type_parameter()){
			result=true;
		}else{
			result=false;
		}
	}else if(_type_parameter()){
		result=true;
	}else if(_type_parameters()){
		token=_lire_token();
		if(token==VIRG){
			token=_lire_token();
			if(_type_parameters_aux()){
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

/*type_parameters_aux = attributes type_parameter
						| type_parameter*/
boolean _type_parameters_aux(){
	boolean result;
	if(_attributes()){
		token=_lire_token();
		if(_type_parameter()){
			result=true;
		}else{
			result=false;
		}
	}else if(_type_parameter()){
		result=true;
	}else{
		result=false;
	}
	return result;
}

/*type_parameter =
	identifier.*/

boolean _type_parameter(){
	boolean result;
	if(token==IDF){
		result=true;
	}else{
		result=false;
	}

	return result;
}

/*constructor_constraint =
	'new' '(' ')'.*/

boolean _constructor_constraint(){
	boolean result;
	if(token==NEW){
		token=_lire_token();
		if(token=POPEN){
			token=_lire_token();
			if(token=PCLOSE){
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

/*class_body =
	'{' class_member_declarations '}'.
	|'{' '}' */
boolean _class_body(){
	boolean result;

	if(token=BOPEN){

		token=_lire_token();

		if (token==BCLOSE)
		{
			result=true;
		}else{
			if(_class_member_declarations()){
			token=_lire_token();
			if(token=BCLOSE){
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


/*method_declaration =
	method_header method_body.*/
boolean _method_declaration(){
	boolean result;
	if(_method_header()){
		token=_lire_token();
		if(_method_body()){
			result=true;
		}else{
			result=false;
		}
	}else{
		result=false;
	}
	return result;
}

/*method_header =
	[attributes], [method_modifiers], ['partial'], return_type, member_name, [type_parameter_list], '(', [formal_parameter_list], ')', [type_parameter_constraints_clauses];
	*/

	boolean _method_header(){
		boolean result;

		if (_method_modifiers())
		{
			token=_lire_token();

			if (token==PARTIAL)
			{
				
				token =_lire_token();

				if (_return_type())
				{
					token=_lire_token();

					if (_member_name())
					{
						token=_lire_token();
/*     type parm list a ajouter          */
						if (token==POPEN)
						{
							token=_lire_token();

							if (_formal_parameter_list())
							{	
								token=_lire_token();

								if (token==PCLOSE)
								{
									result=true;
								}else{ // PCOLLSE
									result=false;
								}
								
							}else{ //_formal_parameter_list
								if (token==PCLOSE)
								{
									result=true;
								}else{ // PCOLLSE
									result=false;
								}

							}
						}else{ // popen
							result=false;
						}
					}else{ //_member_name

							result=false;
					}
				}else{
						result=false;
				}


			}else{  //partial
								token =_lire_token();

				if (_return_type())
				{
					token=_lire_token();

					if (_member_name())
					{
						token=_lire_token();
/*     type parm list a ajouter          */
						if (token==POPEN)
						{
							token=_lire_token();

							if (_formal_parameter_list())
							{	
								token=_lire_token();

								if (token==PCLOSE)
								{
									result=true;
								}else{ // PCOLLSE
									result=false;
								}
								
							}else{ //_formal_parameter_list
								if (token==PCLOSE)
								{
									result=true;
								}else{ // PCOLLSE
									result=false;
								}

							}
						}else{ // popen
							result=false;
						}
					}else{ //_member_name

							result=false;
					}
				}else{
						result=false;
				}

			}


			
		}else{ // _method_modifiers

			token=_lire_token();

			if (token==PARTIAL)
			{
				
				token =_lire_token();

				if (_return_type())
				{
					token=_lire_token();

					if (_member_name())
					{
						token=_lire_token();
/*     type parm list a ajouter          */
						if (token==POPEN)
						{
							token=_lire_token();

							if (_formal_parameter_list())
							{	
								token=_lire_token();

								if (token==PCLOSE)
								{
									result=true;
								}else{ // PCOLLSE
									result=false;
								}
								
							}else{ //_formal_parameter_list
								if (token==PCLOSE)
								{
									result=true;
								}else{ // PCOLLSE
									result=false;
								}

							}
						}else{ // popen
							result=false;
						}
					}else{ //_member_name

							result=false;
					}
				}else{
						result=false;
				}


			}else{  //partial
								token =_lire_token();

				if (_return_type())
				{
					token=_lire_token();

					if (_member_name())
					{
						token=_lire_token();
/*     type parm list a ajouter          */
						if (token==POPEN)
						{
							token=_lire_token();

							if (_formal_parameter_list())
							{	
								token=_lire_token();

								if (token==PCLOSE)
								{
									result=true;
								}else{ // PCOLLSE
									result=false;
								}
								
							}else{ //_formal_parameter_list
								if (token==PCLOSE)
								{
									result=true;
								}else{ // PCOLLSE
									result=false;
								}

							}
						}else{ // popen
							result=false;
						}
					}else{ //_member_name

							result=false;
					}
				}else{
						result=false;
				}

			}

		}






		return result;
	}
	
	// method_modifiers =
	// method_modifier
	//  | method_modifiers, method_modifier;
/*
method_modifiers = method_modifier method_modifiers_aux */

boolean _method_modifiers(){
	boolean result;

		if (_method_modifier() )
		{
			token=_lire_token();

			if (_method_modifiers_aux())
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

/*method_modifiers_aux = method_modifier method_modifiers_aux | eps */
boolean _method_modifiers_aux(){
	boolean result;

		if (_return_type() || token==PARTIAL)
		{
			result=true;
			follow_token=true;
		}else{

			if (_method_modifiers())
			{
				result=true;
			}else{

				result=false;
			}
		}


	return result;
}
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


boolean _method_modifier(){
	boolean result;

		switch(token){
		case NEW : 
			result=true;

			break;
		case PUBLIC : 
			result=true;
			
			break;
		case PROTECTED : 

			result=true;
			break;
		case PRIVATE : 
			result=true;
			break;
		case STATIC : 
			result=true;
			break;

		default : result=false;
	}
	return result;
}

/*return_type =
	type
	 | 'void';*/


boolean _return_type(){
	boolean result;

	if (token==VOID)
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

/*member_name =
	identifier
	 | interface_type, '.', identifier;*/
boolean _member_name(){
	boolean result;

	if (token==IDF)
	{
		result=true;
	}else{


		result=false;
	}


	return result;
}



/*method_body =
	block
	 | ';';	*/

boolean _method_body(){
	boolean result;

		if (_block())		
		{
			result=true;
		}else{

			if (token==PVIRG)
			{
				result=true;
			}else{

				result=false;
			}
		}

	return result;

}

