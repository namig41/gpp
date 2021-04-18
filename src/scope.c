#include "scope.h"

t_scope*		init_scope()
{
	t_scope* scope = calloc(1, sizeof(t_scope));
	scope->function_definitions = (void *) 0;
	scope->function_definitions_size = 0;

	scope->variable_definitions = (void *) 0;
	scope->variable_definitions_size = 0;

	return scope;
}

t_ast*			scope_add_function_definition(t_scope* scope, t_ast* fdef)
{
	scope->function_definitions_size += 1;

	if (scope->function_definitions == (void *) 0) {
		scope->function_definitions = calloc(1, sizeof(t_ast *));
	} else {
		scope->function_definitions = realloc(
				scope->function_definitions,
				scope->function_definitions_size * sizeof(t_ast *));
	}

	scope->function_definitions[scope->function_definitions_size - 1] = fdef;
	return fdef;
}

t_ast*			scope_get_function_definition(t_scope* scope, const char* fname)
{
	for (int i = 0; i < scope->function_definitions_size; i++) {
		t_ast* fdef = scope->function_definitions[i];

		if (strcmp(fdef->function_definition_name, fname) == 0) {
			return fdef;
		}
	}
	return (void *)0;
}

t_ast*			scope_add_variable_definition(t_scope* scope, t_ast* var_def)
{
	scope->variable_definitions_size += 1;
	if (scope->variable_definitions == (void *)0) {
		scope->variable_definitions = calloc(1, sizeof(t_ast *));
	} else {
		scope->variable_definitions = realloc(
				scope->variable_definitions,
				scope->variable_definitions_size * sizeof(t_ast *));
	}
	scope->variable_definitions[scope->variable_definitions_size - 1] = var_def;
	return var_def;
}

t_ast*			scope_get_variable_definition(t_scope* scope, const char* var_name)
{
	for (int i = 0; i < scope->variable_definitions_size; i++) {
		t_ast* var_def = scope->variable_definitions[i];

		if (strcmp(var_def->variable_definition_name, var_name) == 0) {
			return var_def;
		}
	}
	return (void *)0;
}
