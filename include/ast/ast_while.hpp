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
  Statement* stmts;
public:
  While(Expression* _cond, Statement* _stmts) : cond(_cond), stmts(_stmts) {}

  Expression* getCond() const
  { return cond; }

  virtual Statement* getCompoundStmt() const override
  { return stmts; }

  virtual bool IsWhile() const {return true;}
};

#endif
