#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_statements.hpp"
//#include "ast/ast_expression.hpp"


#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_unary.hpp"


#include "ast/ast_function.hpp"
#include "ast/ast_function_call.hpp"
#include "ast/ast_program.hpp"



extern const Program *parseAST();

void CodeGen(const Program *prog);

#endif
