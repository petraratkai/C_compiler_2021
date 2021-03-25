#ifndef ast_char_hpp
#define ast_char_hpp

#include <string>
#include <iostream>



class CharLiteral
    : public Expression
{
private:
    std::string value;
    int size;
public:
    CharLiteral(std::string _value)
        : value(_value)
    {size =1;}
    CharLiteral(std::string _value, int _size)
        : value(_value), size(_size)
    {}
    virtual std::string getChar() const override {return value;}
    virtual int getSize() const override {return size;}
    virtual VarType getType(const std::vector<Variable_hash>& variables) const override {return CharType;}

    virtual bool IsCharStmt() const override {return true;}
    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }
};


#endif
