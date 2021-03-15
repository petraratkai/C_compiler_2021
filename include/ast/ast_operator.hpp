#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <cmath>

class Operator
    : public Expression
{
private:
    Expression* left;
    Expression* right;
    std::string type_of_op;
    int size;
public:
    Operator(Expression* _left, Expression* _right, const std::string &_type_of_op)
        : left(_left)
        , right(_right)
        , type_of_op(_type_of_op)
    {size = (std::max(_left->getSize(),_right->getSize())+1);}
    //Operator(Expression* _left, Expression* _right, const std::string &_type_of_op, int _size)
    //    : left(_left)
    //    , right(_right)
    //    , type_of_op(_type_of_op)
    //    , size(_size)
    //{}

    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual std::string getOpcode() const override
    {
        return type_of_op;
    }

    virtual Expression* getLeft() const override
    { return left; }

    virtual Expression* getRight() const override
    { return right; }

    virtual int getSize() const override {return size;}
    
    virtual bool IsOperatorExpr() const override {return true;}

    virtual void print(std::ostream &dst) const override
    {
        dst<<"( ";
        left->print(dst);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->print(dst);
        dst<<" )";
    }
};



//class LessThanOperator;
//class GreaterThanOperator;
//class GreaterThanEqualOperator;
//class LessThanEqualOperator;
//class EqualToOperator;
// ?: operator?, shift operators,

#endif
