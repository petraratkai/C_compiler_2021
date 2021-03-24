#ifndef ast_dereference_operator_hpp
#define ast_dereference_operator_hpp


class DereferenceOperator
    : public Expression
{
private:
    FakeVariable* thing;
    int size;
public:
    DereferenceOperator(FakeVariable* _thing)
        : thing(_thing)
    {size = 1;}
    //CondOperator(Expression* _left, Expression* _middle, Expression* _right, int _size)
    //    : left(_left)
    //    , middle(_middle)
    //    , right(_right)
    //    , size(_size)
    //{}
    virtual ~DereferenceOperator()
    {
        delete thing;
    }

    virtual Expression* getFakeVariable() const override
    { return thing; }

    int getSize() const {return size;}

    virtual VarType getType(const std::vector<Variable_hash>& variables) const override {return thing->getType(variables);}

    /*virtual void print(std::ostream &dst) const override
    {
        dst<<"( ";
        left->print(dst);
        dst<<" ";
        middle<<print(dst);
        dst<<" ";
        right->print(dst);
        dst<<" )";
    }*/
    virtual bool IsDereferenceOp() const override {return true;}
};
#endif
