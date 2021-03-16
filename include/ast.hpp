#ifndef ast_hpp
#define ast_hpp

#include <string>

#include "ast/ast_statement.hpp"
#include "ast/ast_expression.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_compoundstmt.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_function.hpp"
#include "ast/ast_function_call.hpp"
#include "ast/ast_expression.hpp"
#include "ast/ast_ifelse.hpp"
#include "ast/ast_number.hpp"
#include "ast/ast_operator.hpp"
#include "ast/ast_program.hpp"
#include "ast/ast_return_stmt.hpp"
#include "ast/ast_unary.hpp"
#include "ast/ast_variable.hpp"
#include "ast/ast_while.hpp"
#include "ast/ast_for.hpp"
#include "ast/Context.hpp"
#include "ast/fakevariable.hpp"
#include "ast/register.hpp"
#include "ast/Variable_hash.hpp"
#include "ast/ast_cond_operator.hpp"
#include "ast/ast_assignmentexpr.hpp"




extern Program *parseAST(const std::string name);

void CodeGen(const Statement *stmt, std::ofstream& Out, Context& variables);

void CompileFunct(const Function *funct, std::ofstream& Out);

void insert_var(std::vector<Variable_hash>* variables, const Variable* var);

void opcode_to_code(const std::string& dest, const std::string& left , const std::string& right,
   const std::string& opcode, std::ostream& Out);

void assignment_to_code(const std::string& dest, const std::string& src,
    const std::string& opcode, std::ostream&  Out);

    static int makeNameUnq=0;

    static std::string makeName(std::string base)
    {
        return "." + base+"_"+std::to_string(makeNameUnq++);
    }

#endif
