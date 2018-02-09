#ifndef START_H
#define START_H

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

boolean _namespace_member_declarations();

boolean _namespace_member_declarations_aux();

/*namespace_member_declaration =
	namespace_declaration
	 | type_declaration;*/

boolean _namespace_member_declaration();

/*type_declaration =
	class_declaration
	 | struct_declaration
	 | interface_declaration
	 | enum_declaration
	 | delegate_declaration;*/


boolean _type_declaration();

/*qualified_alias_member =
	identifier, '::', identifier, [type_argument_list];*/

/*(*B.2.6 Namespaces;*) 
compilation_unit =
	[extern_alias_directives], [using_directives], [global_attributes], [namespace_member_declarations];
	*/

boolean _compilation_unit();


#endif