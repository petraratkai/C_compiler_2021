#ifndef declaration_hpp
#define declaration_hpp

#include "ast_statement.hpp"
#include "ast_expression.hpp"
#include "ast_variable.hpp"
#include "Variable_hash.hpp"
#include "ast_number.hpp"

class Declaration
  :public Statement
{
private:
  Variable *var;
  std::vector<Expression *>* rhs; //can be null if it's something like int a; vector for pointers
  int size;
  Expression* arraySize;
public:
  Declaration(Variable* var, Expression *rhs) : var(var)
  {
    if(rhs!=nullptr)
      size = rhs->getSize()+1;
    else size = 1;
    this->rhs = new std::vector<Expression*>;
    this->rhs->push_back(rhs);
    Expression* arraysize= new Number(1);
    arraySize = arraysize;
  }
  /*Declaration(Variable* var, std::vector<Expression *>* rhs) : var(var), rhs(rhs)
  {
    if(rhs!=nullptr)
      size = rhs->size()+1;
    else size = 1;
    if(rhs!=nullptr) arraySize = rhs->size();
  }*/
  /*Declaration(Variable* var, int arraySize = 0):var(var), arraySize(arraySize)
  {
    rhs->push_back(nullptr);
    size = arraySize;
  }*/
  Declaration(Variable* var, std::vector<Expression*>* rhs = nullptr, Expression* arraySize = new Number(1)) :var(var), arraySize(arraySize)
  {
    if(rhs!=nullptr)
    {
      this->rhs = rhs;
      size = rhs->size()+1;
    }
    else
    {
      size = 1;
      this->rhs = new std::vector<Expression*>;
      this->rhs->push_back(nullptr);
    }
    if(rhs!=nullptr) this->size = rhs->size();
    else if(arraySize==nullptr) arraySize = new Number(1);
  }
  Declaration(VarType type, const std::string& name, Expression* rhs, Expression* arraySize = new Number(1)) : var(new Variable(name, type)), arraySize(arraySize)
  {
      this->rhs = new std::vector<Expression*>;
      this->rhs->push_back(rhs);
      if(rhs!=nullptr)
        size = rhs->getSize()+1;
      else if(arraySize==nullptr)
      {
        size = 1;
        this->arraySize = new Number(1);
      }
  }
  //Declaration(Variable* var, Expression *rhs, int _size) : var(var), rhs(rhs), size(_size) {}
  //Declaration(VarType type, const std::string& name, Expression* rhs, int _size) : var(new Variable(name, type)), rhs(rhs), size(_size) {}

  //destructor!!
  virtual std::string getVariable() const override {return var->getId();}
  virtual Statement *getExpr(int i = 0) const override {return (*rhs)[i];}
  virtual bool IsDeclarationStmt() const override {return true;}
  virtual int getSize() const override{return size;}
  VarType getType() const {return var->getType();}
  void changeType(VarType _type) {var->changeType(_type);}
  virtual int getArraySize() const override {return arraySize->getValue();}
};


#endif
