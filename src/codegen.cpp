#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../include/ast.hpp"

std::string CodeGenExpr(const Expression *expr, std::ofstream& Out, Context& ctxt) //could return a string which is the regname
{
  //std::cout<<"Here"<<expr->getValue();
  if(expr->IsNumberStmt())
  {
    std::string regname = ctxt.InsertExpr(expr);
    Out<<"addiu " + regname + ", " + regname + ", " << expr->getValue() <<std::endl;

    return regname;
  }
  else if(expr->IsFunctionCallExpr())
  {
    //need to save the argument registers a0-a3
    //save registers
    //need to save the return address later
    Out << "jal " + expr->getName() << std::endl;
  }
}

void CodeGen(const Statement *stmt, std::ofstream& Out, std::vector<Variable_hash>* variables)
{


  if(stmt->IsVariableStmt())
  {
      //find variable in hash table
  }
  else if(stmt->IsReturnStmt())
  {
    //evaluate return value
    //move that value to v0
    std::string regname = CodeGenExpr(stmt->getRetVal(), Out, variables);
    Out<<"addiu v0, " << regname << ", 0" <<std::endl;
  }

  else if(stmt->IsCompoundStmt())
  {
    std::vector<Statement*>* stmts= stmt->getStmts();
    for(int i = 0; i<stmts->size(); i++)
    {
      CodeGen((*stmts)[i], Out, variables);
    }
  }
  else if(stmt->IsDeclarationStmt())
  {
    //need to push back to variables, find a registers
    /*Variable *var = stmt->getVar();
    Variable_hash var_hash
    insert_var(var_hash, var);*/
    //variables->push_back(


  }
}

void CompileFunct(const Function *funct, std::ofstream& Out)
{
  //label:
  Out << funct->getName() + ":" << std::endl;
  CompoundStmt *body = funct->getBody();
  CodeGen(body, Out, funct->getVariables());
  Out<<"jr $ra" <<std::endl;
}
