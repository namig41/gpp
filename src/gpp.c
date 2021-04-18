#include "gpp.h"

void gpp_compiler(const char* file_name)
{
	char* src = io_read_file(file_name);
	t_lexer* lexer = init_lexer(src);
	t_parser* parser = init_parser(lexer);
	t_visitor* visitor = init_visitor();

	t_ast* root = parser_parse(parser);
	visitor_visit(visitor, root);
}
