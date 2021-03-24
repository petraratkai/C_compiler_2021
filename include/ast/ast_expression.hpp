#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "ast_statement.hpp"
#include "vartype.hpp"
#include <string>
#include <iostream>
#include "Variable_hash.hpp"
#include <vector>
class Expression;

typedef const Expression *ExpressionPtr;

class Expression
  :public Statement
{
  std::string regname;
  int size;
  //VarType type;
public:


    virtual ~Expression()
    {}

    //! Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) const {};

    virtual stmt_type get_type() const override {/*return ExpressionType;*/}
    //! Evaluate the tree using the given mapping of variables to numbers
    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    { throw std::runtime_error("Not implemented."); }*/

    virtual int getValue() const override {}

    virtual float getFValue() const override {}

    virtual bool IsFloatStmt() const override {return false;}

    virtual bool IsExpressionStmt() const override {return true;}

    virtual Expression *getRetVal() const override{}

    virtual bool IsFunctionCallExpr() const override {return false;}

    std::string getRegname() const {return regname;}

    int getSize() const {return size;}

    virtual void setRegname(std::string regname) {}

    virtual bool IsFakeVariableExpr() const {return false;}

    virtual bool IsOperatorExpr() const {return false;}

    virtual Expression* getLeft() const
    { return nullptr; }

    virtual Expression* getRight() const
    { return nullptr; }

    virtual Expression* getMiddle() const
    { return nullptr; }

    virtual const std::string getId() const
    { std::cerr << "called getId from expression" << std::endl; }

    virtual std::string getOpcode() const
    { }
    virtual bool IsAssignExpr() const {return false;}
    virtual Expression* getLhs() const {return nullptr;}
    virtual Expression* getRhs() const {return nullptr;}
    //virtual Expression* getExpr() const override {return this;}

    virtual Expression* getExpr() const {return nullptr;}

    virtual bool IsUnary() const {return false;}

    virtual std::string getName() const { return "hey";}

    virtual std::vector<Expression*>* getParams() const {}

    virtual int getArraySize() const {}

    virtual bool IsIndexingOperator() const  {return false;}

    virtual VarType getType(const std::vector<Variable_hash>& variables) const {return IntType;}

    virtual double getDValue() const {}

    virtual bool IsDoubleStmt() const {return false;}

    virtual bool IsAddressOperator() const {return false;}

    virtual Expression* getFakeVariable() const
    { }

    virtual bool IsDereferenceOp() const {return false;}

    virtual bool IsCondOperator() const{return false;}



};
#endif
