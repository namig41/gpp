#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_token
{

	enum {
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_LBRACE,
		TOKEN_RBRACE,
		TOKEN_COLON,
		TOKEN_COMMA,
		TOKEN_LT,
		TOKEN_GT,
		TOKEN_INT,
		TOKEN_STRING,
		TOKEN_SEMI,
		TOKEN_PLUS,
		TOKEN_MINUS,
		TOKEN_EOF
	} type;

	char*		value;

}				t_token;

t_token*		init_token(char* value, int type);

char*			token_to_string(t_token* token);

#endif
