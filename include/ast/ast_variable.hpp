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
    VarStorage storage;
    VarQualifier qualifier;
    int size;
public:
    Variable(const std::string &_id, VarType type)
        : id(_id), type(type)
    {size = 2; storage = NoStorage; qualifier = NoQualifier;}

    Variable(const std::string &_id, VarType type, VarQualifier qualifier)
        : id(_id), type(type), qualifier(qualifier)
    {size = 2; storage = NoStorage;}

    Variable(const std::string &_id, VarType type, VarStorage storage)
        : id(_id), type(type), storage(storage)
    {size = 2; qualifier = NoQualifier;}

    Variable(const std::string &_id, VarType type, VarQualifier qualifier, VarStorage storage)
        : id(_id), type(type), qualifier(qualifier), storage(storage)
    {size = 2;}
//Variable(const std::string &_id, VarType type, int _size)
//        : id(_id), type(type), size(_size)
//    {}

    virtual const std::string getId() const override
    { return id; }

    VarType getType() const {return type;}

    VarQualifier getQualifier() {return qualifier;}

    VarStorage getStorage() {return storage;}

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
