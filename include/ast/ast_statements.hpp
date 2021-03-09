#ifndef ast_statements_hpp
#define ast_statements_hpp

class Variable;
class Expression;

//#include "ast_expression.hpp"
//#include "ast_primitives.hpp"
//#include "ast_function_call.hpp"


typedef enum stmt_type {ReturnType, AssignType, DeclareType, DefineType, ExpressionType, FunctionCallType} stmt_type;


class Statement
{
private:
public:
  virtual ~Statement() {}
  virtual stmt_type get_type() const {}
  virtual int getValue() const {}
  virtual Expression* getRetVal() const {}
  virtual std::string getName() const {}
  virtual bool IsReturnStmt() const {return false;}
  virtual bool IsAssignExpr() const {return false;}
  virtual bool IsDeclarationStmt() const {return false;}
  //virtual bool IsDefineExpr() const {return false;}
  virtual bool IsExpressionStmt() const {return false;}
  virtual bool IsFunctionCallStmt() const {return false;}
  virtual bool IsVariableStmt() const {return false;}
  virtual bool IsNumberStmt() const {return false;}
  virtual bool IsOperatorStmt() const {return false;}
  virtual bool IsCompundStmt() const {return false;}

  virtual std::vector<Statement*>* getStmts() const {}




};

class Declaration
  :public Statement
{
private:
  Variable *var;
  Expression *rhs; //can be null if it's something like int a;
public:
  Declaration(Variable* var, Expression *rhs) : var(var), rhs(rhs) {};
  //destructor!!
  Variable *getVariable() const {return var;}
  Expression *getExpr() const {return rhs;}
  virtual bool IsDeclarationStmt() const override {return true;}

};


 //public Statement

typedef const Expression *ExpressionPtr;

class Expression
  :public Statement
{
public:
    virtual ~Expression()
    {}

    //! Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) const =0;

    virtual stmt_type get_type() const override {return ExpressionType;}
    //! Evaluate the tree using the given mapping of variables to numbers
    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    { throw std::runtime_error("Not implemented."); }*/

    virtual int getValue() const override {}

    virtual bool IsExpressionStmt() const override {return true;}

    virtual Expression *getRetVal() const override{}

};

class ReturnStmt
  : public Statement
{
private:
  Expression *return_value;

public:
  ReturnStmt (Expression *return_value) : return_value(return_value) {}
  virtual stmt_type get_type() const override {return ReturnType;}
  virtual Expression* getRetVal() const override {return return_value;}

  virtual bool IsReturnStmt() const override {return true;}

};


class AssignmentExpr
  : public Expression
{
private:
  Variable *lhs;
  Expression *rhs;

public:
  AssignmentExpr(Variable *lhs, Expression *rhs ) : lhs(lhs), rhs(rhs) {}
  //destructor?
  virtual bool IsAssignExpr() const override {return true;}

};

class CompoundStmt
  :public Statement
{
private:
  std::vector<Statement*>* stmts;
public:
  CompoundStmt(std::vector<Statement*>* stmts) : stmts(stmts) {}
  virtual std::vector<Statement*>* getStmts() const override {return stmts;}
  virtual bool IsCompundStmt() const override {return true;}

};


/*class Declaration //int a;
  : public Statement
{
private:
  //std::string name;
  //VarType type;
  Variable *var;
public:
  Declaration_stmt(Variable *var): var(var) {}
  virtual bool IsDeclarationStmt() const override {return true;}
};*/


//class Definition; //variable, expression
class IfElse; // condition, if_branch, else_branch
class If; //condition, if_branch
class While; //condition, statements

//class Scope_stmt;
//class Expression -> defined in the other file

#endif
