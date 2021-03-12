#ifndef ast_while_hpp
#define ast_while_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"
#include "ast_compoundstmt.hpp"

class While
  :public Statement
{
private:
  Expression* cond;
  CompoundStmt* stmts;
public:
  While(Expression* _cond, CompoundStmt* _stmts) : cond(_cond), stmts(_stmts) {}

  Expression* getCond() const
  { return cond; }

  CompoundStmt* getCompoundStmt() const
  { return stmts; }
};

#endif
