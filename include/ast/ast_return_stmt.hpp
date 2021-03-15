#ifndef ast_returnstmt_hpp
#define ast_returnstmt_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"


class ReturnStmt
  : public Statement
{
private:
  Expression *return_value;
  int size;
public:
  ReturnStmt (Expression *return_value) : return_value(return_value) {size = (return_value->getSize()+1);}
//  ReturnStmt (Expression *return_value, int _size) : return_value(return_value), size(_size) {}

  virtual stmt_type get_type() const override {return ReturnType;}
  virtual Statement* getRetVal() const override {return return_value;}
  virtual int getSize() const override {return size;}
  virtual bool IsReturnStmt() const override {return true;}

};

#endif
