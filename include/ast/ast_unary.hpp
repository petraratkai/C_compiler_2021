#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>

class Unary
    : public Expression
{
private:
    Expression* expr;
    std::string type_of_op2;
    VarType keyword;
    int size;
  public:
    Unary(Expression* _expr, const std::string& _type_of_op2)
        : expr(_expr)
        , type_of_op2(_type_of_op2)
    {keyword = IntType; size = (_expr->getSize() +1) ;}
    Unary(VarType _keyword, const std::string& _type_of_op2)
        : keyword(_keyword)
        , type_of_op2(_type_of_op2)
    {expr = NULL; size = (2) ;}
    //Unary(Expression* _expr, std::string _type_of_op2, int _size)
    //    : expr(_expr)
    //    , type_of_op2(_type_of_op2)
    //    , size(_size)
    //{}

    virtual ~Unary()
    {
        //delete expr;
    }

    virtual std::string getOpcode() const override
    {
        return type_of_op2;
    }

    virtual bool IsSizeOf() const override {return type_of_op2 == "sizeof";}

    virtual Expression* getExpr() const override
    { return expr; }

    virtual VarType getKeyword() const override
    { return keyword; }

    virtual bool IsUnary() const override {return true;}

    virtual int getSize() const override {return size;}

    virtual VarType getType(const std::vector<Variable_hash>& variables) const override
    {
      if(IsSizeOf()) return IntType;
      return expr->getType(variables);
    }

    /*virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << getOpcode();
        dst << " ";
        expr->print(dst);
        dst << " )";
    }*/
};


#endif
