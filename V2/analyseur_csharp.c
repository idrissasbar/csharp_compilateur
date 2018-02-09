
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"analyseur_csharp.h"
#include"types.h"
#include"error.h"
#include "tablesymb.h"
#include "classes.h"
#include "start.h"

extern boolean debug;

extern int yylex();
extern int yylindeno;
extern char *yytext;



typetoken token;

//varvalueType var;

int localrangvar;

boolean follow_token=false;

varvalueType varattribute;
constvalueType constattribute;
typevalueType typeattribute;
instvalueType instattribute;
listinstvalueType listinstattribute;
tokenvalueType tokenattribute;

int rangvar;
boolean semanticerror = false;

typetoken _lire_token(){


	if(follow_token){
		follow_token = false; 
		return token; 
	}else{
	return (typetoken) yylex();
	}
}


void set_idf_attributes(char *name, int line){
	if (debug) printf("[%s]", name);
	varattribute.name = (char *)malloc(sizeof(char) * strlen(name)+1);
	strcpy(varattribute.name, name);
	if (debug) printf("[%s]", varattribute.name);
	varattribute.line = line;
}

void set_number_attributes(double value){
	constattribute.valinit = value;
}

void set_token_attributes(int line){
	tokenattribute.line = line;
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
		{	constattribute.typename = Bool;
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
	{	constattribute.typename = Double;
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
    				constattribute.typename = Int;
    				break;
    	case BYTE : result = true;
    				constattribute.typename = Int;
    				break;
    	case SHORT : result = true;
    				constattribute.typename = Int;
    				break;
    	case USHORT : result = true;
    				constattribute.typename = Int;
    				break;
    	case INT : result = true;
    				constattribute.typename = Int;
    				break;
    	case UINT : result = true;
    				constattribute.typename = Int;
    				break;
    	case LONG : result = true;
    				constattribute.typename = Int;
    				break;
    	case ULONG : result = true;
    				constattribute.typename = Int;
    				break;
    	case CHAR : result = true;
    				constattribute.typename = Int;
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
		constattribute.typename = Double;
		result = true;
	}else{
		if (token == DOUBLE) {
			constattribute.typename = Double;
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
			// 5eme gestion erreur AlreadyDeclared : l'IDF peut être déjà déclaré
				if (inTS(varattribute.name, &rangvar) == true) {
					semanticerror = true;
					creer_sm_erreur_declaration(AlreadyDeclared, varattribute.line, varattribute.name);
				}else{
					varvalueType newvar;
					newvar.nbdecl = 1;
			    		newvar.name = (char *)malloc(sizeof(char)*strlen(varattribute.name)+1);
					strcpy(newvar.name, varattribute.name);
					if (debug) printf("VAR{%s}-->NEW{%s}",varattribute.name, newvar.name);
					newvar.line = varattribute.line;
					newvar.initialisation = varattribute.initialisation; // l'initialisation est marquée par decl_aux dans varattribute
				        newvar.typevar = typeattribute.typename;
			      		newvar.valinit = ((varattribute.initialisation == true)?constattribute.valinit:0.0);
			      		constattribute.valinit=0.0;
					ajouter_nouvelle_variable_a_TS(newvar);
				}

				// 6eme gestion erreur BadlyInitialised : l'IDF peut avoir été initialisé par une constante du mauvais type
				if (varattribute.initialisation == true){
				    if (constattribute.typename != typeattribute.typename){ //Int/Double, Double/Int, Double/Bool, Bool/Double, Int/Bool, Bool/Int
					if ( (typeattribute.typename != Double) || (constattribute.typename != Int) ){  // ce n'est pas Double := Int
						semanticerror = true;
						creer_sm_erreur_declaration(BadlyInitialised, varattribute.line, varattribute.name);
					}
				        //else casting implicit Double = (Double) Int
				    }
				}
			
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
	{	varattribute.initialisation = false;
		result=true;
		follow_token=true;
	}else{

		if (token==EQ)
		{
			token=_lire_token();

			if (_local_variable_initializer())
			{	varattribute.initialisation = true;
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

boolean _local_variable_initializer(listinstvalueType ** pplistinstattribute){
	boolean result;
if (debug) printf ("%s \n ","_local_variable_initializer");

AST *past = (AST *) malloc(sizeof(AST)); // NEW
(*past) = (AST) malloc(sizeof(struct Exp));

	if (_expression(past))	
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
boolean _expression(AST *past){
	boolean result;
if (debug) printf ("%s \n ","_expression");
	if (_non_assignment_expression(past))
	{
		result=true;
	}else{

		if (_assignment(past))
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

boolean _assignment(AST *past){
	boolean result;
if (debug) printf ("%s \n ","_assignment");

	if (_unary_expression())
	{
		token=_lire_token();
		if (_assignment_operator())
		{
			token=_lire_token();
			if (_expression(past)){

				if (semanticerror != true){
				     	if (typevar(localrangvar) == constattribute.typename) {
						//*past = creer_feuille_booleen(true);
						//*ppinstattribute = creer_instruction_affectation(localrangvar, past);
					     }else{
						semanticerror = true ;
						// 2eme gestion erreur IncompatibleAssignType : l'affectation peut être mal typée
						creer_sm_erreur_instruction(IncompatibleAssignType, line(localrangvar), name(localrangvar));
					     }
				     }
				
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

boolean _unary_expression(AST *past){
	boolean result;
if (debug) printf ("%s \n ","_unary_expression");
	if (_primary_expression(past))
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

boolean _primary_expression(AST *past){
	boolean result;
if (debug) printf ("%s \n ","_primary_expression");
	if (_primary_no_array_creation_expression(past))	
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

boolean _primary_no_array_creation_expression(AST *past){
	boolean result;
if (debug) printf ("%s \n ","_primary_no_array_creation_expression");

	if (_literal(past))
	{
		result=true;
	}else{

		if (_simple_name())
		{
			result=true;
		}else{

			if (_parenthesized_expression(past))
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
boolean _literal(AST *past){
	boolean result;

if (debug) printf ("%s \n ","_literal");

	if (token==FALSE)
	{	constattribute.typename = Bool;
		*past = creer_feuille_booleen(true);
		result=true;
	}else{
		if (token==TRUE)
		{	constattribute.typename = Bool;
			*past = creer_feuille_booleen(true);
			result=true;
		}else{
			if (token==INTNUMBER)
			{	constattribute.typename = Int;
				
		*past = creer_feuille_nombre(constattribute.valinit, Int);
				result=true;
			}else{
				if (token==DOUBLENUMBER)
				{	constattribute.typename = Double;

		*past = creer_feuille_nombre(constattribute.valinit, Double);
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
			{	if (inTS(varattribute.name, &localrangvar) == false) {
					semanticerror = true ;
					creer_sm_erreur_instruction(NotDeclared, varattribute.line, varattribute.name);
				}
				result=true;
			}else{

				result=false;
			}
	return result;
}

/*parenthesized_expression =
	'(' expression ')'. */


boolean 	_parenthesized_expression(AST *past){
	boolean result;

		if (debug) printf ("%s \n ","_parenthesized_expression");


	if (token==POPEN)
	{
		token=_lire_token();

		if (_expression(past))
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

boolean _non_assignment_expression(AST *past){
	boolean result;

	
		if (debug) printf ("%s \n ","non_assignment_expression");


		if (_conditional_expression(past))
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

boolean 	_multiplicative_expression(AST *past){
	boolean result;


			if (debug) printf ("%s \n ","_multiplicative_expression");

		AST *past1 = (AST *) malloc(sizeof(AST));
		AST *past2 = (AST *) malloc(sizeof(AST));

		(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW 

	
		if (_unary_expression(past1))
		{
			token=_lire_token();

			//if ((*past1) == NULL) printf("PAST1 \n"); // NEW
		//if ((*past) == NULL) printf("PAST\n"); // NEW
		if ((*past)->noeud.op.expression_gauche == NULL) (*past) = *past1; // initialisation par le première feuille gauche.
		else (*past)->noeud.op.expression_droite = *past1; // NEW 3
		//if (arbre_gauche(*past) == NULL) printf("ag(PAST) 1\n"); // NEW
		//if (arbre_droit(*past) == NULL) printf("ad(PAST) 1\n"); // NEW
		
			if (_multiplicative_expression_aux(past))
			{	

				if ((arbre_droit(*past) != NULL) && (arbre_gauche(*past) != NULL)) {
					if (type(arbre_gauche(*past)) != Bool || type(arbre_droit(*past)) != Bool ){ // NEW 5 & 6 Int/Int ou Double/Double
						(*past)->typename = type(arbre_gauche(*past));

						semanticerror = true;
						creer_sm_erreur_instruction(IncompatibleCompType, tokenattribute.line , "exp");

					}else (*past)->typename = type(arbre_gauche(*past));
				}else {(*past) = *past1;} // ??

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

boolean _multiplicative_expression_aux(AST *past){
	boolean result;

	//unsigned int follow[]={PVIRG,PCLOSE,VIRG,LT,GT,LEQ,GEQ};

			if (debug) printf ("%s \n ","_multiplicative_expression_aux");



		if (token==PLUS ||token==MINUS||token==EQ || token==PVIRG || token==PCLOSE || token==VIRG || token==LT || token==GT || token==NOTEQ)
		{
			result=true;
			follow_token=true;
		}else{

			if (token==MULT)
			{
				token=_lire_token();
*past = creer_noeud_operation('*', *past, NULL, type(*past)); 

				if (_multiplicative_expression(past))
				{
					result=true;
				}else{

					result=false;
				}
			}else{

					if (token==DIV)
						{
							token=_lire_token();
*past = creer_noeud_operation('/', *past, NULL, type(*past)); 

								if (_multiplicative_expression(past))
								{
									result=true;
								}else{

									result=false;
								}
						}else{
								if (token==MOD)
								{
									token=_lire_token();
*past = creer_noeud_operation('%', *past, NULL, type(*past)); 

									if (_multiplicative_expression(past))
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


boolean 	_additive_expression(AST *past){
	boolean result;

		if (debug) printf ("%s \n ","_additive_expression");

		AST *past1 = (AST *) malloc(sizeof(AST));
		AST *past2 = (AST *) malloc(sizeof(AST));

		(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW 

		if (_multiplicative_expression(past1))
		{
			token=_lire_token();

			//if ((*past1) == NULL) printf("PAST1 \n"); // NEW
		//if ((*past) == NULL) printf("PAST\n"); // NEW
		if ((*past)->noeud.op.expression_gauche == NULL) (*past) = *past1; // initialisation par le première feuille gauche.
		else (*past)->noeud.op.expression_droite = *past1; // NEW 3
		//if (arbre_gauche(*past) == NULL) printf("ag(PAST) 1\n"); // NEW
		//if (arbre_droit(*past) == NULL) printf("ad(PAST) 1\n"); // NEW
		

			if (_additive_expression_aux(past))
			{	
				if ((arbre_droit(*past) != NULL) && (arbre_gauche(*past) != NULL)) {
					if (type(arbre_gauche(*past)) == type(arbre_droit(*past))){ // NEW 5 & 6 Int/Int ou Double/Double
						(*past)->typename = type(arbre_gauche(*past));

			

					}else (*past)->typename = Double;
				}else {(*past) = *past1;} // ??
			
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

boolean 	 _additive_expression_aux(AST *past){
	boolean result;

			if (debug) printf ("%s \n ","_additive_expression_aux");


		if (token==PVIRG||token==EQ  || token==PCLOSE || token==VIRG || token==LT)
		{
			result=true;
			follow_token=true;
		}else{

			if (token==PLUS)
			{
				token=_lire_token();
					*past = creer_noeud_operation('+', *past, NULL, type(*past)); 

					if (_additive_expression(past))
					{
						result=true;
					}else{

						result=false;
					}
			}else{
					if (token==MINUS)
					{
						token=_lire_token();
*past = creer_noeud_operation('-', *past, NULL, type(*past)); 

						if (_additive_expression(past))
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


boolean 	_shift_expression(AST *past){
	boolean result;

			if (debug) printf ("%s \n ","_shift_expression");


		AST *past1 = (AST *) malloc(sizeof(AST));
		AST *past2 = (AST *) malloc(sizeof(AST));

		(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW 


		if (_additive_expression(past1))
		{
			token=_lire_token();

			//if ((*past1) == NULL) printf("PAST1 \n"); // NEW
		//if ((*past) == NULL) printf("PAST\n"); // NEW
		if ((*past)->noeud.op.expression_gauche == NULL) (*past) = *past1; // initialisation par le première feuille gauche.
		else (*past)->noeud.op.expression_droite = *past1; // NEW 3
		//if (arbre_gauche(*past) == NULL) printf("ag(PAST) 1\n"); // NEW
		//if (arbre_droit(*past) == NULL) printf("ad(PAST) 1\n"); // NEW
		

			if (_shift_expression_aux(past))
			{	
				if ((arbre_droit(*past) != NULL) && (arbre_gauche(*past) != NULL)) {
					if (type(arbre_gauche(*past)) != Bool || type(arbre_droit(*past)) != Bool ){ // NEW 5 & 6 Int/Int ou Double/Double
						(*past)->typename = type(arbre_gauche(*past));

						semanticerror = true;
						creer_sm_erreur_instruction(IncompatibleCompType, tokenattribute.line , "exp");

					}else (*past)->typename = type(arbre_gauche(*past));
				}else {(*past) = *past1;} // ??
			
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

boolean _shift_expression_aux(AST *past){
	boolean result;

			if (debug) printf ("%s \n ","_shift_expression_aux");


		if (token==PVIRG ||token==EQ|| token==PCLOSE || token==VIRG || token==LT)
		{
			result=true;
			follow_token=true;
			
		}else{
			if (token==LTLT)
			{
				token=_lire_token();
					*past = creer_noeud_operation('L', *past, NULL, type(*past)); 

					if (_shift_expression(past))
					{
						result=true;
					}else{

						result=false;
					}
			}else{
					if (token==GTGT)
					{
						token=_lire_token();
*past = creer_noeud_operation('R', *past, NULL, type(*past)); 

						if (_shift_expression(past))
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

boolean 	_relational_expression(AST *past){
	boolean result;

		if (debug) printf ("%s \n ","_relational_expression");

		AST *past1 = (AST *) malloc(sizeof(AST));
		AST *past2 = (AST *) malloc(sizeof(AST));

		(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW 

		if (_shift_expression(past1))
		{
			token=_lire_token();

			//if ((*past1) == NULL) printf("PAST1 \n"); // NEW
		//if ((*past) == NULL) printf("PAST\n"); // NEW
		if ((*past)->noeud.op.expression_gauche == NULL) (*past) = *past1; // initialisation par le première feuille gauche.
		else (*past)->noeud.op.expression_droite = *past1; // NEW 3
		//if (arbre_gauche(*past) == NULL) printf("ag(PAST) 1\n"); // NEW
		//if (arbre_droit(*past) == NULL) printf("ad(PAST) 1\n"); // NEW
		

			if (_relational_expression_aux(past))
			{	
				if ((arbre_droit(*past) != NULL) && (arbre_gauche(*past) != NULL)) {
					if (type(arbre_gauche(*past)) != Bool || type(arbre_droit(*past)) != Bool ){ // NEW 5 & 6 Int/Int ou Double/Double
						(*past)->typename = type(arbre_gauche(*past));

						semanticerror = true;
						creer_sm_erreur_instruction(IncompatibleCompType, tokenattribute.line , "exp");

					}else (*past)->typename = type(arbre_gauche(*past));
				}else {(*past) = *past1;} // ??
			

				result=true;
			}else{
				result=false;
			}
		}else{

			if (_type())
			{
				
				token=_lire_token();

				if (_relational_expression_aux_aux(past))
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

boolean 	_relational_expression_aux(AST *past){
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

*past = creer_noeud_operation('<', *past, NULL, type(*past)); 

			if (_relational_expression(past))
			{
				result=true;
			}else{

					result=false;
			}
		}else{

			if (token==GT)
			{
				token=_lire_token();

*past = creer_noeud_operation('>', *past, NULL, type(*past)); 
				if (_relational_expression(past))
				{
					result=true;
				}else{

					result=false;
				}
			}else{


				if (token==LEQ)
				{
					token=_lire_token();
*past = creer_noeud_operation('l', *past, NULL, type(*past)); 

					if (_relational_expression(past))
					{
						result=true;
					}else{

						result=false;
					}
				}else{

							if (token==GEQ)
							{
								token=_lire_token();
*past = creer_noeud_operation('g', *past, NULL, type(*past)); 

								if (_relational_expression(past))
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

boolean 	_relational_expression_aux_aux(AST *past){
	boolean result=false;



	return result;
}

/*******************************************equality_expression =
														relational_expression
														 | equality_expression '==' relational_expression
														 | equality_expression '!=' relational_expression.*/


/* equality_expression = relational_expression equality_expression_aux */

boolean 	_equality_expression(AST *past){
	boolean result;

			if (debug) printf ("%s \n ","_equality_expression");

		AST *past1 = (AST *) malloc(sizeof(AST));
		AST *past2 = (AST *) malloc(sizeof(AST));

		(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW 


		if (_relational_expression(past))
		{
			token=_lire_token();

			//if ((*past1) == NULL) printf("PAST1 \n"); // NEW
		//if ((*past) == NULL) printf("PAST\n"); // NEW
		if ((*past)->noeud.op.expression_gauche == NULL) (*past) = *past1; // initialisation par le première feuille gauche.
		else (*past)->noeud.op.expression_droite = *past1; // NEW 3
		//if (arbre_gauche(*past) == NULL) printf("ag(PAST) 1\n"); // NEW
		//if (arbre_droit(*past) == NULL) printf("ad(PAST) 1\n"); // NEW
		
			if (_equality_expression_aux(past))
			{	

				if ((arbre_droit(*past) != NULL) && (arbre_gauche(*past) != NULL)) {
					if (type(arbre_gauche(*past)) == type(arbre_droit(*past))  ){ // NEW 5 & 6 Int/Int ou Double/Double
						(*past)->typename = type(arbre_gauche(*past));

						
					}else {
						semanticerror = true;
						creer_sm_erreur_instruction(IncompatibleCompType, tokenattribute.line , "exp");
						(*past)->typename = Double;

					}
				}else {(*past) = *past1;} // ??

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

boolean 	_equality_expression_aux(AST *past){
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
				*past = creer_noeud_operation('e', *past, NULL, type(*past)); 
				if (_equality_expression(past))
				{
					result=true;
				}else{
					result=false;
				}
			}else{

				if (token==NOTEQ)
				{
					token=_lire_token();
					*past = creer_noeud_operation('n', *past, NULL, type(*past)); 
					if (_equality_expression(past))
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

boolean 	_and_expression(AST *past){
	boolean result;

		if (debug) printf ("%s \n ","_and_expression");

		AST *past1 = (AST *) malloc(sizeof(AST));
		AST *past2 = (AST *) malloc(sizeof(AST));

		(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW 

		if (_equality_expression(past1))
		{
			token=_lire_token();


			//if ((*past1) == NULL) printf("PAST1 \n"); // NEW
		//if ((*past) == NULL) printf("PAST\n"); // NEW
		if ((*past)->noeud.op.expression_gauche == NULL) (*past) = *past1; // initialisation par le première feuille gauche.
		else (*past)->noeud.op.expression_droite = *past1; // NEW 3
		//if (arbre_gauche(*past) == NULL) printf("ag(PAST) 1\n"); // NEW
		//if (arbre_droit(*past) == NULL) printf("ad(PAST) 1\n"); // NEW
		

			if (_and_expression_aux(past))
			{	

				if ((arbre_droit(*past) != NULL) && (arbre_gauche(*past) != NULL)) {
					if (type(arbre_gauche(*past)) != Bool || type(arbre_droit(*past)) != Bool ){ // NEW 5 & 6 Int/Int ou Double/Double
						(*past)->typename = type(arbre_gauche(*past));

						semanticerror = true;
						creer_sm_erreur_instruction(IncompatibleCompType, tokenattribute.line , "exp");

					}else (*past)->typename = type(arbre_gauche(*past));
				}else {(*past) = *past1;} // ??

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

boolean 	_and_expression_aux(AST *past){
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

				*past = creer_noeud_operation('&', *past, NULL, type(*past)); 

				if (_and_expression(past))
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


boolean 	_exclusive_or_expression(AST *past){
	boolean result;

		if (debug) printf ("%s \n ","_exclusive_or_expression");


		AST *past1 = (AST *) malloc(sizeof(AST));
		AST *past2 = (AST *) malloc(sizeof(AST));

		(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW 


		if (_and_expression(past1))
		{
			token=_lire_token();


			//if ((*past1) == NULL) printf("PAST1 \n"); // NEW
		//if ((*past) == NULL) printf("PAST\n"); // NEW
		if ((*past)->noeud.op.expression_gauche == NULL) (*past) = *past1; // initialisation par le première feuille gauche.
		else (*past)->noeud.op.expression_droite = *past1; // NEW 3
		//if (arbre_gauche(*past) == NULL) printf("ag(PAST) 1\n"); // NEW
		//if (arbre_droit(*past) == NULL) printf("ad(PAST) 1\n"); // NEW
		

			if (_exclusive_or_expression_aux(past))
			{	
				if ((arbre_droit(*past) != NULL) && (arbre_gauche(*past) != NULL)) {
					if (type(arbre_gauche(*past)) != Bool || type(arbre_droit(*past)) != Bool ){ // NEW 5 & 6 Int/Int ou Double/Double
						(*past)->typename = type(arbre_gauche(*past));

						semanticerror = true;
						creer_sm_erreur_instruction(IncompatibleCompType, tokenattribute.line , "exp");

					}else (*past)->typename = type(arbre_gauche(*past));
				}else {(*past) = *past1;} // ??

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
boolean 	_exclusive_or_expression_aux(AST *past){
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

				*past = creer_noeud_operation('^', *past, NULL, type(*past)); 

				if (_exclusive_or_expression(past))
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

boolean 	_inclusive_or_expression(AST *past){
	boolean result;

			if (debug) printf ("%s \n ","_inclusive_or_expression");

			AST *past1 = (AST *) malloc(sizeof(AST));
		AST *past2 = (AST *) malloc(sizeof(AST));

		(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW 

		if (_exclusive_or_expression(past1))
		{
			token=_lire_token();

			//if ((*past1) == NULL) printf("PAST1 \n"); // NEW
		//if ((*past) == NULL) printf("PAST\n"); // NEW
		if ((*past)->noeud.op.expression_gauche == NULL) (*past) = *past1; // initialisation par le première feuille gauche.
		else (*past)->noeud.op.expression_droite = *past1; // NEW 3
		//if (arbre_gauche(*past) == NULL) printf("ag(PAST) 1\n"); // NEW
		//if (arbre_droit(*past) == NULL) printf("ad(PAST) 1\n"); // NEW
			

			if (_inclusive_or_expression_aux(past))
			{

				if ((arbre_droit(*past) != NULL) && (arbre_gauche(*past) != NULL)) {
					if (type(arbre_gauche(*past)) != Bool || type(arbre_droit(*past)) != Bool ){ // NEW 5 & 6 Int/Int ou Double/Double
						(*past)->typename = type(arbre_gauche(*past));

						semanticerror = true;
						creer_sm_erreur_instruction(IncompatibleCompType, tokenattribute.line , "exp");

					}else (*past)->typename = type(arbre_gauche(*past));;
				}else {(*past) = *past1;} // ??

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

boolean 	_inclusive_or_expression_aux(AST *past){
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

				*past = creer_noeud_operation('|', *past, NULL, type(*past)); 

				if (_inclusive_or_expression(past))
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

boolean 	_conditional_and_expression(AST *past){
	boolean result;
		if (debug) printf ("%s \n ","_conditional_and_expression");


		AST *past1 = (AST *) malloc(sizeof(AST));
		AST *past2 = (AST *) malloc(sizeof(AST));

		(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW 

		if (_inclusive_or_expression(past1))
		{
			token=_lire_token();

			//if ((*past1) == NULL) printf("PAST1 \n"); // NEW
		//if ((*past) == NULL) printf("PAST\n"); // NEW
		if ((*past)->noeud.op.expression_gauche == NULL) (*past) = *past1; // initialisation par le première feuille gauche.
		else (*past)->noeud.op.expression_droite = *past1; // NEW 3
		//if (arbre_gauche(*past) == NULL) printf("ag(PAST) 1\n"); // NEW
		//if (arbre_droit(*past) == NULL) printf("ad(PAST) 1\n"); // NEW

		
			if (_conditional_and_expression_aux(past))
			{	

				if ((arbre_droit(*past) != NULL) && (arbre_gauche(*past) != NULL)) {
					if (type(arbre_gauche(*past)) != Bool || type(arbre_droit(*past)) != Bool ){ // NEW 5 & 6 Int/Int ou Double/Double
						(*past)->typename = type(arbre_gauche(*past));

						semanticerror = true;
						creer_sm_erreur_instruction(IncompatibleCompType, tokenattribute.line , "exp");

					}else (*past)->typename = type(arbre_gauche(*past));
				}else {(*past) = *past1;} // ??

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

boolean 	_conditional_and_expression_aux(AST *past){
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
						*past = creer_noeud_operation('a', *past, NULL, type(*past)); 
					if (_conditional_and_expression(past))
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

boolean 	_conditional_expression(AST *past){
	boolean result;

			if (debug) printf ("%s \n ","_conditional_expression");


	 	if (_null_coalescing_expression(past))
	 	{
	 		token=_lire_token();
	 		if (_conditional_expression_aux(past))
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

boolean _conditional_expression_aux(AST *past){
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

		if (_expression(past))
		{
			token=_lire_token();
			if (token==DOUBLEDOT)
			{
				token=_lire_token();
				if (_expression(past))
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

boolean 	_null_coalescing_expression(AST *past){
	boolean result;

		if (debug) printf ("%s \n ","_null_coalescing_expression");

	if (_conditional_or_expression(past))
	{
		token=_lire_token();
		if (_null_coalescing_expression_aux(past))
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


boolean _null_coalescing_expression_aux(AST *past){
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
			if (_null_coalescing_expression(past))
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

boolean 	_conditional_or_expression(AST *past){
	boolean result;

			if (debug) printf ("%s \n ","_conditional_or_expression");

		AST *past1 = (AST *) malloc(sizeof(AST));
		AST *past2 = (AST *) malloc(sizeof(AST));

		(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW 

		if (_conditional_and_expression(past1))
		{
			token=_lire_token();

			//if ((*past1) == NULL) printf("PAST1 \n"); // NEW
		//if ((*past) == NULL) printf("PAST\n"); // NEW
		if ((*past)->noeud.op.expression_gauche == NULL) (*past) = *past1; // initialisation par le première feuille gauche.
		else (*past)->noeud.op.expression_droite = *past1; // NEW 3
		//if (arbre_gauche(*past) == NULL) printf("ag(PAST) 1\n"); // NEW
		//if (arbre_droit(*past) == NULL) printf("ad(PAST) 1\n"); // NEW
			if (_conditional_or_expression_aux(past))
			{	
				
				if ((arbre_droit(*past) != NULL) && (arbre_gauche(*past) != NULL)) {
					if (type(arbre_gauche(*past)) != Bool || type(arbre_droit(*past)) != Bool ){ // NEW 5 & 6 Int/Int ou Double/Double
						

						semanticerror = true;
						creer_sm_erreur_instruction(IncompatibleCompType, tokenattribute.line , "exp");

					}else (*past)->typename = type(arbre_gauche(*past));
				}else {(*past) = *past1;} // ??
			
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

boolean 	_conditional_or_expression_aux(AST *past){
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

				*past = creer_noeud_operation('o', *past, NULL, type(*past));

				if (_conditional_or_expression(past))
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

boolean _constant_expression(AST *past){
	boolean result;

			if (debug) printf ("%s \n ","_constant_expression");


	if (_expression(past))
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

boolean _boolean_expression(AST  *past){
	boolean result;
		if (debug) printf ("%s \n ","_boolean_expression");

	if (_expression(past))
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

boolean _statement(listinstvalueType ** pplistinstattribute){
	boolean result;

			if (debug) printf ("%s \n ","_statement");

		if (_declaration_statement())
		{
			result=true;
		}else{
			if (_embedded_statement(pplistinstattribute))
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


boolean _embedded_statement(listinstvalueType ** pplistinstattribute){
	boolean result;

			if (debug) printf ("%s \n ","_embedded_statement");


		if (_block(pplistinstattribute))
		{
			result=true;
		}else{

			if (_empty_statement(pplistinstattribute))
			{
				result=true;
			}else{

				if (_expression_statement(pplistinstattribute))
				{
					result=true;
				}else{
						
					if (_selection_statement(pplistinstattribute))
					{
						result=true;
					}else{
						
						if (_iteration_statement(pplistinstattribute))
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

/*  block = '{''}'
			| '{' [statement_list] '}'*/

boolean _block(listinstvalueType ** pplistinstattribute){
	boolean result;
		if (debug) printf ("%s \n ","_block");

		if (token==BOPEN)
		{
		if (debug) printf ("%s \n ","debut _block");
			token=_lire_token();

			if (token==BCLOSE)
			{
				result=true;
				//follow_token=true;
			}else{

		if (debug) printf ("%s \n ","debut5555 _block");
				if (_statement_list(pplistinstattribute))
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

		if (debug) printf ("%s \n ","FIN _block");
	return result;
}

/******************************************statement_list =
														statement
														 | statement_list statement.*/

/* statement_list = statement statement_list_aux */

boolean 	_statement_list(listinstvalueType ** pplistinstattribute){
	boolean result;

			if (debug) printf ("%s \n ","_statement_list");


		if (_statement(pplistinstattribute))
		{
			token=_lire_token();

			if (_statement_list_aux(pplistinstattribute))
			{
				result=true;
			}else{

				result=false;
			}
		}else{

			result=false;
		}

			if (debug) printf ("%s \n ","FIN  _statement_list");

	return result;
}

/* statement_list_aux = 
						statement statement_list_aux
						| eps */

boolean 	_statement_list_aux(listinstvalueType ** pplistinstattribute){
	boolean result;
		if (debug) printf ("%s 	\n ","_statement_list_aux");

		if ( token==END_OF_FILE || token==BCLOSE)
		{
			result=true;
			follow_token=true;
		}else{

			if (_statement_list(pplistinstattribute))
			{
				result=true;
			}else{

				result=false;
			}
		}

		if (debug) printf ("%s 	\n ","FIN 	_statement_list_aux");
	return result;
}

/*empty_statement = ';'.*/

boolean 	_empty_statement(listinstvalueType ** pplistinstattribute){
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
boolean _expression_statement(listinstvalueType ** pplistinstattribute){
	boolean result;
		if (debug) printf ("%s \n ","_expression_statement");

		if (_statement_expression(pplistinstattribute))
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


boolean 	_statement_expression(listinstvalueType ** pplistinstattribute){
	boolean result;

	AST *past = (AST *) malloc(sizeof(AST)); // NEW
	(*past) = (AST) malloc(sizeof(struct Exp));

		if (debug) printf ("%s \n ","_statement_expression");

		if (_assignment(past))
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

boolean _selection_statement(listinstvalueType ** pplistinstattribute){
	boolean result;

	if(_if_statement(pplistinstattribute)){
		result=true;
	}else{
		if(_switch_statement(pplistinstattribute)){
			result=true;
		}else{
			result=false;
		}
	}
	return result;
}


/*if_statement  = 'if' '(' boolean_expression ')' embedded_statement if_statement_aux
 */
boolean _if_statement(listinstvalueType ** pplistinstattribute){
	boolean result;

	AST *past1 = (AST *) malloc(sizeof(AST));
	(*past1) = (AST) malloc (sizeof(struct Exp)); // NEW

	if(token==IF){
		token=_lire_token();
		if(token==POPEN){
			token=_lire_token();
			if(_boolean_expression(past1)){
				token=_lire_token();
				if(token==PCLOSE){
					token=_lire_token();
					if(_embedded_statement(pplistinstattribute)){
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
boolean _if_statement_aux(listinstvalueType ** pplistinstattribute){
	boolean result;
	if(token==ELSE){
		token=_lire_token();
		if(_embedded_statement(pplistinstattribute)){
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

boolean _switch_statement(listinstvalueType ** pplistinstattribute){
	boolean result;

	AST *past = (AST *) malloc(sizeof(AST)); // NEW
	(*past) = (AST) malloc(sizeof(struct Exp));

	if(token==SWITCH){
		token=_lire_token();

		if(token==POPEN){
			token=_lire_token();

			if(_expression(past)){
				token=_lire_token();

				if(token==PCLOSE){
					token=_lire_token();

					if(_switch_block(pplistinstattribute)){
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

boolean _switch_block(listinstvalueType ** pplistinstattribute){
	boolean result;
	if(token==BOPEN){
		token=_lire_token();
		if (token==BCLOSE)
		{
			result=true;
		}else{
		if(_switch_sections(pplistinstattribute)){
			token=_lire_token();
			if(token==BCLOSE){
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

/****** switch_sections =
	switch_section
	 | switch_sections switch_section.*/

/*switch_sections = switch_section switch_sections_aux.*/

boolean _switch_sections(listinstvalueType ** pplistinstattribute){
	boolean result;
	if(_switch_section(pplistinstattribute)){
		token=_lire_token();
		if(_switch_sections_aux(pplistinstattribute)){
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
	
boolean _switch_sections_aux(listinstvalueType ** pplistinstattribute){
	boolean result;
	if(token==BCLOSE){
		result=true;
		follow_token=true;
	}else{
		if(_switch_sections(pplistinstattribute)){
			
				result=true;
			
		}else{
			result=false;
		}
	}

	return result;
}

/*switch_section =
	switch_labels statement_list.*/

boolean _switch_section(listinstvalueType ** pplistinstattribute){
	boolean result;
	if(_switch_labels(pplistinstattribute)){
		token=_lire_token();
		if(_statement_list(pplistinstattribute)){
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

boolean _switch_labels(listinstvalueType ** pplistinstattribute){
	boolean result;
	if(_switch_label(pplistinstattribute)){
		token=_lire_token();
		if(_switch_labels_aux(pplistinstattribute)){
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

boolean _switch_labels_aux(listinstvalueType ** pplistinstattribute){
	boolean result;
	if(token==BREAK || token==BCLOSE || token==CASE || token==DEFAULT){
		result=true;
		follow_token=true;
		
	}else{
		if(_switch_labels(pplistinstattribute)){

			
				result=true;
			
		}else{
			result=false;
		}
	}

	return result;
}

/*switch_label =
	'case' constant_expression ':'
	 | 'default' ':'.*/
	 
boolean _switch_label(listinstvalueType ** pplistinstattribute){
	boolean result;

	AST *past = (AST *) malloc(sizeof(AST)); // NEW
	(*past) = (AST) malloc(sizeof(struct Exp));

	if(token==CASE){
		token=_lire_token();
		if(_constant_expression(past)){
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

boolean _iteration_statement(listinstvalueType ** pplistinstattribute){
	boolean result;

				if (debug) printf ("%s \n ","_iteration_statement");


	if (_while_statement(pplistinstattribute))
	{
		result=true;
	}else{
		if (_do_statement(pplistinstattribute))
		{
			result=true;
		}else{
			if(_for_statement(pplistinstattribute)){
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

boolean _while_statement(listinstvalueType ** pplistinstattribute){
	boolean result;

					if (debug) printf ("%s \n ","_while_statement");


	AST *past = (AST *) malloc(sizeof(AST)); // NEW
	(*past) = (AST) malloc(sizeof(struct Exp));

	listinstvalueType ** ppwhilecondition = (listinstvalueType **) malloc (sizeof(listinstvalueType *));
	listinstvalueType ** pplistwhile = (listinstvalueType **) malloc (sizeof(listinstvalueType *));
	
	if(token==WHILE){
		token=_lire_token();
		if(token==POPEN){
			token=_lire_token();
			if(_boolean_expression(past)){
				token=_lire_token();
				if(token==PCLOSE){
					token=_lire_token();
					if(_embedded_statement(pplistwhile)){
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

boolean _do_statement(listinstvalueType ** pplistinstattribute){
	boolean result;

				if (debug) printf ("%s \n ","_do_statement");

	AST *past = (AST *) malloc(sizeof(AST)); // NEW
	(*past) = (AST) malloc(sizeof(struct Exp));

	listinstvalueType ** pplistdo = (listinstvalueType **) malloc (sizeof(listinstvalueType *));
	

	if(token==DO){
		token=_lire_token();
		if(_embedded_statement(pplistdo)){
			token=_lire_token();
			if(token==WHILE){
				token=_lire_token();
				if(token==POPEN){
					token=_lire_token();
					if(_boolean_expression(past)){
						token=_lire_token();
						if(token==PCLOSE){
							token=_lire_token();
							if(token==PVIRG){
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

boolean _for_statement(listinstvalueType ** pplistinstattribute){
	

	boolean result;

	if (debug) printf ("%s \n ","_for_statement");

	AST *past = (AST *) malloc(sizeof(AST)); // NEW
	(*past) = (AST) malloc(sizeof(struct Exp));
	 
	
	if (token == FOR){ // Si on trouve FOR 

		token = _lire_token();

		if (token == POPEN){ //  FOR ( 

			token = _lire_token();

			if (token == PVIRG){ //  FOR ( ;

				token = _lire_token();

				if (token == PVIRG){ //  FOR ( ; ; 

					token = _lire_token();

					if (token == PCLOSE){ //  FOR ( ; ; )

						token = _lire_token();

						if(_embedded_statement(pplistinstattribute)){ //  FOR ( ; ; ) embedded_statement -----------------------
							result = true;
						}
						else{
							result = false;
						}
					}else if (_for_iterator(pplistinstattribute)){ // FOR ( ; ; for_iterator 

						token = _lire_token();

						if(token == PCLOSE){ // FOR ( ; ; for_iterator ) 

							token = _lire_token();

							if(_embedded_statement(pplistinstattribute)){ // FOR ( ; ; for_iterator ) embedded_statement ------------------ 
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
				}else if (_for_condition(past)){  // FOR ( ; FOR_CONDITION 

					token = _lire_token();

					if (token == PVIRG)
					{ // FOR ( ; FOR_CONDITION ;

						token = _lire_token();

						if (token == PCLOSE)
						{ //  FOR ( ; FOR_CONDITION ; )

							token = _lire_token();

							if(_embedded_statement(pplistinstattribute)){ // FOR ( ; FOR_CONDITION ; ) embeddedd_statement --------------
								result = true;
							}
							else{
								result = false;
							}
						}else if(_for_iterator(pplistinstattribute))
						{//  FOR ( ; FOR_CONDITION ; FOR_ITERATOR

							token = _lire_token();

							if (token == PCLOSE)
							{ //  FOR ( ; FOR_CONDITION ; FOR_ITERATOR ) 

								token = _lire_token();

								if(_embedded_statement(pplistinstattribute))
								{ // FOR ( ; FOR_CONDITION ; FOR_ITERATOR ) embedded_statement ----------------
									result = true; 
								}else{
									result = false;
								}
							}
							else{
								result = false;
							}
						}else{
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
			}else if (_for_initializer(pplistinstattribute))
			{  // FOR ( FOR_initializer 


				token = _lire_token();

				if (token == PVIRG){   //  FOR ( FOR_initializer ; 

					token = _lire_token();

					if (token == PVIRG){ //  FOR ( FOR_initializer ; ;

						token = _lire_token();

						if (token == PCLOSE){ //  FOR ( FOR_initializer ; ; ) 

							token = _lire_token();

							if(_embedded_statement(pplistinstattribute)){ //  FOR ( FOR_initializer ; ; ) embedded_statement ----------------
								result = true;
							}
							else{
								result = false;
							}
						}

						else if (_for_iterator(pplistinstattribute)){ // FOR ( FOR_initializer ; ; FOR_ITERATOR 

							token = _lire_token();

							if(token == PCLOSE){ //  FOR ( FOR_initializer ; ; FOR_ITERATOR  ) 

								token = _lire_token();

								if(_embedded_statement(pplistinstattribute)){ //  FOR ( FOR_initializer ; ; FOR_ITERATOR ) embedded_statement -----------------------
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

					}else if (_for_condition(past))
					{  // FOR ( FOR_initializer ; FOR_CONDITION

						token = _lire_token();

						if (token == PVIRG){  // FOR ( FOR_initializer ; FOR_CONDITION ; 

							token = _lire_token();

							if (token == PCLOSE){  // FOR ( FOR_initializer ; FOR_CONDITION ; ) 

								token = _lire_token();

								if(_embedded_statement(pplistinstattribute)){  // FOR ( FOR_initializer ; FOR_CONDITION ; ) embedded_statement ----------------------
									result = true;
								}
								else{
									result = false;
								}
							}else if(_for_iterator(pplistinstattribute))
							{  // FOR ( FOR_initializer ; FOR_CONDITION ; FOR_IETRATOR 

								token = _lire_token();

								if (token == PCLOSE){ // FOR ( FOR_initializer ; FOR_CONDITION ; FOR_IETRATOR )

									token = _lire_token();

									if(_embedded_statement(pplistinstattribute)){ // FOR ( FOR_initializer ; FOR_CONDITION ; FOR_IETRATOR ) embedded_statemnt --------------------
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

boolean _for_initializer(listinstvalueType ** pplistinstattribute){

	boolean result = false;

	if(_local_variable_declaration()){

		result = true;
	}

	else{

		if(_statement_expression_list(pplistinstattribute)){

			result = true; 
		}
	}

	return result; 
}

/*for_condition =
	boolean_expression.*/

boolean _for_condition(AST *past){

	boolean result = false; 

	if(_boolean_expression(past)){ //boolean_expression ma3reftch finahiya 

		result = true; 
	}

	return result; 
}

/*for_iterator =
	statement_expression_list.*/

boolean _for_iterator(listinstvalueType ** pplistinstattribute){

	boolean result = false; 

	if(_statement_expression_list(pplistinstattribute)){

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
											| eps
	*/

boolean _statement_expression_list(listinstvalueType ** pplistinstattribute){

	boolean result = false;

	if(_statement_expression(pplistinstattribute)){

			token=_lire_token();

		if(_statement_expression_list_aux(pplistinstattribute)){

			result = true; 

		}else{
			result=false;
		}
	}else{
		result=false;
	}

	return result; 
}


boolean _statement_expression_list_aux(listinstvalueType ** pplistinstattribute){

	boolean result = false; 

	if(token==PVIRG || token==PCLOSE){

		result = true; 
		follow_token=true;
	}else{
		if(token == VIRG){
				token=_lire_token();
				if(_statement_expression_list(pplistinstattribute)){

					result = true; 
				}else{

					result=false;
				}
			
		}else{

			result=false;
		}
	}

	return result; 
	
}








int main(){

	listinstvalueType ** pplistinstattribute = (listinstvalueType **) malloc (sizeof(listinstvalueType *));
	*pplistinstattribute = NULL;

	token=_lire_token();

	if(_statement_list(pplistinstattribute)){
		if (debug) ("0 erreurs syntaxiques\n");
		afficherTS();
		if (nombre_sm_erreurs() == 0){
			if (debug) printf("0 erreurs sémantiques\n");
			if (debug) afficherTS();

			if (debug) { 
			printf("Affichage du Control Flow Graph produit :\n"); afficher_list_inst(*pplistinstattribute);
			}
			if (debug) printf("Generation du code ...\n");			
			pseudocode pc = generer_pseudo_code(*pplistinstattribute);
			if (debug) printf("Affichage du pseudocode généré :\n");
			afficher_pseudo_code(pc);
			
		}else{
			printf("%d erreurs sémantiques\n", nombre_sm_erreurs());
			afficher_sm_erreurs();
		}
	}else{
		printf("plusieurs erreurs syntaxiques\n");
		/* printf("%d erreurs syntaxiques\n", nombre_sx_erreurs());
		afficher_sx_erreurs(); */
		
		printf("%d erreurs sémantiques\n", nombre_sm_erreurs());
		if (nombre_sm_erreurs()> 0) afficher_sm_erreurs();
	}

	
}			
			

