#ifndef ast_ifelse_hpp
#define ast_ifelse_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"
#include "ast_compoundstmt.hpp"
class IfElse
  :public Statement
{
private:
  Expression* cond;
  CompoundStmt* ifstmts;
  CompoundStmt* elsestmts;
public:
  IfElse(Expression* _cond, CompoundStmt* _ifstmts, CompoundStmt* _elsestmts) : cond(_cond), ifstmts(_ifstmts), elsestmts(_elsestmts) {}

  Expression* getCond() const
  { return cond; }

  CompoundStmt* getIfStmts() const
  { return ifstmts; }

  CompoundStmt* getElseStmts() const
  { return elsestmts; }
};

#endif
