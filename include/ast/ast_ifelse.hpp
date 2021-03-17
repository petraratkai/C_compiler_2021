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
  int size;
public:
  IfElse(Expression* _cond, Statement* _ifstmts, Statement* _elsestmts) : cond(_cond), ifstmts(_ifstmts), elsestmts(_elsestmts) {size = (std::max(ifstmts->getSize(), elsestmts->getSize())+1+_cond->getSize());}
  IfElse(Expression* _cond, Statement* _ifstmts) : cond(_cond), ifstmts(_ifstmts) {elsestmts = NULL; size = (ifstmts->getSize()+1+_cond->getSize());}

//  IfElse(Expression* _cond, Statement* _ifstmts, Statement* _elsestmts, int _size) : cond(_cond), ifstmts(_ifstmts), elsestmts(_elsestmts), size(_size) {}

  virtual Statement* getCond() const override
  { return cond; }

  virtual Statement* getIfStmts() const override
  { return ifstmts; }

  virtual Statement* getElseStmts() const override
  { return elsestmts; }

  virtual bool IsIfElseStmt() const override {return true;}

  virtual int getSize() const override {return size;}
};

#endif
