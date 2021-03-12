#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <cmath>

class Operator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
    std::string type_of_op;
protected:
    Operator(ExpressionPtr _left, ExpressionPtr _right, const std::string &_type_of_op)
        : left(_left)
        , right(_right)
        , type_of_op(_type_of_op)
    {}
public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    std::string getOpcode() const
    {
        return type_of_op;
    }

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

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
