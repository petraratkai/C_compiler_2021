#ifndef ast_cond_operator_hpp
#define ast_cond_operator_hpp


class CondOperator
    : public Expression
{
private:
    Expression* left;
    Expression* middle;
    Expression* right;
    int size;
public:
    CondOperator(Expression* _left, Expression* _middle, Expression* _right)
        : left(_left)
        , middle(_middle)
        , right(_right)
    {size = (std::max(_middle->getSize(),_right->getSize())+left->getSize()+1);}
    //CondOperator(Expression* _left, Expression* _middle, Expression* _right, int _size)
    //    : left(_left)
    //    , middle(_middle)
    //    , right(_right)
    //    , size(_size)
    //{}
    virtual ~CondOperator()
    {
        delete left;
        delete middle;
        delete right;
    }

    virtual Expression* getLeft() const override
    { return left; }

    virtual Expression* getMiddle() const override
    { return middle; }

    virtual Expression* getRight() const override
    { return right; }

    int getSize() const {return size;}

    virtual VarType getType(const std::vector<Variable_hash>& variables) const override {return middle->getType(variables);}

    virtual bool IsCondOperator() const override {return true;}
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
};
#endif
