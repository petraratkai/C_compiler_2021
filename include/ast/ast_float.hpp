#ifndef ast_float_hpp
#define ast_float_hpp

#include <string>
#include <iostream>



class Fnumber
    : public Expression
{
private:
    float value;
    int size;
public:
    Fnumber(float _value)
        : value(_value)
    {size =1;}
    Fnumber(float _value, int _size)
        : value(_value), size(_size)
    {}
      virtual float getFValue() const override {return value;}
    virtual int getSize() const override {return size;}
    virtual VarType getType(const std::vector<Variable_hash>& variables) const override {return FloatType;}

      virtual bool IsFloatStmt() const override {return true;}
    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }
};


#endif
