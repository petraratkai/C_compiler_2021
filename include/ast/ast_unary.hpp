#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>

class Unary
    : public Expression
{
private:
    ExpressionPtr expr;
    std::string type_of_op2;
protected:
    Unary(const ExpressionPtr _expr, std::string _type_of_op2)
        : expr(_expr)
        , type_of_op2(_type_of_op2)
    {}
public:
    virtual ~Unary()
    {
        delete expr;
    }

    std::string getOpcode() const
    {
        return type_of_op2;
    }

    ExpressionPtr getExpr() const
    { return expr; }

    virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << getOpcode();
        dst << " ";
        expr->print(dst);
        dst << " )";
    }
};
/*
class NegOperator
    : public Unary
{
public:
    NegOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

    /*virtual double evaluate(
        const std::map<std::string, double> &bindings
    ) const override
    {
        // TODO-F: Implement this similar to how AddOperator was implemented.
        //throw std::runtime_error("NegOperator::evaluate is not implemented.");
        return -getExpr()->evaluate(bindings);
    }*/
//};

#endif
