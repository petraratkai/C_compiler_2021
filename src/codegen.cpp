#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

#include "../include/ast.hpp"
#include "../include/ast/Context.hpp"



std::string CodeGenExpr(Expression *expr, std::ofstream& Out, Context& ctxt) //could return a string which is the regname
{
  //std::cout<<"Here"<<expr->getValue();
  if(expr->IsNumberStmt())
  {
    std::string regname = ctxt.findFreeReg(Out);
    Out<<"addiu " + regname + ", " + "$zero" + ", " << (expr->getValue()>>16) <<std::endl;
    Out<<"sll " + regname + ", " + regname + ", 16" << std::endl;
    Out<<"addiu " + regname + ", " + "$zero" + ", " << ((expr->getValue()<<16)>>16) <<std::endl;
    return regname;
  }
  if(expr->IsCharStmt())
  {
    std::string regname = ctxt.findFreeReg(Out);
    Out << "addiu " + regname + ", $zero, " <<  (int(expr->getChar()[1])) << std::endl;
    return regname;
  }
  else if(expr->IsFloatStmt())
  {
    std::string regname = ctxt.findFreeFReg(Out);
    Out << "li.s " + regname + ", " << expr->getFValue() << std::endl;
    return regname;
  }
  else if(expr->IsDoubleStmt())
  {
    std::string regname = ctxt.findFreeFReg(Out);
    Out << "li.d " + regname + ", " << expr->getDValue() << std::endl;
    return regname;

  }
  else if(expr->IsStringStmt())
  {
    std::string regname = ctxt.saveString(expr->getString(), Out);
    return regname;
  }
  else if(expr->IsFakeVariableExpr())
  {
    //need to load it into some register
    //find a free register

    std::string regname = ctxt.loadVar(expr->getId(), Out);

    //std::string dest = ctxt.findFreeReg(Out);
    Out << "nop"<< std::endl;
    return regname; //change this!!!

    //find the variable in
  }
  else if(expr->IsFunctionCallExpr())
  {
    //need to save the argument registers a0-a3
    //save registers
    //need to save the return address later

    if(expr->getParams())
    {
    for(int i=0; i<4 && i<expr->getParams()->size(); i++) //need to calculate them + need to store them in $a0-$a1
    {
      std::string dest2 = CodeGenExpr((*expr->getParams())[i], Out, ctxt);
      Out << "addiu $a" << i << ", " + dest2 + ", 0" << std::endl;
      ctxt.emptyReg(dest2);
    }
    for(int i = 4; i<expr->getParams()->size();i++)
    {
      std::string dest2 = CodeGenExpr((*expr->getParams())[i], Out, ctxt);
      Out << "sw " + dest2 + ", " <<  i*4 -4<<"($sp)" << std::endl;
      ctxt.emptyReg(dest2);
    }

  }

  //ctxt.emptyReg(dest);
  //ctxt.storeregs(false, ctxt.FirstEmptyIndex()*4, Out);
    ctxt.storeregs(false, (8+4+1+(4+1)%2)*4, Out); //params!!
    Out << "addiu $sp, $sp, -4" << std::endl;
    Out << "jal " + expr->getName() << std::endl;
    Out << "nop" << std::endl;
    //ctxt.reloadregs(false, ctxt.FirstEmptyIndex()*4, Out);
    Out << "addiu $sp, $sp, 4" << std::endl;
    ctxt.reloadregs(false, (8+4+1+(4+1)%2)*4, Out); //+params!!!
    Out << "addiu $v0, $v0, 0" << std::endl; //nop after jump
    std::string dest = ctxt.findFreeReg(Out);
    Out << "addiu " + dest + ", $v0, 0" << std::endl;
    ctxt.emptyReg("$v0");
    return dest;
  }
  else if(expr->IsOperatorExpr())
  {
    if(!expr->IsIndexingOperator())
    {
      if(expr->getType(ctxt.getVariables())==IntType)
      {
    //call some other function
      std::string left = CodeGenExpr(expr->getLeft(), Out, ctxt);
      std::string right = CodeGenExpr(expr->getRight(), Out, ctxt);
      std::string dest = ctxt.findFreeReg(Out);
      opcode_to_code(dest, left, right, expr->getOpcode(), Out);
      ctxt.emptyReg(left);
      ctxt.emptyReg(right);
      return dest;
      }
      else if(expr->getType(ctxt.getVariables())==FloatType)
      {
      std::string left = CodeGenExpr(expr->getLeft(), Out, ctxt);
      std::string right = CodeGenExpr(expr->getRight(), Out, ctxt);
      std::string dest = ctxt.findFreeFReg(Out);
      opcode_to_code_float(dest, left, right, expr->getOpcode(), Out, FloatType);

      ctxt.emptyFReg(left);
      ctxt.emptyFReg(right);
      return dest;
      }
    else if(expr->getType(ctxt.getVariables())==DoubleType)
    {
      std::string left = CodeGenExpr(expr->getLeft(), Out, ctxt);
      std::string right = CodeGenExpr(expr->getRight(), Out, ctxt);
      std::string dest = ctxt.findFreeFReg(Out);
      opcode_to_code_float(dest, left, right, expr->getOpcode(), Out, DoubleType);
      ctxt.emptyFReg(left);
      ctxt.emptyFReg(right);
      return dest;
    }
    }
    else
    {
      std::string varname = expr->getLeft()->getId();
      int idx = ctxt.findVarHashIndex(varname);
      if(!ctxt.getVariables()[idx].isPointer())
    { //this is just for local vars
      //std::cerr<<"here";
      std::string dest = ctxt.findFreeReg(Out);
      std::string address = ctxt.findFreeReg(Out);
      ctxt.loadIndex(expr->getLeft()->getId(), address, Out); //dest has the address of the first element of the array
      std::string right = CodeGenExpr(expr->getRight(), Out, ctxt); //right has the index
      std::string size = ctxt.findFreeReg(Out);
      Out << "addiu " + size + ", $zero, 4" << std::endl; //different if not int!!
      Out << "mult " + right + ", " + size << std::endl;
      Out << "mflo " + right << std::endl;
      Out << "add " + address + ", " + address + ", " + right << std::endl; //address of the element we need
      Out << "lw " + dest + ", 0(" + address + ")" << std::endl;
      Out << "nop" << std::endl;
      ctxt.emptyReg(address);
      ctxt.emptyReg(right);
      ctxt.emptyReg(size);
      return dest;
    }
    else //it is a pointer
    {
      VarType type;
      //std::cerr<<"here";
      type = (expr->getLeft()->getType(ctxt.getVariables())==CharType ? IntType : expr->getLeft()->getType(ctxt.getVariables()));
      std::string left = CodeGenExpr(expr->getLeft(), Out, ctxt);
      std::string idx = CodeGenExpr(expr->getRight(), Out, ctxt);
      int size = sizeOf(type);
      std::string sizereg = ctxt.findFreeReg(Out);
      Out << "addiu " + sizereg + ", $zero, " << size << std::endl;
      Out << "mult " + sizereg + ", " + idx << std::endl;
      Out << "mflo " + idx << std::endl;
      Out << "sll " + left + ", " + left + ", 2" << std::endl;
      Out << "add " + idx + ", " + idx + ", " + left << std::endl;
      Out << "lw " + sizereg + ", 0" + "(" + idx + ")"<< std::endl;
      ctxt.emptyReg(idx);
      ctxt.emptyReg(left);
      return sizereg;
    }
  }
  }
  else if(expr->IsSizeOf())
  {
    Number* size;
    if(expr->getExpr())
    {
      size = new Number(sizeOf(expr->getExpr()->getType(ctxt.getVariables())));

    }
    else
    {
      size = new Number(sizeOf(expr->getKeyword()));
    }
    std::string dest = CodeGenExpr(size, Out, ctxt);
    return dest;
  }
  else if(expr->IsUnary())
  {
    if(expr->getType(ctxt.getVariables())==IntType) //or char
    {
      if(expr->getOpcode()!="&" && expr->getOpcode()!="*")
      {
        std::string src = CodeGenExpr(expr->getExpr(), Out, ctxt);
        std::string dest = ctxt.findFreeReg(Out);
        opcode_to_code(dest, "$zero", src, expr->getOpcode(), Out); //need to fix the function! or would it work?
        if(expr->getOpcode()=="++" || expr->getOpcode() == "--" || expr->getOpcode()=="++post" || expr->getOpcode()=="--post")
        {
          ctxt.saveNewVar(src, expr->getExpr()->getId(), Out);
        }
        ctxt.emptyReg(src);
        return dest;
      }
      else if(expr->getOpcode()=="&")
      {
        std::string address = ctxt.findFreeReg(Out);
        ctxt.loadIndex(expr->getExpr()->getId(), address, Out);
        Out << "srl " << address + ", 2" << std::endl;
        return address;
      }
      else //dereference
      {
        //std::cerr<<"here";
        std::string address = ctxt.loadVar(expr->getExpr()->getId(), Out);
        Out << "sll " << address + ", 2" << std::endl;
        Out << "lw " + address + ", 0(" + address + ")" << std::endl;
        Out << "nop" << std::endl;
        return address;

      }
    }
    else
    {
      std::string src = CodeGenExpr(expr->getExpr(), Out, ctxt);
      std::string dest = ctxt.findFreeFReg(Out);
      opcode_to_code_float(dest, "$zero", src, expr->getOpcode(), Out, expr->getType(ctxt.getVariables())); //need to fix the function! or would it work?
      if(expr->getOpcode()=="++" || expr->getOpcode() == "--" || expr->getOpcode()=="++post" || expr->getOpcode()=="--post")
      {
        ctxt.saveNewVar(src, expr->getExpr()->getId(), Out, expr->getType(ctxt.getVariables()));
      }
      ctxt.emptyFReg(src);
      return dest;
    }
  }
  else if(expr->IsAssignExpr())
  { /*if(expr->getLhs()->IsUnary()) std::cerr<<"exists";
    else std::cerr<<"null";*/
    if(!expr->getLhs()->IsIndexingOperator() && !(expr->getLhs()->IsUnary()))
    { //std::cerr<<"here";
      if(expr->getType(ctxt.getVariables())==IntType)
      {
      std::string src = CodeGenExpr(expr->getRhs(), Out, ctxt);
      std::string dest = CodeGenExpr(expr->getLhs(), Out, ctxt);
      assignment_to_code(dest, src, expr->getOpcode(), Out);
      ctxt.saveNewVar(dest, expr->getLhs()->getId(), Out);
      ctxt.emptyReg(src);

    //ctxt.emptyRegifExpr(src, Out);
      return dest;
      }
      else
      {
        std::string src = CodeGenExpr(expr->getRhs(), Out, ctxt);
        std::string dest = CodeGenExpr(expr->getLhs(), Out, ctxt);
        assignment_to_code_float(dest, src, expr->getOpcode(), Out, expr->getType(ctxt.getVariables()));
        ctxt.saveNewVar(dest, expr->getLhs()->getId(), Out, expr->getType(ctxt.getVariables()));
        ctxt.emptyFReg(src);
      //ctxt.emptyRegifExpr(src, Out);
        return dest;
      }
    }
    else if (expr->getLhs()->IsIndexingOperator())
    {
      //std::cerr<<"here";
      std::string src = CodeGenExpr(expr->getRhs(), Out, ctxt);

      std::string dest = ctxt.findFreeReg(Out);
      std::string address = ctxt.findFreeReg(Out);
      //std::cerr<<expr->getLhs()->getLeft()->getId();
      std::string idxReg = CodeGenExpr(expr->getLhs()->getRight(), Out, ctxt);
      ctxt.loadIndex(expr->getLhs()->getLeft()->getId(), address, Out); //absolute address of the first element
      std::string size = ctxt.findFreeReg(Out);
      Out << "addiu " + size + ", $zero, 4" << std::endl; //different if not int!!
      Out << "mult " + idxReg + ", " + size << std::endl;
      Out << "mflo " + idxReg << std::endl;
      Out << "add " + address + ", " + address + ", " + idxReg << std::endl; //address of element we need
      //Out << "sw " + src + ", 0(" + dest + ")" << std::endl;
      Out << "lw " + dest + ", 0(" + address + ")"<< std::endl;
      assignment_to_code(dest, src, expr->getOpcode(), Out);
      Out << "sw " + dest + ", 0(" + address + ")" << std::endl;
      ctxt.emptyReg(src);
      ctxt.emptyReg(address);
      ctxt.emptyReg(size);
      return dest;
    }
    else if(expr->getLhs()->IsUnary() /*&& expr->getLhs()->getOpcode() == "*"*/)
    { //std::cerr<<"here";
      std::string lhs = CodeGenExpr(expr->getLhs(), Out, ctxt);
      std::string rhs = CodeGenExpr(expr->getRhs(), Out, ctxt);
      assignment_to_code(lhs, rhs, expr->getOpcode(), Out);
      std::string address = CodeGenExpr(expr->getLhs()->getExpr(), Out, ctxt);
      Out << "sll " + address + ", 2" << std::endl;
      Out << "sw " + lhs + ", 0(" + address + ")" << std::endl;
      ctxt.emptyReg(rhs);
      ctxt.emptyReg(address);
      return lhs;
    }
  }
  /*else if(expr->IsAddressOperator())
  {
    std::string address = ctxt.findFreeReg(Out);
    ctxt.loadIndex(expr->getFakeVariable()->getId(), address, Out);
    Out << "srl " << address + ", 2" << std::endl;
    return address;
  }
  else if(expr->IsDereferenceOp())
  { //std::cerr<<"here2";
    std::string address = ctxt.loadVar(expr->getFakeVariable()->getId(), Out);
    Out << "sll " << address + ", 2" << std::endl;
    Out << "lw " + address + ", 0(" + address + ")" << std::endl;
    return address;
  }*/
  else if(expr->IsCondOperator())
  {
    std::string left = CodeGenExpr(expr->getLeft(), Out, ctxt);
    std::string middle = CodeGenExpr(expr->getMiddle(), Out, ctxt);
    std::string right = CodeGenExpr(expr->getRight(), Out, ctxt);
    std::string dest = ctxt.findFreeReg(Out);
    std::string elselabel = makeName("elselabel");
    std::string aftercond = makeName("aftercond");
    Out << "beq " + left + ", $zero, " + elselabel << std::endl;
    Out << "nop" << std::endl;
    Out << "move " << dest + ", " + middle << std::endl;
    Out << "j " + aftercond << std::endl;
    Out << "nop" << std::endl;
    Out << elselabel + ":" << std::endl;
    Out << "move " << dest + ", " + right << std::endl;
    Out << "j " + aftercond << std::endl;
    Out << "nop" << std::endl;
    Out << aftercond + ":" << std::endl;
    ctxt.emptyReg(left);
    ctxt.emptyReg(right);
    ctxt.emptyReg(middle);
    return dest;


  }
  else assert(0);
}

void CodeGen(const Statement *stmt, std::ofstream& Out, Context& variables, int memsize, int returnAddr, const std::string& beginlabel, const std::string& endlabel)
{


  if(stmt->IsExpressionStmt())
  {
      //find variable in hash table
        //fprintf(stderr, "here");
      std::string regname = CodeGenExpr((Expression*)stmt, Out, variables);
      if(((Expression*)stmt)->getType(variables.getVariables())==IntType)
        variables.emptyReg(regname);
      else
        variables.emptyFReg(regname);
  }
  else if(stmt->IsReturnStmt())
  {
    //evaluate return value
    //move that value to v0
      //fprintf(stderr, "here");
//std::cerr<<"here";
    std::string regname = CodeGenExpr((Expression*)stmt->getRetVal(), Out, variables);

    if(((Expression*)(stmt->getRetVal()))->getType(variables.getVariables())==IntType || ((Expression*)(stmt->getRetVal()))->getType(variables.getVariables())==CharType)
    {
      Out<<"addiu $v0, " << regname << ", 0" <<std::endl;
      variables.emptyReg(regname);
    }
    else
    {
      if(((Expression*)(stmt->getRetVal()))->getType(variables.getVariables())==FloatType)
        Out << "mov.s $f0, " + regname<<std::endl; //double??
      else
        Out << "mov.d $f0, " + regname<<std::endl;
      variables.emptyFReg(regname);
    }


    //if(funct->getName()!="main")
    //{
      variables.loadRetAddr(Out, returnAddr*4);

      variables.reloadregs(true, 4*4, Out);
    //}
    //else

      //need to load s0-s7 back
      //ctxt.freeMem((funct->getSize()+21+(4/*+paramssize*/)%2)*4 + (funct->getSize()%2)*4, Out); //shouldn't matter i think ?? //FIX THIS
    //(funct->getSize()+21+(4+1/*+paramssize*/)%2) + (funct->getSize()%2)
    variables.freeMem(memsize, Out); //shouldn't matter i think ?? //FIX THIS
    Out << "jr $ra" << std::endl;
    Out << "nop" << std::endl;

  return;
  }

  else if(stmt->IsBreakStmt())
  {
    Out << "j " + endlabel << std::endl;
    return;
  }
  else if(stmt->IsContinueStmt())
  {
    Out << "j " + beginlabel << std::endl;
    return;
  }
  else if(stmt->IsCaseStmt())
  {
    Out << stmt->getLabel() + ":" << std::endl;
    return;
  }
  else if(stmt->IsDefaultStmt())
  {
    Out << stmt->getLabel()+ ":" << std::endl;
    return;
  }

  else if(stmt->IsCompoundStmt())
  {
    //variables.findInMem("a"); std::cerr<<"compound"<<std::endl;
    std::vector<Statement*>* stmts= stmt->getStmts();
    std::vector<Variable_hash> gv;
    Context newCtxt(0, gv);

    newCtxt.enterScope(variables);
    //std::cerr<<"here\n";
    if(stmts)
    {
    for(int i = 0; i<stmts->size(); i++)
    {
      CodeGen((*stmts)[i], Out, newCtxt, memsize, returnAddr, beginlabel, endlabel);
//std::cerr<<"here";
    }
    }

    newCtxt.leaveScope(variables, Out);

  }
  else if(stmt->IsDeclarationStmt())
  {

    variables.newVar(stmt->getVariable(), ((Declaration*)stmt)->getType(variables.getVariables()), stmt->getArraySize(), stmt->IsPointer());



    if(stmt->getExpr()!=nullptr)
    {
      /*if(stmt->getExpr()->IsString())
      {

      }*/
        //std::cerr<<"here";
    //std::string dest = variables.findFreeReg(Out);
    std::string regname = CodeGenExpr((Expression*)(stmt->getExpr()), Out, variables);
    //Out << "add " + dest + ", " + regname + ", $zero" << std::endl;
    variables.saveNewVar(regname, stmt->getVariable(), Out, ((Declaration*)stmt)->getType(variables.getVariables()));
    //std::cerr<<"here";
    if(((Declaration*)stmt)->getType(variables.getVariables())==IntType || ((Declaration*)stmt)->getType(variables.getVariables())==CharType ) variables.emptyReg(regname);
    else variables.emptyFReg(regname);

    }
    else
    {
    //  variables.saveNewVar("$zero", stmt->getVariable(), Out);
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
    if(stmt->getElseStmts())
      Out << "beq " + regCond + ", $zero, " +  elselabel << std::endl;
    else
      Out << "beq " +  regCond + ", $zero, " + afteriflabel<< std::endl;
    variables.emptyReg(regCond);
    //if there is an else jump to elselabel
    Out << "addiu $v0, $v0, 0" << std::endl; //nop
    CodeGen(stmt->getIfStmts(), Out, variables, memsize, returnAddr, beginlabel, endlabel);
    Out << "j " + afteriflabel << std::endl;
    Out << "addiu $v0, $v0, 0" << std::endl;
    //jump to afterifelse
    if(stmt->getElseStmts())
    {
    Out << elselabel +":" << std::endl;
    //if(stmt->getElseStmts()!=nullptr)
      CodeGen(stmt->getElseStmts(), Out, variables, memsize, returnAddr, beginlabel, endlabel);
    Out << "j " + afteriflabel << std::endl;
    Out << "addiu $v0, $v0, 0" << std::endl;
    }

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
    variables.emptyReg(regCond);
    CodeGen(stmt->getCompoundStmt(), Out, variables, memsize, returnAddr, whilelabel, afterwhilelabel);
    Out << "j " + whilelabel <<std::endl;
    Out<< "addiu $zero, $zero, 0" << std::endl;
    Out << afterwhilelabel + ":" <<std::endl;
  }
  else if(stmt->IsFor())
  {
    std::string forlabel = makeName("for");
    std::string afterforlabel = makeName("afterfor");
    if(stmt->getFirst())
      CodeGen(stmt->getFirst(), Out, variables, memsize, returnAddr, "", "");
    Out << forlabel + ":" << std::endl;
    std::string regCond = CodeGenExpr((Expression*)stmt->getSecond(), Out, variables);
    Out << "beq " + regCond + ", $zero, " +  afterforlabel << std::endl;
    Out << "addiu $v0, $v0, 0" << std::endl;
    variables.emptyReg(regCond);
    CodeGen(stmt->getCompoundStmt(), Out, variables, memsize, returnAddr, "", "");
    if(stmt->getThird())
      CodeGenExpr((Expression*)stmt->getThird(), Out, variables);
    Out << "j " + forlabel <<std::endl;
    Out<< "addiu $zero, $zero, 0" << std::endl;
    Out << afterforlabel + ":" <<std::endl;
  }
  else if(stmt->IsSwitchStmt())
  {
    std::string end = makeName("switchend");
    std::string cond = CodeGenExpr((Expression*)(stmt->getCond()), Out, variables);
    CompoundStmt* body = (CompoundStmt*)(stmt->getSwitchStmts());
    std::vector<Statement*>* stmts = body->getStmts();
    //int caseidx = 0;
    for(int i = 0; i<stmts->size(); i++)
    {
      if((*stmts)[i]->IsCaseStmt())
      {
        std::string caseExpr = CodeGenExpr((Expression*)((*stmts)[i]->getCond()), Out, variables);
        Out << "beq " + caseExpr + ", " + cond + ", " + (*stmts)[i]->getLabel() << std::endl;
        Out << "nop" << std::endl;
        //caseidx++;
      }
      else if((*stmts)[i]->IsDefaultStmt())
      {
        Out << "j " + (*stmts)[i]->getLabel() << std::endl;
      }
    }
    CodeGen(body, Out, variables, memsize, returnAddr, "", end);
    Out << end + ":" << std::endl;
    return;

  }
  else throw("Invalid statement!");
}

void CompileFunct(const Function *funct, std::ofstream& Out, std::vector<Variable_hash> global_vars)
{
  //label:
  Out << funct->getName() + ":" << std::endl;

  CompoundStmt *body = funct->getBody();
  int ParamSize = funct->getParams()?funct->getParams()->size():0; //should be different with different types
  Context ctxt((funct->getSize()+21+(4+1+ParamSize)%2 + (funct->getSize()%2)), global_vars);
  //need to save return address
  //need to save registers
  //fprintf(stderr, c_str(std::to_string(funct->getSize())));
  //std::cerr<<std::to_string(funct->getSize());
//ctxt.printStack();
    int memsize = (funct->getSize()+21+(4+1+ParamSize)%2) + (funct->getSize()%2);
  Out << "addiu $t1, $sp, 0" << std::endl; //store previous stack pointer
ctxt.allocateMem((funct->getSize()+21+(4+1+ParamSize)%2) + (funct->getSize()%2), Out);
int returnAddr;
if(ParamSize<=4) returnAddr = 8 + 4;
else returnAddr = 8 + ParamSize;

//std::cerr << funct->getParams()->size();
if(funct->getParams())
  for(int i = 4; i<(funct->getParams())->size(); i++)
  {

    Out << "lw $t0, " << i*4 << "($t1)" << std::endl;
    Out << "nop" << std::endl;
    if((*(funct->getParams()))[i]->IsPointer()) Out << "srl $t0, $t0, 2" << std::endl;
    Out << "sw $t0, " << (returnAddr /*+ returnAddr%2*/ + i -4 +1)*4 << "($sp)" << std::endl;
  }
//std::cerr<<(funct->getSize()+21+(4+1+ParamSize)%2) + (funct->getSize()%2)<<std::endl;
  if(funct->getParams())
  {
    for(int i = 0; i<4 && i< ParamSize; i++)
    {
      if((*(funct->getParams()))[i]->IsPointer())
      {
        Out << "srl $a" << i <<", $a" << i << ", 2" << std::endl;
      }
      Out << "sw $a" << i << ", " << i*4 << "($sp)" << std::endl;
    }
  for(int i = 0; i<(funct->getParams())->size() && i<4; i++)
  {
    CodeGen((*funct->getParams())[i], Out, ctxt, memsize, returnAddr, "", "");
  }

  int nrOffloats = 0;
  int stackidx = 0;
  for(int i = 0; i<4 && nrOffloats<2 && i<(funct->getParams())->size(); i++)
  {
    std::string prec;
    if(((Declaration*)((*funct->getParams())[i]))->getType(ctxt.getVariables())==FloatType)
    {

      prec = "s";
      //stackidx++;
    }
     else if(((Declaration*)((*funct->getParams())[i]))->getType(ctxt.getVariables())==DoubleType)
    {
      prec = "d";
    }
    if(((Declaration*)((*funct->getParams())[i]))->getType(ctxt.getVariables())==FloatType || ((Declaration*)(*funct->getParams())[i])->getType(ctxt.getVariables())==DoubleType)
    {
    Out << "s." + prec + " $f" <<12 + nrOffloats*2 << ", " << stackidx*4 << "($sp)" << std::endl;

    }

    if(((Declaration*)((*funct->getParams())[i]))->getType(ctxt.getVariables())==FloatType)
    {
      stackidx++;
      nrOffloats++;
    }
     else if(((Declaration*)((*funct->getParams())[i]))->getType(ctxt.getVariables())==DoubleType)
    {
      stackidx += 2;
      nrOffloats++;
    }
    else if(((Declaration*)((*funct->getParams())[i]))->getType(ctxt.getVariables())==IntType)
   {
     stackidx++;
   }


  }
  }
  ctxt.setMemEmpty(returnAddr+returnAddr%2);
  if(funct->getParams())
  {
    for(int i = 4; i<funct->getParams()->size(); i++)
    {
      CodeGen((*funct->getParams())[i], Out, ctxt, memsize, returnAddr, "", "");
    }
  }


  //ctxt.allocateMem((funct->getSize()+21+(4+1+ParamSize)%2) + (funct->getSize()%2), Out); //FIX THIS

  if(funct->getName()=="main")
  {
    //ctxt.allocateMem((funct->getSize()+21+(4+1/*+paramssize*/)%2)*4 + (funct->getSize()%2)*4, Out); //FIX THIS
  }
  else
  {

    ctxt.saveRetAddr(Out, returnAddr*4); //+params size

    //need to save s0-s7
    ctxt.storeregs(true, 4*4, Out); //+params size
    //std::cerr<<"here";
    //ctxt.printStack();

  }
  //for loop for the parameters maybe?
  //ctxt.printStack();
  CodeGen(body, Out, ctxt, memsize, returnAddr, "", "");

   //is this correct?
  /*if(funct->getName()!="main")
  {
    ctxt.loadRetAddr(Out, 12*4);

    ctxt.reloadregs(true, 4*4, Out);
  }
  else
  {*/
    //need to load s0-s7 back
    //ctxt.freeMem((funct->getSize()+21+(4/*+paramssize*/)%2)*4 + (funct->getSize()%2)*4, Out); //shouldn't matter i think ?? //FIX THIS
  //}
/*ctxt.freeMem((funct->getSize()+21+(4+1/*+paramssize*///)%2) + (funct->getSize()%2), Out); //shouldn't matter i think ?? //FIX THIS
  //Out<<"jr $ra" <<std::endl;
}
