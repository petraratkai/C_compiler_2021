#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../include/ast.hpp"

/*void CodeGen(const Expression *expr, std::ofstream& Out, std::vector<Variable_hash>& variables)
{
  if(expr->IsNumberStmt())
  {
    Out<<stmt->getValue();
  }
}*/

void CodeGen(const Statement *stmt, std::ofstream& Out, std::vector<Variable_hash>* variables)
{
  if(stmt->IsNumberStmt())
  {
    Out<<stmt->getValue();
  }
  else if(stmt->IsVariableStmt())
  {
      //find variable in hash table
  }
  else if(stmt->IsReturnStmt())
  {
    //evaluate return value
    //move that value to v0
    Out << "addiu $v0, ";
    CodeGen(stmt->getRetVal(), Out, variables);
    Out << ", 0" << std::endl;

  }
  else if(stmt->IsFunctionCallStmt())
  {
    //need to save the argument registers a0-a3
    //save registers
    //need to save the return address later
    Out << "jal " + stmt->getName() << std::endl;
  }
  else if(stmt->IsCompundStmt())
  {
    std::vector<Statement*>* stmts= stmt->getStmts();
    for(int i = 0; i<stmts->size(); i++)
    {
      CodeGen((*stmts)[i], Out, variables);
    }
  }
}

void CompileFunct(const Function *funct, std::ofstream& Out)
{
  //label:
  Out << funct->getName() + ":" << std::endl;
  CompoundStmt *body = funct->getBody();
  /*for(int i = 0; i<body->size(); i++)
  {*/
    CodeGen(body, Out, funct->getVariables());
  //}
  //jump to return address
  Out<<"jr $ra" <<std::endl;
}
