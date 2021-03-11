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

class CondOperator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr middle;
    ExpressionPtr right;
protected:
    CondOperator(ExpressionPtr _left, ExpressionPtr _middle ExpressionPtr _right)
        : left(_left)
        , middle(_middle)
        , right(_right)
    {}
public:
    virtual ~CondOperator()
    {
        delete left;
        delete middle;
        delete right;
    }

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getMiddle() const
    { return middle; }

    ExpressionPtr getRight() const
    { return right; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<"( ";
        left->print(dst);
        dst<<" ";
        middle<<print(dst);
        dst<<" ";
        right->print(dst);
        dst<<" )";
    }
};
/*class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // TODO-C : Run bin/eval_expr with something like 5+a, where a=10, to make sure you understand how this works
        double vl=getLeft()->evaluate(bindings);
        double vr=getRight()->evaluate(bindings);
        return vl+vr;
    }*/
//};
/*
class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // TODO-D : Implement this, based on AddOperator::evaluate
        //throw std::runtime_error("MulOperator::evaluate is not implemented.");
        double v1 = getLeft()->evaluate(bindings);
        double v2 = getRight()->evaluate(bindings);
        return v1-v2;
    }*/
//};


/* class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

  /*  virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        //throw std::runtime_error("MulOperator::evaluate is not implemented.");
        double v1 = getLeft()->evaluate(bindings);
        double v2 = getRight()->evaluate(bindings);
        return v1*v2;
    }*/
//};

/*class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        //throw std::runtime_error("DivOperator::evaluate is not implemented.");
        double v1 = getLeft()->evaluate(bindings);
        double v2 = getRight()->evaluate(bindings);
        return v1/v2;
    }*/

//};

//class LessThanOperator;
//class GreaterThanOperator;
//class GreaterThanEqualOperator;
//class LessThanEqualOperator;
//class EqualToOperator;
// ?: operator?, shift operators,

#endif
