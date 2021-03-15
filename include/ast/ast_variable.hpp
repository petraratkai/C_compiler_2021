#ifndef variable_hpp
#define variable_hpp

#include <string>
#include "ast_expression.hpp"
#include "Variable_hash.hpp"
class Variable
    : public Expression //probably won't be an expression
{
private:
    std::string id;
    VarType type;
    int size;
public:
    Variable(const std::string &_id, VarType type)
        : id(_id), type(type)
    {size = 0;}

Variable(const std::string &_id, VarType type, int _size)
        : id(_id), type(type), size(_size)
    {}

    virtual const std::string getId() const override
    { return id; }

    VarType getType() const {return type;}

    virtual int getSize() const override {return size;}

    virtual bool IsVariableStmt() const override {return true;}
    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
        // If the binding does not exist, this will throw an error
        return bindings.at(id);
    }*/
};
#endif
