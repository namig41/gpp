#include "parser.h"

static t_scope* get_node_scope(t_parser* parser, t_ast* node)
{
	return (node->scope == 0) ? parser->scope : node->scope;
}

t_parser*		init_parser(t_lexer* lexer)
{
	t_parser* parser = (t_parser *)calloc(1, sizeof(t_parser));
	parser->cur_token = lexer_next_token(lexer);
	parser->lexer = lexer;
	parser->scope = init_scope();
	return parser;
}

t_token*		parser_advance(t_parser* parser, int type)
{
	if (parser->cur_token->type != type) {
		printf("[Parser]: Unexpected token: %s",
				token_to_string(parser->cur_token));
		exit(1);
	}
	parser->prev_token = parser->cur_token;
	parser->cur_token = lexer_next_token(parser->lexer);
	return parser->cur_token;
}

t_ast*			parser_parse(t_parser* parser)
{
	return parser_parse_statements(parser, parser->scope);
}

t_ast*			parser_parse_statement(t_parser* parser, t_scope* scope)
{
	switch (parser->cur_token->type) {
		case TOKEN_ID:			return parser_parse_id(parser, scope);
		case TOKEN_STRING:		return parser_parse_string(parser, scope);
		case TOKEN_INT:			return parser_parse_integer(parser, scope);		
		case TOKEN_EOF:			return init_ast(AST_NOOP);
	}
	return init_ast(AST_NOOP);
}

t_ast*			parser_parse_statements(t_parser* parser, t_scope* scope)
{
	t_ast* compound = init_ast(AST_COMPOUND);
	compound->scope = scope;
	compound->compound_value = (t_ast **)calloc(1, sizeof(t_ast *));

	t_ast* ast_statment = parser_parse_statement(parser, scope);
	compound->compound_value[0] = ast_statment;
	compound->compound_size += 1;

	do {
		parser_advance(parser, TOKEN_SEMI);
		ast_statment = parser_parse_statement(parser, scope);
		if (ast_statment) {
			compound->compound_size += 1;
			compound->compound_value = (t_ast **)realloc(compound->compound_value,
					compound->compound_size * sizeof(t_ast *));
			compound->compound_value[compound->compound_size - 1] = ast_statment;

		}
	} while (parser->cur_token->type == TOKEN_SEMI);
	return compound;
}

t_ast*			parser_parse_scope_variable(t_parser* parser, t_scope* scope)
{
	t_ast* ast_variable = init_ast(AST_VARIABLE);
	ast_variable->variable_name = parser->prev_token->value;
	ast_variable->scope = scope;
	return ast_variable;
}

t_ast*			parser_parser_assignment(t_parser* parser, t_scope* scope)
{
	t_ast* ast_assignment = init_ast(AST_ASSIGNMENT);

	ast_assignment->variable_name = parser->prev_token->value;
	parser_advance(parser, TOKEN_EQUALS);
	t_ast* ast_value = parser_parse_expr(parser, scope);
	ast_assignment->variable_value = ast_value;
	ast_assignment->scope = scope;
	return ast_assignment;
}

t_ast*			parser_parse_variable(t_parser* parser, t_scope* scope)
{
	parser_advance(parser, TOKEN_ID);

	if (parser->cur_token->type == TOKEN_LPAREN) {
		return parser_parse_function_call(parser, scope);
	} else if (parser->cur_token->type == TOKEN_EQUALS) {
		return parser_parser_assignment(parser, scope);
	} else {
		return parser_parse_scope_variable(parser, scope);
	}
}

t_ast*			parser_parse_variable_definition(t_parser* parser, t_scope* scope)
{
	parser_advance(parser, TOKEN_ID);
	char* variable_definition_name = parser->cur_token->value;

	parser_advance(parser, TOKEN_ID);
	parser_advance(parser, TOKEN_EQUALS);
	
	t_ast* variable_definition_value = parser_parse_expr(parser, scope);

	t_ast* variable_definition = init_ast(AST_VARIABLE_DEFINITION);
	variable_definition->variable_definition_name = variable_definition_name;
	variable_definition->variable_definition_value = variable_definition_value;	

	variable_definition->scope = scope;
	return variable_definition;
}

t_ast*			parser_parse_function_definition(t_parser* parser, t_scope* scope)
{
	t_ast* function_definition = init_ast(AST_FUNCTION_DEFINITION);
	parser_advance(parser, TOKEN_ID);

	char* function_name = parser->cur_token->value;

	parser_advance(parser, TOKEN_ID);
	parser_advance(parser, TOKEN_LPAREN);

	if (parser->cur_token->type != TOKEN_RPAREN)
	{
		t_ast* variable = parser_parse_id(parser, scope);
		function_definition->function_definition_args_size += 1;
		function_definition->function_definition_args = (t_ast **)calloc(function_definition->function_definition_args_size, sizeof(t_ast *));
		function_definition->function_definition_args[function_definition->function_definition_args_size - 1] = variable;

		while (parser->cur_token->type == TOKEN_COMMA) {
			parser_advance(parser, TOKEN_COMMA);
			t_ast* variable = parser_parse_id(parser, scope);
			function_definition->function_definition_args_size += 1;
			function_definition->function_definition_args = (t_ast **)realloc(function_definition->function_definition_args,
					function_definition->function_definition_args_size * sizeof(t_ast *));
			function_definition->function_definition_args[function_definition->function_definition_args_size - 1] = variable;
		}
	}

	parser_advance(parser, TOKEN_RPAREN);
	parser_advance(parser, TOKEN_LBRACE);

	t_scope* local_scope = init_scope();
	function_definition->function_definition_body = parser_parse_statements(parser, local_scope);
	function_definition->function_definition_body->scope = local_scope;
	function_definition->function_definition_name = strdup(function_name);

	parser_advance(parser, TOKEN_RBRACE);
	function_definition->scope = scope;
	return function_definition;
}

t_ast*			parser_parse_expr(t_parser* parser, t_scope* scope)
{
	return parser_parse_term(parser, scope);
}

t_ast*			parser_parse_term(t_parser* parser, t_scope* scope)
{
	t_ast*	ast_left = parser_parse_factor(parser, scope);

	while (parser->cur_token->type == TOKEN_PLUS ||
			parser->cur_token->type == TOKEN_MINUS) {
		parser_advance(parser, parser->cur_token->type);
		t_ast* ast_binop = init_ast(AST_BINOP);
		ast_binop->left = ast_left;
		ast_binop->op = parser->prev_token->type;
		ast_left = ast_binop;
		ast_binop->right = parser_parse_factor(parser, scope);
	}
	return ast_left;
}

t_ast*			parser_parse_factor(t_parser* parser, t_scope* scope)
{
	switch (parser->cur_token->type) {
		case TOKEN_ID:		return parser_parse_id(parser, scope);
		case TOKEN_STRING:	return parser_parse_string(parser, scope);
		case TOKEN_INT:		
			return parser_parse_integer(parser, scope);
		case TOKEN_LPAREN:
			parser_advance(parser, TOKEN_LPAREN);
			t_ast* ast_expr = parser_parse_expr(parser, scope);
			parser_advance(parser, TOKEN_RPAREN);
			return ast_expr;
	}
	return init_ast(AST_NOOP);
}

t_ast*			parser_parse_function_call(t_parser* parser, t_scope* scope)
{
	t_ast* function_call = init_ast(AST_FUNCTION_CALL);
	function_call->function_call_name = parser->prev_token->value;
	function_call->function_call_arguments = (t_ast **)calloc(1, sizeof(t_ast *));

	parser_advance(parser, TOKEN_LPAREN);

	if (parser->cur_token->type != TOKEN_RPAREN) {
		t_ast* ast_expr = parser_parse_expr(parser, scope);
		function_call->function_call_arguments[0] = ast_expr;
		function_call->function_call_arguments_size += 1;

		while (parser->cur_token->type == TOKEN_COMMA) {
			parser_advance(parser, TOKEN_COMMA);
			ast_expr = parser_parse_expr(parser, scope);
			function_call->function_call_arguments_size += 1;
			function_call->function_call_arguments = (t_ast **)realloc(function_call->function_call_arguments,
					function_call->function_call_arguments_size * sizeof(t_ast *));
			function_call->function_call_arguments[function_call->function_call_arguments_size - 1] = ast_expr;
		}
	}
	parser_advance(parser, TOKEN_RPAREN);
	function_call->scope = scope;
	return function_call;
}

t_ast*			parser_parse_string(t_parser* parser, t_scope* scope)
{
	t_ast* ast_string = init_ast(AST_STRING);
	ast_string->string_value = parser->cur_token->value;
	parser_advance(parser, TOKEN_STRING);
	ast_string->scope = scope;
	return ast_string;
}

t_ast*			parser_parse_comparsion(t_parser* parser, t_scope* scope)
{
	t_ast* ast_comp;
	if (strcmp(parser->cur_token->value, "while") == 0) {
		ast_comp = init_ast(AST_WHILE);
	} else {
		ast_comp = init_ast(AST_IF);
	}
	parser_advance(parser, TOKEN_ID);
	parser_advance(parser, TOKEN_LPAREN);
	ast_comp->left = parser_parse_expr(parser, scope);
	if (
			parser->cur_token->type == TOKEN_EQ ||
			parser->cur_token->type == TOKEN_NE ||
			parser->cur_token->type == TOKEN_LE ||
			parser->cur_token->type == TOKEN_LT ||
			parser->cur_token->type == TOKEN_GE ||
			parser->cur_token->type == TOKEN_GT
	   ) {
		
		ast_comp->op = parser->cur_token->type;
		parser_advance(parser, parser->cur_token->type);
	} 
	ast_comp->right = parser_parse_expr(parser, scope);
	parser_advance(parser, TOKEN_RPAREN);
	parser_advance(parser, TOKEN_LBRACE);

	ast_comp->scope = scope;
	/* t_scope* local_scope = init_scope(); */
	ast_comp->comparsion_body = parser_parse_statements(parser, scope);
	ast_comp->comparsion_body->scope = scope;

	parser_advance(parser, TOKEN_RBRACE);
	ast_comp->scope = scope;
	return ast_comp;
}

t_ast*			parser_parse_id(t_parser* parser, t_scope* scope)
{
	if (strcmp(parser->cur_token->value, "var") == 0) {
		return parser_parse_variable_definition(parser, scope);
	} else if (strcmp(parser->cur_token->value, "def") == 0) {
		return parser_parse_function_definition(parser, scope);
	} else if (strcmp(parser->cur_token->value, "if") == 0) {
		return parser_parse_comparsion(parser, scope);
	} else if (strcmp(parser->cur_token->value, "while") == 0) {
		return parser_parse_comparsion(parser, scope);
	} else {
		return parser_parse_variable(parser, scope);
	}
}

t_ast*			parser_parse_integer(t_parser* parser, t_scope* scope)
{
	t_ast* ast_integer = init_ast(AST_INT);
	ast_integer->int_value = atoi(parser->cur_token->value);
	parser_advance(parser, TOKEN_INT);
	if (parser->cur_token->type == TOKEN_MULT ||
			parser->cur_token->type == TOKEN_DIV) {
		parser_advance(parser, parser->cur_token->type);
		t_ast* ast_binop = init_ast(AST_BINOP);
		ast_binop->left = ast_integer;
		ast_binop->op = parser->prev_token->type;
		ast_binop->right = parser_parse_factor(parser, scope);
		ast_integer = ast_binop;
	}
	ast_integer->scope = scope;
	return ast_integer;
}
