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
  Statement* ifstmts;
  Statement* elsestmts;
public:
  IfElse(Expression* _cond, CompoundStmt* _ifstmts, CompoundStmt* _elsestmts) : cond(_cond), ifstmts(_ifstmts), elsestmts(_elsestmts) {}

  virtual Statement* getCond() const override
  { return cond; }

  virtual Statement* getIfStmts() const override
  { return ifstmts; }

  virtual Statement* getElseStmts() const override
  { return elsestmts; }

  virtual bool IsIfElseStmt() const override {return true;}
};

#endif
