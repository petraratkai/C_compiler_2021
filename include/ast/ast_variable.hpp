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
    Expression* arraySize;
public:
    Variable(const std::string &_id, VarType type)
        : id(_id), type(type)
    {size = 1; storage = NoStorage; qualifier = NoQualifier; arraySize = nullptr;}

    Variable(const std::string &_id, VarType type, VarQualifier qualifier)
        : id(_id), type(type), qualifier(qualifier)
    {size = 1; storage = NoStorage; arraySize = nullptr;}

    Variable(const std::string &_id, VarType type, VarStorage storage)
        : id(_id), type(type), storage(storage)
    {size = 1; qualifier = NoQualifier; arraySize = nullptr;}

    Variable(const std::string &_id, VarType type, VarQualifier qualifier, VarStorage storage)
        : id(_id), type(type), qualifier(qualifier), storage(storage)
    {size = 1; arraySize = nullptr;}

    Variable(const std::string &_id, VarType type, VarQualifier qualifier, VarStorage storage, Expression* arraySize)
        : id(_id), type(type), qualifier(qualifier), storage(storage), arraySize(arraySize)
    {size = 1;}
//Variable(const std::string &_id, VarType type, int _size)
//        : id(_id), type(type), size(_size)
//    {}
    void changeType(VarType _type) {type = _type;}

    virtual const std::string getId() const override
    { return id; }

    VarType getType() const {return type;}

    VarQualifier getQualifier() {return qualifier;}

    VarStorage getStorage() {return storage;}

    virtual int getSize() const override {return size;}

    virtual int getArraySize() const override {return arraySize->getValue();}

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
