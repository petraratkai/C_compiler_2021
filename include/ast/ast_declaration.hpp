#ifndef declaration_hpp
#define declaration_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"
#include "ast_variable.hpp"
#include "Variable_hash.hpp"

class Declaration
  :public Statement
{
private:
  Variable *var;
  Expression *rhs; //can be null if it's something like int a;
public:
  Declaration(Variable* var, Expression *rhs) : var(var), rhs(rhs) {}
  Declaration(VarType type, const std::string& name, Expression* rhs) : var(new Variable(name, type)), rhs(rhs) {}
  //destructor!!
  virtual std::string getVariable() const override {return var->getId();}
  Expression *getExpr() const {return rhs;}
  virtual bool IsDeclarationStmt() const override {return true;}

};


#endif
