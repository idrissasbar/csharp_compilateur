
#include"analyseur_csharp.h"


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types.h"
#include"error.h"
#include "tablesymb.h"
#include "start.h"
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

/*(*B.2.6 Namespaces;*) 
compilation_unit =
	[extern_alias_directives], [using_directives], [global_attributes], [namespace_member_declarations];
	*/

boolean _compilation_unit(){
	boolean result;

	if (_namespace_member_declarations())
	{
		result=true;
	}else{
		result=false;
	}

	return result;
}

/*namespace_declaration =
	'namespace', qualified_identifier, namespace_body, [';'];*/

/*qualified_identifier =
	identifier
	 | qualified_identifier, '.', identifier;*/

/*namespace_body =
	'{', [extern_alias_directives], [using_directives], [namespace_member_declarations], '}';
	*/

/*extern_alias_directives =
	extern_alias_directive
	 | extern_alias_directives, extern_alias_directive;
	 */

/*extern_alias_directive =
	'extern', 'alias', identifier, ';';*/

/*using_directives =
	using_directive
	 | using_directives, using_directive;*/

/*using_directive =
	using_alias_directive
	 | using_namespace_directive;*/

/*using_alias_directive =
	'using', identifier, '=', namespace_or_type_name, ';';*/

/*using_namespace_directive =
	'using', namespace_name, ';';*/

/*namespace_member_declarations =
	namespace_member_declaration
	 | namespace_member_declarations, namespace_member_declaration;*/

boolean _namespace_member_declarations(){
	boolean result;


	if (_namespace_member_declaration())
	{
		token=_lire_token();

		if (_namespace_member_declarations_aux())
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


boolean _namespace_member_declarations_aux(){
	boolean result;
	
	if (token==BCLOSE)
	{
		result=true;
		follow_token=true;
	}else{

		if (_namespace_member_declarations())
		{
			result=true;
		}else{
			result=false;
		}
	}



	return result;
}

/*namespace_member_declaration =
	namespace_declaration
	 | type_declaration;*/

boolean _namespace_member_declaration(){
	boolean result;

		if (_type_declaration())
		{
			result=true;
		}else{
			// namespace_declaration

			result=false;
		}

	return result;
}

/*type_declaration =
	class_declaration
	 | struct_declaration
	 | interface_declaration
	 | enum_declaration
	 | delegate_declaration;*/


boolean _type_declaration(){
	boolean result;

		if (_class_declaration())
		{
			result=true;
		}else{
			result=false;
		}

	return result; 
}

/*qualified_alias_member =
	identifier, '::', identifier, [type_argument_list];*/

