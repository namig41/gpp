#ifndef SCOPE_H
#define SCOPE_H

#include <string.h>
#include <stdlib.h>

#include "ast.h"

typedef struct	s_scope 
{
	t_ast**		function_definitions;
	size_t		function_definitions_size;

	t_ast**		variable_definitions;
	size_t		variable_definitions_size;
}				t_scope;

t_scope*		init_scope();

t_ast*			scope_add_function_definition(t_scope* scope, t_ast* fdef);	
t_ast*			scope_get_function_definition(t_scope* scope, const char* fname);

t_ast*			scope_add_variable_definition(t_scope* scope, t_ast* fdef);	
t_ast*			scope_get_variable_definition(t_scope* scope, const char* fname);

#endif
