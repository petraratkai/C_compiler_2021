#ifndef ast_string_hpp
#define ast_string_hpp

#include <string>
#include <iostream>



class StringLiteral
    : public Expression
{
private:
    std::string value;
    int size;
public:
    StringLiteral(std::string _value)
        : value(_value)
    {size =1;}
    StringLiteral(std::string _value, int _size)
        : value(_value), size(_size)
    {}
    virtual std::string getString() const override {return value;}
    virtual int getSize() const override {return size;}
    virtual VarType getType(const std::vector<Variable_hash>& variables) const override {return StringType;}

    virtual bool IsStringStmt() const override {return true;}
    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }
};


#endif
