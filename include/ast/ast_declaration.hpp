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
  bool pointer;
public:
  Declaration(Variable* var, Expression *rhs) : var(var)
  {
    pointer = false;
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
    pointer = false;
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
      pointer = false;
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
  Declaration(Variable* var, Expression *rhs, bool pointer) : var(var), pointer(pointer)
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
  Declaration(Variable* var, bool pointer, std::vector<Expression*>* rhs = nullptr, Expression* arraySize = new Number(1)) :var(var), arraySize(arraySize), pointer(pointer)
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
  Declaration(VarType type, bool pointer, const std::string& name, Expression* rhs, Expression* arraySize = new Number(1)) : var(new Variable(name, type)), arraySize(arraySize), pointer(pointer)
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
  //destructor!!
  virtual std::string getVariable() const override {return var->getId();}
  virtual Statement *getExpr(int i = 0) const override {return (*rhs)[i];}
  virtual bool IsDeclarationStmt() const override {return true;}
  virtual int getSize() const override{return size;}
  virtual VarType getType(const std::vector<Variable_hash>& variables) const {return var->getType(variables);}
  void changeType(VarType _type) {var->changeType(_type);}
  virtual int getArraySize() const override {return arraySize->getValue();}
  virtual bool IsPointer() const override {return pointer;}
};


#endif
