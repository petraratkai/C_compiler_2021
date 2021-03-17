#ifndef ast_switch_hpp
#define ast_switch_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"
#include "ast_compoundstmt.hpp"
class Switch
  :public Statement
{
private:
  Expression* cond;
  Statement* stmts;
  int size;
public:
  Switch(Expression* _cond, Statement* _stmts) : cond(_cond), stmts(_stmts) {size = (_stmts->getSize()+1+_cond->getSize());}

//  IfElse(Expression* _cond, Statement* _ifstmts, Statement* _elsestmts, int _size) : cond(_cond), ifstmts(_ifstmts), elsestmts(_elsestmts), size(_size) {}

  virtual Statement* getCond() const override
  { return cond; }

  virtual Statement* getSwitchStmts() const override
  { return stmts; }

  virtual bool IsSwitchStmt() const override {return true;}

  virtual int getSize() const override {return size;}
};

#endif
