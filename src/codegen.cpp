#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../include/ast.hpp"
#include "../include/ast/Context.hpp"

std::string CodeGenExpr(Expression *expr, std::ofstream& Out, Context& ctxt) //could return a string which is the regname
{
  //std::cout<<"Here"<<expr->getValue();
  if(expr->IsNumberStmt())
  {
    std::string regname = ctxt.findFreeReg();
    Out<<"addiu " + regname + ", " + regname + ", " << expr->getValue() <<std::endl;

    return regname;
  }
  else if(expr->IsFakeVariableExpr())
  {
    //need to load it into some register
    //find a free register
    //std::string regname = ctxt.findFreeReg();
    std::string regname = ctxt.loadVar(expr->getId(), Out);
    return regname;
    //find the variable in
  }
  else if(expr->IsFunctionCallExpr())
  {
    //need to save the argument registers a0-a3
    //save registers
    //need to save the return address later
    Out << "jal " + expr->getName() << std::endl;
  }
  else if(expr->IsOperatorExpr())
  {
    //call some other function
    std::string left = CodeGenExpr(expr->getLeft(), Out, ctxt);
    std::string right = CodeGenExpr(expr->getRight(), Out, ctxt);
    std::string dest = ctxt.findFreeReg();
    opcode_to_code(dest, left, right, expr->getOpcode(), Out);
    return dest;
  }
  else if(expr->IsAssignExpr())
  {
    std::string src = CodeGenExpr(expr->getRhs(), Out, ctxt);
    std::string dest = CodeGenExpr(expr->getLhs(), Out, ctxt);
    assignment_to_code(src, dest, expr->getOpcode(), Out);
  }
}

void CodeGen(const Statement *stmt, std::ofstream& Out, Context& variables)
{


  if(stmt->IsVariableStmt())
  {
      //find variable in hash table
  }
  else if(stmt->IsReturnStmt())
  {
    //evaluate return value
    //move that value to v0
    std::string regname = CodeGenExpr((Expression*)stmt->getRetVal(), Out, variables);
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
    //std::string varname = stmt->getVariable();
    variables.newVar(stmt->getVariable());


  }
}

void CompileFunct(const Function *funct, std::ofstream& Out)
{
  //label:
  Out << funct->getName() + ":" << std::endl;
  CompoundStmt *body = funct->getBody();
  Context ctxt;
  CodeGen(body, Out, ctxt);
  Out<<"jr $ra" <<std::endl;
}
