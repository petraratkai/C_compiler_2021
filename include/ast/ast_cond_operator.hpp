#ifndef ast_cond_operator_hpp
#define ast_cond_operator_hpp


class CondOperator
    : public Expression
{
private:
    Expression* left;
    Expression* middle;
    Expression* right;
protected:
    CondOperator(Expression* _left, Expression* _middle, Expression* _right)
        : left(_left)
        , middle(_middle)
        , right(_right)
    {}
public:
    virtual ~CondOperator()
    {
        delete left;
        delete middle;
        delete right;
    }

    Expression* getLeft() const
    { return left; }

    Expression* getMiddle() const
    { return middle; }

    Expression* getRight() const
    { return right; }

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
