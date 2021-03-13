#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../include/ast.hpp"
#include "../include/ast/Context.hpp"

static int makeNameUnq=0;

static std::string makeName(std::string base)
{
    return "." + base+"_"+std::to_string(makeNameUnq++);
}

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


  if(stmt->IsExpressionStmt())
  {
      //find variable in hash table
      CodeGenExpr((Expression*)stmt, Out, variables);
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
    variables.newVar(stmt->getVariable());
  }
  else if(stmt->IsIfElseStmt())
  {
    std::string regCond = CodeGenExpr((Expression*)stmt->getCond(), Out, variables);
    //std::string iflabel = makeName("if");
    std::string elselabel = makeName("else");
    std::string afteriflabel = makeName("afterif");
    //if cond true jump to iflabel
    //nop
    Out << "beq " + regCond + ", $zero, " +  elselabel << std::endl;
    //if there is an else jump to elselabel
    Out << "addiu $v0, $v0, 0" << std::endl; //nop
    CodeGen(stmt->getIfStmts(), Out, variables);
    Out << "j " + afteriflabel << std::endl;
    Out << "addiu $v0, $v0, 0" << std::endl;
    //jump to afterifelse
    Out << elselabel +":" << std::endl;
    if(stmt->getElseStmts()!=nullptr)
      CodeGen(stmt->getElseStmts(), Out, variables);
    Out << "j " + afteriflabel << std::endl;
    Out << "addiu $v0, $v0, 0" << std::endl;
    //jump to afterifelse
    Out << afteriflabel + ":" <<std::endl;


  }
}

void CompileFunct(const Function *funct, std::ofstream& Out)
{
  //label:
  Out << funct->getName() + ":" << std::endl;
  CompoundStmt *body = funct->getBody();
  Context ctxt;
  CodeGen(body, Out, ctxt);
  if(funct->getName()!="main")
    Out<<"jr $ra" <<std::endl; //is this correct?
}
