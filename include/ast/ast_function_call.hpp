#ifndef ast_function_call_hpp
#define ast_function_call_hpp



#include <cmath>
#include <string>
#include "fakevariable.hpp"

class FunctionCall
    : public Expression {
private:
    Expression* arg;
    Expression* funct_name;
    int size;
public:
    FunctionCall(Expression* _arg, Expression* funct_name)
        : arg(_arg), funct_name(funct_name)
    {size = /*arg->getSize()*/+1;}
    //FunctionCall(ExpressionPtr _arg, std::string funct_name, int _size)
    //    : arg(_arg), funct_name(funct_name), size(_size)
    //{}
    virtual ~FunctionCall()
    {
        delete arg;
    }


    ExpressionPtr getArg() const
    { return arg; }

    virtual std::string getName() const override{ return funct_name->getName();}

    virtual bool IsFunctionCallExpr() const override {return true;}

    virtual int getSize() const override {return size;}

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
