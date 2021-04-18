#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "token.h"
#include "macros.h"

typedef struct		s_lexer
{
	size_t			i;
	size_t			src_size;
	char*			src;
	char			c;
}					t_lexer;

t_lexer*			init_lexer(char* src);

void				lexer_advance(t_lexer* lexer);
void				lexer_retire(t_lexer* lexer, size_t i;);
void 				lexer_skip_whitspace(t_lexer* lexer);
void 				lexer_skip_comment(t_lexer* lexer);

t_token*			lexer_parse_id(t_lexer* lexer);
t_token* 			lexer_parse_number(t_lexer* lexer);
t_token* 			lexer_parse_string(t_lexer* lexer);

t_token*			lexer_next_token(t_lexer* lexer);
t_token* 			lexer_advance_current(t_lexer* lexer, int type);

char				lexer_peek(t_lexer* lexer, int offset);

#endif
