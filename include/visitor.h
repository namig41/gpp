#ifndef VISITOR_H
#define VISITOR_H

#include <string.h>
#include <stdio.h>

#include "ast.h"
#include "scope.h"
#include "macros.h"
#include "token.h"

typedef struct		s_visitor
{
}					t_visitor;

t_visitor*			init_visitor();

t_ast*				visitor_visit(t_visitor* visitor, t_ast* node);
t_ast* 				visitor_visit_variable_definition(t_visitor* visitor, t_ast* node);
t_ast* 				visitor_visit_variable(t_visitor* visitor, t_ast* node);
t_ast* 				visitor_visit_string(t_visitor* visitor, t_ast* node);
t_ast* 				visitor_visit_integer(t_visitor* visitor, t_ast* node);
t_ast* 				visitor_visit_binop(t_visitor* visitor, t_ast* node);
t_ast* 				visitor_visit_assignment(t_visitor* visitor, t_ast* node);
t_ast* 				visitor_visit_compound(t_visitor* visitor, t_ast* node);
t_ast* 				visitor_visit_function_call(t_visitor* visitor, t_ast* node);
t_ast*				visitor_visit_function_definition(t_visitor* visitor, t_ast* node);
t_ast*				visitor_visit_if(t_visitor* visitor, t_ast* node);
t_ast*				visitor_visit_while(t_visitor* visitor, t_ast* node);
t_ast*				visitor_visit_comparsion(t_visitor* visitor, t_ast* node);

#endif
