#ifndef ast_float_hpp
#define ast_float_hpp

#include <string>
#include <iostream>


/*class Variable
    : public Expression
{
private:
    std::string id;
    VarType type;
public:
    Variable(const std::string &_id, VarType type)
        : id(_id), type(type)
    {}

    const std::string getId() const
    { return id; }

    VarType getType() const {return type;}

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual bool IsVariableStmt() const override {return true;}
    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
        // If the binding does not exist, this will throw an error
        return bindings.at(id);
    }
};*/

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


      virtual bool IsFloatStmt() const override {return true;}
    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }
};


#endif
