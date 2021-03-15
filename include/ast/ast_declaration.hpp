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
  int size;
public:
  Declaration(Variable* var, Expression *rhs) : var(var), rhs(rhs) {size = rhs->getSize()+1;}
  Declaration(VarType type, const std::string& name, Expression* rhs) : var(new Variable(name, type)), rhs(rhs) {size = 0;}
  //Declaration(Variable* var, Expression *rhs, int _size) : var(var), rhs(rhs), size(_size) {}
  //Declaration(VarType type, const std::string& name, Expression* rhs, int _size) : var(new Variable(name, type)), rhs(rhs), size(_size) {}

  //destructor!!
  virtual std::string getVariable() const override {return var->getId();}
  virtual Statement *getExpr() const override {return rhs;}
  virtual bool IsDeclarationStmt() const override {return true;}
  virtual int getSize() const override {return size;}
};


#endif
