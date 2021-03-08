#ifndef ast_primitives_hpp
#define ast_primitives_hpp

class Variable;
//#include "ast_expression.hpp"
#include "ast_primitives.hpp"
//#include "ast_function_call.hpp"


typedef enum stmt_type {ReturnType, AssignType, DeclareType, DefineType, ExpressionType, FunctionCallType} stmt_type;

class Statement
{
private:
public:
  virtual ~Statement() {}
  virtual stmt_type get_type() const {}
  virtual int getValue() const {}
  virtual Expression* getRetVal() const{}
};


class Expression; //public Statement

typedef const Expression *ExpressionPtr;

class Expression
  :public Statement
{
public:
    virtual ~Expression()
    {}

    //! Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) const =0;

    virtual stmt_type get_type() const override {return ExpressionType;}
    //! Evaluate the tree using the given mapping of variables to numbers
    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    { throw std::runtime_error("Not implemented."); }*/
    virtual Expression* getRetVal() const override {}
    virtual int getValue() const override {}
};

class Return_stmt
  : public Statement
{
private:
  Expression *return_value;

public:
  Return_stmt (Expression *return_value) : return_value(return_value) {}
  virtual stmt_type get_type() const override {return ReturnType;}
  virtual Expression* getRetVal() const override {return return_value;}
};


class Assignment_stmt
  : public Statement
{
private:
  Variable *lhs;
  Expression *rhs;

public:
  Assignment_stmt(Variable *lhs, Expression *rhs ) : lhs(lhs), rhs(rhs) {}
  //destructor?

};


class Declaration_stmt //int a;
  : public Statement
{
private:
  //std::string name;
  //VarType type;
  Variable *var;
public:
  Declaration_stmt(Variable *var): var(var) {}
};


class Definition_stmt; //variable, expression
class IfElse_stmt; // condition, if_branch, else_branch
class If_stmt; //condition, if_branch
class While_stmt; //condition, statements

//class Scope_stmt;
//class Expression -> defined in the other file

#endif
