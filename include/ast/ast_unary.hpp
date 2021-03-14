#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>

class Unary
    : public Expression
{
private:
    Expression* expr;
    std::string type_of_op2;
protected:
    Unary(Expression* _expr, std::string _type_of_op2)
        : expr(_expr)
        , type_of_op2(_type_of_op2)
    {}
public:
    virtual ~Unary()
    {
        //delete expr;
    }

    virtual std::string getOpcode() const override
    {
        return type_of_op2;
    }

    virtual Expression* getExpr() const override
    { return expr; }

    virtual bool IsUnary() const override {return true;}

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
