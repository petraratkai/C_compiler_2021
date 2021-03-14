#ifndef ast_assignmentexpr
#define ast_assignmentexpr

#include <string>
#include "ast_expression.hpp"

class AssignmentExpr
  : public Expression
{
private:
  Expression* lhs;
  Expression* rhs;
  std::string type_of_assign;

public:
  AssignmentExpr(Expression* _lhs, Expression* _rhs, const std::string &_type_of_assign ) : lhs(_lhs), rhs(_rhs), type_of_assign(_type_of_assign) {}
  //destructor?
  virtual bool IsAssignExpr() const override {return true;}
  virtual Expression* getLhs() const override {return lhs;}
  virtual Expression* getRhs() const override {return rhs;}

};

#endif
