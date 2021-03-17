#ifndef ast_for_hpp
#define ast_for_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"
#include "ast_compoundstmt.hpp"

class For
  :public Statement
{
private:
  Statement* first;
  Expression* second;
  Expression* third;
  Statement* stmts;
  int size;
public:
  For(Statement* _first, Expression* _second, Expression* _third, Statement* _stmts) : first(_first), second(_second), third(_third), stmts(_stmts) {size = _stmts->getSize() +3;}
  //While(Expression* _cond, Statement* _stmts, int _size) : cond(_cond), stmts(_stmts), size(_size) {}

  virtual Statement* getFirst() const override
  { return first; }
  virtual Statement* getSecond() const override
  { return second; }
  virtual Statement* getThird() const override
  { return third; }

  virtual int getSize() const override {return size;}

  virtual Statement* getCompoundStmt() const override
  { return stmts; }

  virtual bool IsFor() const {return true;}
};

#endif
