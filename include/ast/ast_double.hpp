#ifndef ast_double_hpp
#define ast_double_hpp
#include "ast_expression.hpp"
class Dnumber
    : public Expression
{
private:
    double value;
    int size;
public:
    Dnumber(double _value)
        : value(_value)
    {size =1;}
    Dnumber(double _value, int _size)
        : value(_value), size(_size)
    {}
      virtual double getDValue() const override {return value;}
    virtual int getSize() const override {return size;}


      virtual bool IsDoubleStmt() const override {return true;}
    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }

      virtual VarType getType(const std::vector<Variable_hash>& variables) const override {return DoubleType;}
};

#endif
