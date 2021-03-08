#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>
//#include "ast_statements.hpp"


class Expression : public Statement; //public Statement

typedef const Expression *ExpressionPtr;

class Expression
  :public Statement
{
public:
    virtual ~Expression()
    {}

    //! Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) const =0;

    virtual stmt_type get_type() const override {return Expression;}
    //! Evaluate the tree using the given mapping of variables to numbers
    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    { throw std::runtime_error("Not implemented."); }*/
};


#endif
