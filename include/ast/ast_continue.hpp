#ifndef ast_continue_hpp
#define ast_continue_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"


class ContinueStmt
  : public Statement
{
private:
  int size;
public:
  ContinueStmt () : size(0) {}
//  ReturnStmt (Expression *return_value, int _size) : return_value(return_value), size(_size) {}

//  virtual stmt_type get_type() const override {return ReturnType;}
//  virtual Statement* getRetVal() const override {return return_value;}
  virtual int getSize() const override {return size;}
  virtual bool IsContinueStmt() const override {return true;}

};

#endif
