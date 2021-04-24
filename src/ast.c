#include "ast.h"

t_ast* init_ast(int type)
{
	t_ast* ast = (t_ast *)calloc(1, sizeof(t_ast));
	ast->type = type;

	ast->scope = 0;

	ast->variable_definition_name = 0;
	ast->variable_definition_value = 0;
	
	ast->function_definition_body = 0;
	ast->function_definition_args = 0;
	ast->function_definition_args_size = 0;

	ast->comparsion_body = 0;

	ast->scope = 0;
	ast->variable_name = 0;
	ast->variable_value = 0;

	ast->function_call_name = 0;
	ast->function_call_arguments = 0;
	ast->function_call_arguments_size = 0;

	ast->string_value = 0;

	ast->compound_value = 0;
	ast->compound_size = 0;

	return ast;
}
