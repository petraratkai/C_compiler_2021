#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <vector>
typedef enum stmt_type {ReturnType, AssignType, DeclareType, DefineType, ExpressionType, FunctionCallType} stmt_type;
class Statement
{
private:
public:
  virtual ~Statement() {}
  virtual stmt_type get_type() const {}
  virtual int getValue() const {}
  virtual Statement* getRetVal() const {}
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
  virtual bool IsWhile() const {return false;}
  virtual Statement* getCompoundStmt() const {return nullptr;}
  virtual std::vector<Statement*>* getStmts() const{}

  virtual std::string getVariable() const {return "";}
  //virtual Expression* getExpr() const {return nullptr;}
  //virtual std::vector<Variable_hash> getVars() const  {}
  virtual bool IsIfElseStmt() const {return false;}
  virtual Statement* getCond() const
  { return nullptr; }

  virtual Statement* getIfStmts() const
  { return nullptr; }

  virtual Statement* getElseStmts() const
  { return nullptr; }



};

#endif
