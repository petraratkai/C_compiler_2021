#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "ast_statement.hpp"
#include <string>
#include <iostream>
class Expression;

typedef const Expression *ExpressionPtr;

class Expression
  :public Statement
{

public:
  std::string regname;

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

    virtual bool IsExpressionStmt() const override {return true;}

    virtual Expression *getRetVal() const override{}

    virtual bool IsFunctionCallExpr() const override {return false;}

    std::string getRegname() const {return regname;}

    virtual void setRegname(std::string regname) {}

    virtual bool IsFakeVariableExpr() const {return false;}


};
#endif
