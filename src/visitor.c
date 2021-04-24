#include "visitor.h"

static t_ast* builtin_function_print(t_visitor* visitor, t_ast* node)
{
	for (int i = 0; i < (int)node->function_call_arguments_size; i++) {
		t_ast* visited_ast = visitor_visit(visitor, node->function_call_arguments[i]);
		
		switch (visited_ast->type) {
			case AST_STRING: printf("%s", visited_ast->string_value); break;
			case AST_INT:	 printf("%d", visited_ast->int_value); break;
		}
	}
	return init_ast(AST_NOOP);
}

t_visitor* init_visitor()
{
	t_visitor* visitor = (t_visitor *)calloc(1, sizeof(t_visitor));
	return visitor;
}

t_ast* visitor_visit(t_visitor* visitor, t_ast* node)
{
	switch (node->type) {
		case AST_VARIABLE_DEFINITION:	return visitor_visit_variable_definition(visitor, node);
		case AST_FUNCTION_DEFINITION:	return visitor_visit_function_definition(visitor, node);
		case AST_VARIABLE:				return visitor_visit_variable(visitor, node);
		case AST_STRING:				return visitor_visit_string(visitor, node);
		case AST_INT:					return visitor_visit_integer(visitor, node);
		case AST_COMPOUND:				return visitor_visit_compound(visitor, node);
		case AST_FUNCTION_CALL:			return visitor_visit_function_call(visitor, node);
		case AST_BINOP:					return visitor_visit_binop(visitor, node);
		case AST_ASSIGNMENT:			return visitor_visit_assignment(visitor, node);
		case AST_IF:					return visitor_visit_if(visitor, node);
		case AST_WHILE:					return visitor_visit_while(visitor, node);
		case AST_NOOP:					return init_ast(AST_NOOP);
	}
	return init_ast(AST_NOOP);
}

t_ast* visitor_visit_variable_definition(t_visitor* visitor, t_ast* node)
{
	Q_UNUSED(visitor);
	scope_add_variable_definition(node->scope, node);
	return node;
}

t_ast* visitor_visit_variable(t_visitor* visitor, t_ast* node)
{
	t_ast* var_def = scope_get_variable_definition(node->scope, node->variable_name);
	if (var_def) {
		return visitor_visit(visitor, var_def->variable_definition_value);
	}

	printf("Undefined variable: %s\n", node->function_call_name);
	exit(1);
}

t_ast* visitor_visit_string(t_visitor* visitor, t_ast* node)
{
	return node;
}

t_ast* visitor_visit_integer(t_visitor* visitor, t_ast* node)
{
	return node;
}

t_ast* visitor_visit_compound(t_visitor* visitor, t_ast* node)
{
	for (int i = 0; i < (int)node->compound_size; i++) {
		visitor_visit(visitor, node->compound_value[i]);
	}
	return init_ast(AST_NOOP);
}

t_ast* visitor_visit_function_call(t_visitor* visitor, t_ast* node)
{
	if (strcmp(node->function_call_name, "print") == 0) {
		return builtin_function_print(visitor, node);
	} else {
		t_ast* fdef = scope_get_function_definition(node->scope, node->function_call_name);

		if (fdef) {
			for (int i = 0; i < (int)fdef->function_definition_args_size; i++) {
				
				t_ast* ast_var = fdef->function_definition_args[i];
				t_ast* ast_value = node->function_call_arguments[i];

				t_ast* local_variable = scope_get_variable_definition(fdef->function_definition_body->scope, ast_var->variable_name);
				if (local_variable) {
					local_variable->variable_definition_value = ast_value;
				} else {
					t_ast* variable_def = init_ast(AST_VARIABLE_DEFINITION);
					variable_def->variable_definition_name = strdup(ast_var->variable_name);
					variable_def->variable_definition_value = ast_value;
					scope_add_variable_definition(fdef->function_definition_body->scope, variable_def);
				}

			}
			return visitor_visit(visitor, fdef->function_definition_body);
		}

	}
	printf("Undefined method: %s\n", node->function_call_name);
	exit(1);
}

t_ast* visitor_visit_function_definition(t_visitor* visitor, t_ast* node)
{
	Q_UNUSED(visitor);
	scope_add_function_definition(node->scope, node);
	return node;
}

t_ast* visitor_visit_assignment(t_visitor* visitor, t_ast* node) 
{
	t_ast* variable = scope_get_variable_definition(node->scope, node->variable_name);
	if (!variable) {
		printf("Undefined variable: %s\n", node->variable_name);
		exit(1);
	}
	variable->variable_definition_value = visitor_visit(visitor, node->variable_value);
	return node;
}

t_ast* visitor_visit_binop(t_visitor* visitor, t_ast* node)
{
	t_ast* res = init_ast(AST_INT);

	switch (node->op) {
		case TOKEN_PLUS:
			res->int_value = visitor_visit(visitor, node->left)->int_value +
						visitor_visit(visitor, node->right)->int_value;
			break;
		case TOKEN_MINUS:
			res->int_value = visitor_visit(visitor, node->left)->int_value -
						visitor_visit(visitor, node->right)->int_value;
			break;
		case TOKEN_MULT:
			res->int_value = visitor_visit(visitor, node->left)->int_value *
						visitor_visit(visitor, node->right)->int_value;
			break;
		case TOKEN_DIV:
			res->int_value = visitor_visit(visitor, node->left)->int_value /
						visitor_visit(visitor, node->right)->int_value;
			break;
	}
	return res;
}

t_ast* visitor_visit_comparsion(t_visitor* visitor, t_ast* node)
{
	t_ast* res = init_ast(AST_INT);

	switch (node->op) {
		case TOKEN_EQ:
			res->int_value = visitor_visit(visitor, node->left)->int_value ==
						visitor_visit(visitor, node->right)->int_value;
			break;
		case TOKEN_NE:
			res->int_value = visitor_visit(visitor, node->left)->int_value !=
						visitor_visit(visitor, node->right)->int_value;
			break;
		case TOKEN_LE:
			res->int_value = visitor_visit(visitor, node->left)->int_value <=
						visitor_visit(visitor, node->right)->int_value;
			break;
		case TOKEN_LT:
			res->int_value = visitor_visit(visitor, node->left)->int_value <
						visitor_visit(visitor, node->right)->int_value;
			break;
		case TOKEN_GE:
			res->int_value = visitor_visit(visitor, node->left)->int_value >=
						visitor_visit(visitor, node->right)->int_value;
			break;
		case TOKEN_GT:
			res->int_value = visitor_visit(visitor, node->left)->int_value >
						visitor_visit(visitor, node->right)->int_value;
			break;
	}
	return res;
}

t_ast* visitor_visit_if(t_visitor* visitor, t_ast* node)
{
	t_ast* res = visitor_visit_comparsion(visitor, node);

	if (res->int_value) {
		return visitor_visit(visitor, node->comparsion_body);
	}

	return node;
}

t_ast* visitor_visit_while(t_visitor* visitor, t_ast* node)
{
	t_ast* res = visitor_visit_comparsion(visitor, node);

	while (res->int_value) {
		visitor_visit(visitor, node->comparsion_body);
		res = visitor_visit_comparsion(visitor, node);
	}

	return node;
}
