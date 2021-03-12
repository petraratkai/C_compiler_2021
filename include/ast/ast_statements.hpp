#ifndef ast_statements_hpp
#define ast_statements_hpp

//class Variable;
class Expression;
class CompoundStmt;
class Variable;
//class Variable_hash;
class Context;


//#include "ast_expression.hpp"
//#include "ast_primitives.hpp"
//#include "ast_function_call.hpp"
//#include "Context.hpp"
//#include "ast_function.hpp"

#include <string>
#include <vector>
#include "ast_statements.hpp"
#include "Context.hpp"
#include "Variable_hash.hpp"
//typedef enum VarType {IntType, VoidType, CharType, DoubleType, ShortType, LongType, FloatType, SignedType, UnsignedType, StringType} VarType;




//typedef enum VarType {IntType, VoidType, CharType, DoubleType, ShortType, LongType, FloatType, SignedType, UnsignedType, StringType} VarType;
//typedef enum stmt_type {ReturnType, AssignType, DeclareType, DefineType, ExpressionType, FunctionCallType} stmt_type;


/*class Statement
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
  virtual bool IsFunctionCallExpr() const {return false;}
  virtual bool IsVariableStmt() const {return false;}
  virtual bool IsNumberStmt() const {return false;}
  virtual bool IsOperatorStmt() const {return false;}
  virtual bool IsCompoundStmt() const {return false;}

  virtual CompoundStmt* getCompoundStmt() const {}
  virtual std::vector<Statement*>* getStmts() const{}

  virtual Variable *getVariable() const {}

  virtual std::vector<Variable_hash> getVars() const  {}




};*/

/*typedef const Expression *ExpressionPtr;

class Expression
  :public Statement
{

public:
  std::string regname;

    virtual ~Expression()
    {}

    //! Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) const {};

    virtual stmt_type get_type() const override {return ExpressionType;}
    //! Evaluate the tree using the given mapping of variables to numbers
    /*virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    { throw std::runtime_error("Not implemented."); }*/

    /*virtual int getValue() const override {}

    virtual bool IsExpressionStmt() const override {return true;}

    virtual Expression *getRetVal() const override{}

    virtual bool IsFunctionCallExpr() const override {return false;}

    std::string getRegname() const {return regname;}

    virtual void setRegname(std::string regname) {this->regname = regname;}

    virtual bool IsFakeVariableExpr() const {return false;}


};*/

/*class FakeVariable
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
//};

/*class Variable
    : public Expression
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
//};

/*class Variable_hash
{
  std::string name;
  VarType type;
  std::string reg; //register assigned
  int memory_address;
  bool in_memory;
public:
  Variable_hash(const std::string& name, const VarType type) : name(name), type(type) {}
  //Variable_hash(const Variable* var, std::string reg, int memory_address, bool in_memory) : name(var->getName()), type(var->getType()), reg(reg), memory_address(memory_address), in_memory(in_memory) {}
  void setlocation(const std::string& reg, int memory_address, bool in_memory) {this->reg = reg; this->memory_address= memory_address; this->in_memory = in_memory;}
  std::string getReg() const {return reg;}
  std::string getName() const {return name;}
  VarType getType() const {return type;}
  bool isInMemory() const {return in_memory;}
  int getMemAddr() const {return memory_address;}

};*/

/*class Constant
    : public Expression
{
private:
    std::string value;
    VarType type;
public:
    Constant(const std::string& _value, VarType type)
        : value(_value), type(type)
    {}

    const std::string getValue() const
    { return value; }

    VarType getType() const {return type;}

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual bool IsVariableStmt() const override {return true;}
};*/

/*class Declaration
  :public Statement
{
private:
  Variable *var;
  Expression *rhs; //can be null if it's something like int a;
public:
  Declaration(Variable* var, Expression *rhs) : var(var), rhs(rhs) {}
  Declaration(VarType type, const std::string& name, Expression* rhs) : var(new Variable(name, type)), rhs(rhs) {}
  //destructor!!
  virtual Variable *getVariable() const override {return var;}
  Expression *getExpr() const {return rhs;}
  virtual bool IsDeclarationStmt() const override {return true;}

};*/


 //public Statement



/*class ReturnStmt
  : public Statement
{
private:
  Expression *return_value;

public:
  ReturnStmt (Expression *return_value) : return_value(return_value) {}
  virtual stmt_type get_type() const override {return ReturnType;}
  virtual Expression* getRetVal() const override {return return_value;}

  virtual bool IsReturnStmt() const override {return true;}

};*/


/*class AssignmentExpr
  : public Expression
{
private:
  ExpressionPtr lhs;
  ExpressionPtr rhs;
  std::string type_of_assign;

public:
  AssignmentExpr(ExpressionPtr _lhs, ExpressionPtr _rhs, const std::string &_type_of_assign ) : lhs(_lhs), rhs(_rhs), type_of_assign(_type_of_assign) {}
  //destructor?
  virtual bool IsAssignExpr() const override {return true;}

};*/

void Context::moveToOriginal(Variable_hash& var1, Variable_hash& var2);
class CompoundStmt
  :public Statement
{
private:
  std::vector<Statement*>* stmts;
  std::vector<Variable_hash> vars;
  int LocalVarNr;
public:
  CompoundStmt(std::vector<Statement*>* stmts) : stmts(stmts) {LocalVarNr = 0;}
  virtual std::vector<Statement*>* getStmts() const override {return stmts;}
  virtual bool IsCompoundStmt() const override {return true;}
  virtual std::vector<Variable_hash> getVars() const override {return vars;}
  void addVar(const Variable_hash& var)
  {
    vars.push_back(var);
    LocalVarNr++;
  }
  void exitScope(Statement* stmt, Context& ctxt) //parameters: outer scope
  {
      //delete the elements created in inner scope
      for(int i = LocalVarNr-1; i>=0; i--)
      {
        vars.erase(vars.begin()+i);
      }
      //set back the original location
      for(int i = 0; i<vars.size(); i++)
      {
        //ctxt.moveToOriginal(stmt->vars()[i], vars[i]);
      }
  }
  void enterScope(const std::vector<Variable> vars)
  {
    this->vars = vars;
  }

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
/*class IfElse
  :public Statement
{
private:
  Expression* cond;
  CompoundStmt* ifstmts;
  CompoundStmt* elsestmts;
public:
  IfElse(Expression* _cond, CompoundStmt* _ifstmts, CompoundStmt* _elsestmts) : cond(_cond), ifstmts(_ifstmts), elsestmts(_elsestmts) {}

  Expression* getCond() const
  { return cond; }

  CompoundStmt* getIfStmts() const
  { return ifstmts; }

  CompoundStmt* getElseStmts() const
  { return elsestmts; }
};*/


/*class While
  :public Statement
{
private:
  Expression* cond;
  CompoundStmt* stmts;
public:
  While(Expression* _cond, CompoundStmt* _stmts) : cond(_cond), stmts(_stmts) {}

  Expression* getCond() const
  { return cond; }

  CompoundStmt* getCompoundStmt() const
  { return stmts; }
}; */


 //condition, statements


//class Scope_stmt;
//class Expression -> defined in the other file

#endif
