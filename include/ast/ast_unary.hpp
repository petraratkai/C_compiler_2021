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
        //delete expr;
    }

    std::string getOpcode() const
    {
        return type_of_op2;
    }

    ExpressionPtr getExpr() const
    { return expr; }

    /*virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << getOpcode();
        dst << " ";
        expr->print(dst);
        dst << " )";
    }*/
};


#endif
