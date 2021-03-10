#ifndef ast_function_call_hpp
#define ast_function_call_hpp

#include "ast_statements.hpp"

#include <cmath>
#include <string>

class FunctionCall
    : public Expression {
private:
    ExpressionPtr arg;
    std::string funct_name;
protected:
    FunctionCall(ExpressionPtr _arg, std::string funct_name)
        : arg(_arg), funct_name(funct_name)
    {}
public:
    virtual ~FunctionCall()
    {
        delete arg;
    }

    virtual const char * getFunction() const =0;

    ExpressionPtr getArg() const
    { return arg; }

    virtual std::string getName() const override{ return funct_name;}

    virtual bool IsFunctionCallExpr() const override {return true;}

    /*virtual void print(std::ostream &dst) const override
    {
        dst<<getFunction()<<"( ";
        arg->print(dst);
        dst<<" )";
    }*/

    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }*/
};

//later: Sizeof_Function??


#endif
