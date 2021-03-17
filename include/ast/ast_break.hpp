#ifndef ast_break_hpp
#define ast_break_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"


class BreakStmt
  : public Statement
{
private:
  int size;
public:
  BreakStmt () : size(0) {}
//  ReturnStmt (Expression *return_value, int _size) : return_value(return_value), size(_size) {}

//  virtual stmt_type get_type() const override {return ReturnType;}
//  virtual Statement* getRetVal() const override {return return_value;}
  virtual int getSize() const override {return size;}
  virtual bool IsBreakStmt() const override {return true;}

};

#endif
