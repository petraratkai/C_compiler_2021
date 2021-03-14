#ifndef fakevariable_hpp
#define fakevariable_hpp

#include "ast_expression.hpp"

class FakeVariable
    : public Expression
{
private:
    std::string id;
public:
    FakeVariable(const std::string& _id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }




    virtual bool IsFakeVariableExpr() const override {return true;}
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