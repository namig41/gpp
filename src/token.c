#include "token.h"

t_token* init_token(char* value, int type)
{
	t_token* token = (t_token *)calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;
	return token;
}

static const char* token_type_to_stirng(t_token* token)
{
	static const char* token_names[] = {
		"TOKEN_ID",
		"TOKEN_EQUALS",
		"TOKEN_LPAREN",
		"TOKEN_RPAREN",
		"TOKEN_LBRACE",
		"TOKEN_RBRACE",
		"TOKEN_COLON",
		"TOKEN_COMMA",
		"TOKEN_LT",
		"TOKEN_GT",
		"TOKEN_INT",
		"TOKEN_STRING",
		"TOKEN_SEMI",
		"TOKEN_PLUS",
		"TOKEN_MINUS",
		"TOKEN_EOF"
	};

	return token_names[token->type];
}

char* token_to_string(t_token* token)
{
	const char* type_str = token_type_to_stirng(token);
	const char* token_template = "<type=%s, int_type=%d, value=%s>\n";
	char* str = (char *)calloc(strlen(type_str) + strlen(token_template), sizeof(char));
	sprintf(str, token_template, type_str, token->type, token->value);
	return str;
}
