#ifndef ast_do_hpp
#define ast_do_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"
#include "ast_compoundstmt.hpp"

class Do
  :public Statement
{
private:
  Expression* cond;
  Statement* stmts;
  int size;
public:
  Do(Expression* _cond, Statement* _stmts) : cond(_cond), stmts(_stmts) {size = _stmts->getSize() + _cond->getSize() +1;}
  //While(Expression* _cond, Statement* _stmts, int _size) : cond(_cond), stmts(_stmts), size(_size) {}

  Expression* getCond() const
  { return cond; }

  virtual int getSize() const override {return size;}
  
  virtual Statement* getCompoundStmt() const override
  { return stmts; }

  virtual bool IsDo() const {return true;}
};

#endif
