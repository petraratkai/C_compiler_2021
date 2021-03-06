#ifndef ast_defaultstmt_hpp
#define ast_defaultstmt_hpp

#include <vector>
#include "ast_statement.hpp"
#include "Variable_hash.hpp"
#include "Context.hpp"
#include <string>
#include "makename.hpp"

class DefaultStmt
  :public Statement
{
private:
  //Expression* cond;
  //std::vector<Statement*>* stmts;
  //std::vector<Variable_hash> vars;
  //int LocalVarNr;
  int size;
  std::string label;
public:
  DefaultStmt() {size = 1; label = makeName("default");}

  //CompoundStmt() : size(0) {LocalVarNr = 0; size = 0; stmts = NULL;}

  //virtual int getSize() const override {
  //  int i = stmts->size();
  //  int k = 0;
  //  for( int j = 0; j < i; j++ ){
  //    if((*stmts)[j]->getSize()>k)
  //      k = (*stmts)[j]->getSize();
  //    }
  //  }



  //CompoundStmt(std::vector<Statement*>* stmts, int _size) : stmts(stmts), size(_size) {LocalVarNr = 0;}
  //virtual Expression* getCond() const override {return cond;}
  virtual bool IsDefaultStmt() const override {return true;}
  virtual int getSize() const override {return size;}
  virtual std::string getLabel() const override {return label;}
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
