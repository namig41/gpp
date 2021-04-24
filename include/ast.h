#ifndef AST_H
#define AST_H

#include <stdlib.h>

typedef struct		s_ast
{
	enum 
	{
		AST_VARIABLE_DEFINITION,
		AST_FUNCTION_DEFINITION,
		AST_VARIABLE,
		AST_FUNCTION_CALL,
		AST_STRING,
		AST_INT,
		AST_COMPOUND,
		AST_BINOP,
		AST_ASSIGNMENT,
		AST_NOOP
	} type;

	struct s_scope*	scope;

	struct s_scope*	global_scope;

	char*			variable_definition_name;
	struct s_ast*	variable_definition_value;

	char*			variable_name;
	struct s_ast*	variable_value;

	char*			function_definition_name;
	struct s_ast*	function_definition_body;
	struct s_ast**	function_definition_args;
	size_t			function_definition_args_size;

	char*			function_call_name;
	struct s_ast**	function_call_arguments;
	size_t			function_call_arguments_size;

	char*			string_value;
	int				int_value;

	struct s_ast**	compound_value;
	size_t			compound_size;

	struct s_ast*	left;
	struct s_ast*	right;
	int				op;

}					t_ast;

t_ast*				init_ast(int type);

#endif
