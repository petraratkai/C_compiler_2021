#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>



class Number //integer!!
    : public Expression
{
private:
    int value;
    int size;
public:
    Number(int _value)
        : value(_value)
    {size =1;}
    Number(int _value, int _size)
        : value(_value), size(_size)
    {}
      virtual int getValue() const override {return value;}
    virtual int getSize() const override {return size;}


      virtual bool IsNumberStmt() const override {return true;}
    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }

    virtual VarType getType(const std::vector<Variable_hash>& variables) const override {return IntType;}
};


#endif
