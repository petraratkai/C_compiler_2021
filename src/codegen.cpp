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
    std::string regname = ctxt.findFreeReg(Out);
    Out<<"addiu " + regname + ", " + "$zero" + ", " << expr->getValue() <<std::endl;
    return regname;
  }
  else if(expr->IsFakeVariableExpr())
  {
    //need to load it into some register
    //find a free register
    std::string regname = ctxt.loadVar(expr->getId(), Out);
    //std::string dest = ctxt.findFreeReg(Out);
    //Out << "add " + dest + ", " + regname + ", $zero" << std::endl;
    return regname; //change this!!!
    //find the variable in
  }
  else if(expr->IsFunctionCallExpr())
  {
    //need to save the argument registers a0-a3
    //save registers
    //need to save the return address later
    std::string dest = ctxt.findFreeReg(Out);
    //std::cerr<<dest;
    ctxt.storeregs(false, (8+4+1+(4+1)%2)*4, Out); //params!!
    Out << "jal " + expr->getName() << std::endl;
    ctxt.reloadregs(false, (8+4+1+(4+1)%2)*4, Out); //+params!!!
    Out << "addiu $v0, $v0, 0" << std::endl; //nop after jump
    Out << "addiu " + dest + ", $v0, 0" << std::endl;

    return dest;
  }
  else if(expr->IsOperatorExpr())
  {
    //call some other function
    std::string left = CodeGenExpr(expr->getLeft(), Out, ctxt);
    std::string right = CodeGenExpr(expr->getRight(), Out, ctxt);
    std::string dest = ctxt.findFreeReg(Out);
    opcode_to_code(dest, left, right, expr->getOpcode(), Out);
    ctxt.emptyRegifExpr(left, Out);
    ctxt.emptyRegifExpr(right, Out);
    return dest;
  }
  else if(expr->IsUnary())
  {
    std::string src = CodeGenExpr(expr->getExpr(), Out, ctxt);
    std::string dest = ctxt.findFreeReg(Out);
    opcode_to_code(dest, "$zero", src, expr->getOpcode(), Out); //need to fix the function! or would it work?
    ctxt.emptyRegifExpr(src, Out);
    return dest;
  }
  else if(expr->IsAssignExpr())
  {

    std::string src = CodeGenExpr(expr->getRhs(), Out, ctxt);
    std::string dest = CodeGenExpr(expr->getLhs(), Out, ctxt);
    assignment_to_code(dest, src, expr->getOpcode(), Out);
    ctxt.emptyRegifExpr(src, Out);
    return dest;
  }
  else throw("Invalid expression!");
}

void CodeGen(const Statement *stmt, std::ofstream& Out, Context& variables)
{


  if(stmt->IsExpressionStmt())
  {
      //find variable in hash table
        //fprintf(stderr, "here");
      std::string regname = CodeGenExpr((Expression*)stmt, Out, variables);
      variables.emptyRegifExpr(regname, Out);
  }
  else if(stmt->IsReturnStmt())
  {
    //evaluate return value
    //move that value to v0
      //fprintf(stderr, "here");
    std::string regname = CodeGenExpr((Expression*)stmt->getRetVal(), Out, variables);
    Out<<"addiu $v0, " << regname << ", 0" <<std::endl;
    variables.emptyRegifExpr(regname, Out);
  }

  else if(stmt->IsCompoundStmt())
  {
    std::vector<Statement*>* stmts= stmt->getStmts();
    Context newCtxt(0);
    newCtxt.enterScope(variables);
    for(int i = 0; i<stmts->size(); i++)
    {
      CodeGen((*stmts)[i], Out, newCtxt);

    }
    newCtxt.leaveScope(variables, Out);
  }
  else if(stmt->IsDeclarationStmt())
  {
    std::string dest = variables.newVar(stmt->getVariable(), Out);
    if(stmt->getExpr()!=nullptr)
    {
    std::string regname = CodeGenExpr((Expression*)(stmt->getExpr()), Out, variables);
    Out << "add " + dest + ", " + regname + ", $zero" << std::endl;
    variables.emptyReg(regname);
    }
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
    variables.emptyRegifExpr(regCond, Out);
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
  else if(stmt->IsWhile())
  {
    std::string whilelabel = makeName("while");
    std::string afterwhilelabel = makeName("afterwhile");
    Out << whilelabel + ":" << std::endl;
    std::string regCond = CodeGenExpr((Expression*)stmt->getCond(), Out, variables);
    Out << "beq " + regCond + ", $zero, " +  afterwhilelabel << std::endl;
    Out << "addiu $v0, $v0, 0" << std::endl;
    variables.emptyRegifExpr(regCond, Out);
    CodeGen(stmt->getCompoundStmt(), Out, variables);
    Out << "j " + whilelabel <<std::endl;
    Out<< "addiu $zero, $zero, 0" << std::endl;
    Out << afterwhilelabel + ":" <<std::endl;
  }
  else throw("Invalid statement!");
}

void CompileFunct(const Function *funct, std::ofstream& Out)
{
  //label:
  Out << funct->getName() + ":" << std::endl;
  CompoundStmt *body = funct->getBody();
  Context ctxt((funct->getSize()+21+(4/*+paramssize*/)%2)*4);
  //need to save return address
  //need to save registers
  //fprintf(stderr, c_str(std::to_string(funct->getSize())));
  //std::cerr<<std::to_string(funct->getSize());
  ctxt.allocateMem((funct->getSize()+21+(4+1/*+paramssize*/)%2) + (funct->getSize()%2), Out); //FIX THIS
  if(funct->getName()=="main")
  {
    //ctxt.allocateMem((funct->getSize()+21+(4+1/*+paramssize*/)%2)*4 + (funct->getSize()%2)*4, Out); //FIX THIS
  }
  else
  {
    ctxt.saveRetAddr(Out, 12*4); //+params size
    //need to save s0-s7
    ctxt.storeregs(true, 4*4, Out); //+params size
  }
  //for loop for the parameters maybe?
  CodeGen(body, Out, ctxt);

   //is this correct?
  if(funct->getName()!="main")
  {
    ctxt.loadRetAddr(Out, 12*4);

    ctxt.reloadregs(true, 4*4, Out);
  }
  else
  {
    //need to load s0-s7 back
    //ctxt.freeMem((funct->getSize()+21+(4/*+paramssize*/)%2)*4 + (funct->getSize()%2)*4, Out); //shouldn't matter i think ?? //FIX THIS
  }
  ctxt.freeMem((funct->getSize()+21+(4+1/*+paramssize*/)%2) + (funct->getSize()%2), Out); //shouldn't matter i think ?? //FIX THIS
  Out<<"jr $ra" <<std::endl;
}
