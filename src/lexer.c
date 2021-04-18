#include "lexer.h"

t_lexer* init_lexer(char* src)
{
	t_lexer* lexer = calloc(1, sizeof(t_lexer));
	lexer->src = src;
	lexer->i = 0;
	lexer->c = lexer->src[lexer->i];
	lexer->src_size = strlen(lexer->src);
	return lexer;
}

void lexer_advance(t_lexer* lexer)
{
	if (lexer->i < lexer->src_size && lexer->c != '\0') {
		lexer->i++;
		lexer->c = lexer->src[lexer->i];
	}
}

char lexer_peek(t_lexer* lexer, int offset)
{
	return lexer->src[MIN(lexer->i + offset, lexer->src_size)];
}

t_token* lexer_advance_current(t_lexer* lexer, int type)
{
	char* value = calloc(1, sizeof(char));
	value[0] = lexer->c;
	value[1] = 0;

	t_token* token = init_token(value, type);
	lexer_advance(lexer);
	return token;
}

t_token* lexer_parse_id(t_lexer* lexer)
{
	char* value = calloc(1, sizeof(char));

	while (isalpha(lexer->c)) {
		value = realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char []){lexer->c, 0});
		lexer_advance(lexer);
	}
	return init_token(value, TOKEN_ID);
}

t_token* lexer_parse_number(t_lexer* lexer)
{
	char* value = calloc(1, sizeof(char));

	while (isdigit(lexer->c)) {
		value = realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char []){lexer->c, 0});
		lexer_advance(lexer);
	}
	return init_token(value, TOKEN_INT);
}


t_token* lexer_parse_string(t_lexer* lexer)
{
	lexer_advance(lexer);
	char* value = calloc(1, sizeof(char));
	int find_end_string = 0;
	while (lexer->c) {
		if (lexer->c == '"') {
			find_end_string = 1;
			break;
		}
		if (lexer->c == '\\') {
			lexer_advance(lexer);
			switch (lexer->c) {
				case 'n':
					lexer->c = '\n';
					break;
				case 't':
					lexer->c = '\t';
					break;
				case 'r':
					lexer->c = '\r';
					break;
				case '\\':
					lexer->c = '\\';
					break;
				case 'f':
					lexer->c = '\f';
					break;
				case '"':
					lexer->c = '\"';
					break;
				case 'b':
					lexer->c = '\b';
					break;
			}
		}
		value = realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char []){lexer->c, 0});
		lexer_advance(lexer);
	}
	if (!find_end_string) {
		printf("[Lexer] Could not find the end of the line");
		exit(1);
	}
	lexer_advance(lexer);
	return init_token(value, TOKEN_STRING);
}

void lexer_skip_comment(t_lexer* lexer)
{
	lexer_skip_whitspace(lexer);
	while (lexer->c == '/') {
		if (lexer->c == '/' && lexer_peek(lexer, 1) == '*') {
			lexer_advance(lexer);
			lexer_advance(lexer);
			do {
				while (lexer->c != '*') {
					lexer_advance(lexer);
				}
				lexer_advance(lexer);
			} while (lexer->c != '/');
			lexer_advance(lexer);
		}
		lexer_skip_whitspace(lexer);
	}
}

void lexer_skip_whitspace(t_lexer* lexer)
{
	while (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t' || lexer->c == '\r') {
		lexer_advance(lexer);
	}
}

t_token* lexer_next_token(t_lexer* lexer)
{
	while (lexer->c != '\0') {

		lexer_skip_comment(lexer);

		if (isalpha(lexer->c)) {
			return lexer_parse_id(lexer);
		}

		if (isdigit(lexer->c)) {
			return lexer_parse_number(lexer);
		}

		if (lexer->c == '"') {
			return lexer_parse_string(lexer);
		}

		switch (lexer->c) {
			case '=': return lexer_advance_current(lexer, TOKEN_EQUALS);
			case '(': return lexer_advance_current(lexer, TOKEN_LPAREN);
			case ')': return lexer_advance_current(lexer, TOKEN_RPAREN);
			case '{': return lexer_advance_current(lexer, TOKEN_LBRACE);
			case '}': return lexer_advance_current(lexer, TOKEN_RBRACE);
			case ',': return lexer_advance_current(lexer, TOKEN_COMMA);
			case '<': return lexer_advance_current(lexer, TOKEN_LT);
			case '>': return lexer_advance_current(lexer, TOKEN_GT);
			case ';': return lexer_advance_current(lexer, TOKEN_SEMI);
			case '+': return lexer_advance_current(lexer, TOKEN_PLUS);
			case '\0': break;
			default: printf("[Lexer]: Unexpect character %c \n", lexer->c); exit(1);
		}
	}
	return init_token(0, TOKEN_EOF);
}

void lexer_retire(t_lexer* lexer, size_t i)
{
	lexer->i = i;
	lexer->c = lexer->src[i];
}
