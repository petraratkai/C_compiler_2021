#ifndef ast_returnstmt_hpp
#define ast_returnstmt_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"


class ReturnStmt
  : public Statement
{
private:
  Expression *return_value;

public:
  ReturnStmt (Expression *return_value) : return_value(return_value) {}
  virtual stmt_type get_type() const override {return ReturnType;}
  virtual Expression* getRetVal() const override {return return_value;}

  virtual bool IsReturnStmt() const override {return true;}

};

#endif
