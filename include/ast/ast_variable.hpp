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
public:
    Variable(const std::string &_id, VarType type)
        : id(_id), type(type)
    {}

    const std::string getId() const
    { return id; }

    VarType getType() const {return type;}



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
