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
    int size;
  public:
    Unary(Expression* _expr, const std::string& _type_of_op2)
        : expr(_expr)
        , type_of_op2(_type_of_op2)
    {size = (_expr->getSize() +1) ;}
    //Unary(Expression* _expr, std::string _type_of_op2, int _size)
    //    : expr(_expr)
    //    , type_of_op2(_type_of_op2)
    //    , size(_size)
    //{}

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

    virtual int getSize() const override {return size;}

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
