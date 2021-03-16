#ifndef ast_for_hpp
#define ast_for_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"
#include "ast_compoundstmt.hpp"

class For
  :public Statement
{
private:
  Expression* first;
  Expression* second;
  Expression* third;
  Statement* stmts;
  int size;
public:
  For(Expression* _first, Expression* _second, Expression* _third, Statement* _stmts) : first(_first), second(_second), third(_third), stmts(_stmts) {size = _stmts->getSize() +3;}
  //While(Expression* _cond, Statement* _stmts, int _size) : cond(_cond), stmts(_stmts), size(_size) {}

  Expression* getFirst() const
  { return first; }
  Expression* getSecond() const
  { return second; }
  Expression* getThird() const
  { return third; }

  virtual int getSize() const override {return size;}
  
  virtual Statement* getCompoundStmt() const override
  { return stmts; }

  virtual bool IsWhile() const {return true;}
};

#endif
