#ifndef ast_compoundstmt_hpp
#define ast_compoundstmt_hpp

#include <vector>
#include "ast_statement.hpp"
#include "Variable_hash.hpp"
#include "Context.hpp"

class CompoundStmt
  :public Statement
{
private:
  std::vector<Statement*>* stmts;
  //std::vector<Variable_hash> vars;
  int LocalVarNr;
public:
  CompoundStmt(std::vector<Statement*>* stmts) : stmts(stmts) {LocalVarNr = 0;}
  virtual std::vector<Statement*>* getStmts() const override {return stmts;}
  virtual bool IsCompoundStmt() const override {return true;}
  //virtual std::vector<Variable_hash> getVars() const override {return vars;}
  /*void addVar(const Variable_hash& var)
  {
    vars.push_back(var);
    LocalVarNr++;
  }*/
  /*void exitScope(Statement* stmt, Context& ctxt) //parameters: outer scope
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
  }*/
  /*void enterScope(const std::vector<Variable> vars)
  {
    this->vars = vars;
  }*/

};

#endif