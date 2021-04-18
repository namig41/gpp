#include "ast.h"

t_ast* init_ast(int type)
{
	t_ast* ast = calloc(1, sizeof(t_ast));
	ast->type = type;

	ast->scope = (void *)0;

	ast->variable_definition_name = (void *)0;
	ast->variable_definition_value = (void *)0;
	
	ast->function_definition_body = (void *)0;

	ast->function_definition_args = (void *)0;
	ast->function_definition_args_size = 0;

	ast->scope = (void *)0;
	ast->variable_name = (void *)0;
	ast->variable_value = (void *)0;

	ast->function_call_name = (void *)0;
	ast->function_call_arguments = (void *)0;
	ast->function_call_arguments_size = 0;

	ast->string_value = (void *)0;

	ast->compound_value = (void *)0;
	ast->compound_size = 0;

	return ast;
}
