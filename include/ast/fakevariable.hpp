#ifndef fakevariable_hpp
#define fakevariable_hpp

#include "ast_expression.hpp"
#include "fakevariable.hpp"

class FakeVariable
    : public Expression
{
private:
    std::string id;
    int size;
public:
    FakeVariable(const std::string& _id)
        : id(_id)
    {size =2;}

    virtual const std::string getId() const override
    { return id; }

    virtual int getSize() const override
    { return size; }

    std::string getName() const override {return id;}


    virtual bool IsFakeVariableExpr() const override {return true;}

    virtual VarType getType(const std::vector<Variable_hash>& variables) const override
    {
      for (int i = 0; i<variables.size(); i++)
      {
        if(variables[i].getName()==id)
        {
          return variables[i].getType();
        }
      }
    }
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
