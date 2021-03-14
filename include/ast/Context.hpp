#ifndef registers_hpp
#define registers_hpp


#include <string>
#include <vector>
#include <iostream>
//#include "../ast.hpp"
//#include "ast_statement.hpp"
#include "Variable_hash.hpp"
#include "register.hpp"


const std::vector<std::string> REGNAMES = {"$zero", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3",
 "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$gp", "$sp", "$fp", "$ra"};


class Context
{
private:
  //names + expressions
  std::vector<Register> regs;
  std::vector<Variable_hash> variables;
  int stackptrOffset;
  std::vector<std::string> stack;
  unsigned int NrOfVarsDeclared;
public:

  Context()
  {
    for(int i = 0; i<REGNAMES.size(); i++)
    {
      regs.push_back(Register(REGNAMES[i]));
    }
    this->NrOfVarsDeclared = 0;
  }
  Context(const Context& Ctxt)
  {
    regs = Ctxt.regs;
    variables = Ctxt.variables;
    stackptrOffset = Ctxt.stackptrOffset;
    stack = Ctxt.stack;
    NrOfVarsDeclared = Ctxt.NrOfVarsDeclared;
  }
  int findRegIndex(const std::string& regname) const
  {
    for(int i = 0; i<regs.size(); i++)
    {
      if(REGNAMES[i] == regname)
        return i;
    }
    throw("all registers taken!");
    return -1;
  }

  bool isEmpty(const std::string& regname)
  {
    int indx = findRegIndex(regname);
    return !regs[indx].isUsed();
  }

  std::string findFreeReg() //finds and reserves a register
  {
    int fromindx = findRegIndex("$t0");
    int toindx = findRegIndex("$s7");
    for(int i = fromindx; i<=toindx; i++)
    {
      if (isEmpty(regs[i].getName()))
      {
        regs[i].setVarName("");
        regs[i].setIsused(true);
        return regs[i].getName();

      }
    }
    return "";
  }
  //set/get
  //insert variable
  //free register
  void emptyReg(const std::string& name) //empties register with name reg DOESN'T SAVE IT
  {
    int idx = findRegIndex(name);
    regs[idx].setVarName("");
    regs[idx].setIsused(false);
  }

  /*std::string findVar(const Variable* var) //return
  {
    for(int i = 0; i<variables.size(); i++)
    {
      if(variables[i].getName()==var->getName())
        return variables[i].getReg();
    }
    return "";

  }*/

  std::string newVar(const std::string& varname) //only for declarations, adds new variable to variable hashes and reserves a register
  //then returns the reserved register name
  {
    std::string regname = findFreeReg();
    if(regname!="")
    {
      int idx = findRegIndex(regname);
      regs[idx].setVarName(varname);
      regs[idx].setIsused(true);
      variables.push_back(Variable_hash(varname, IntType));
      variables[variables.size()-1].setlocation(regname, 0, false);

    }
    return regname;
    //if no free register?
    //store something else on the stack
  }
  int findVarHashIndex(std::string varname)
  {
    for (int i = 0; i<variables.size(); i++)
    {
      if(variables[i].getName() == varname)
        return i;
    }
    return -1;
  }

  std::string loadVar(std::string varId, std::ostream& Out) //finds the variable in variables, loads from the stack, returns the resserved register
  {
    int varidx = findVarHashIndex(varId);
    if(!variables[varidx].isInMemory())
      return variables[varidx].getReg();

    std::string regname = findFreeReg();
    if(regname!="")
    {
      int idx = findRegIndex(regname);
      regs[idx].setVarName(varId);
      regs[idx].setIsused(true);
      Out<<"lw "<< regname <<", $sp(" << variables[varidx].getMemAddr()<<")"<<std::endl;
      variables[varidx].setlocation(regname, 0, false);

    }
    //if no more free registers!!
    return regname;
  }

  void removeVar(const std::string& varname) //when we leave a scope, variable is not live anymore
  {

    int varidx = findVarHashIndex(varname);
    if(varidx!=-1) //should always be the case
    {
      std::string regname = variables[varidx].getReg();
      emptyReg(regname);
      variables.erase(variables.begin()+varidx);
    }
  }
  /*const std::string insertExpr(Expression* expr)
  {
    std::string regname = findFreeReg();
    if(regname!="")
    {
      int idx = findIndex(regname);
      regs[idx].setExpr(expr);
      regs[idx].setIsused(true);
      return regname;
    }
    return "";
    //if no free register?
    //store something else on the stack
  }*/
  void saveReg(const std::string& regname,  std::ostream& Out) //probably take the stack as argument
  {
    int memAddr = 0; //has to be fixed!!
    int regidx = findRegIndex(regname);

    if(regs[regidx].getVarName()!="")
    {
      int varidx = findVarHashIndex(regs[regidx].getVarName());
      variables[varidx].setlocation("", memAddr, true);
      Out<<"sw " + regname + ", " << memAddr <<std::endl;
    }
    emptyReg(regname);
  }

  void emptyRegifExpr(const std::string& regname,  std::ostream& Out)
  {
    int regidx = findRegIndex(regname);
    if(regs[regidx].getVarName()=="" && regs[regidx].isUsed())
    {
      emptyReg(regname);
    }
  }
void moveToOriginal( const std::string& id, Context& ctxtTo, std::ostream& Out);

  void enterScope(Context& ctxtFrom) //must be called form an empty context
  {
    //need to copy all  into from
    *this = ctxtFrom;
    this->NrOfVarsDeclared = 0;
  }
  void leaveScope(Context& ctxtTo, std::ostream& Out) //ctxtFrom won't be used anymore
  {
    //have to delete everything from this : last few variables
    //then put everything back to where they were in ctxt to
    for(int i = NrOfVarsDeclared; i>0; i++)
    {
      if(!variables[ctxtTo.variables.size()+NrOfVarsDeclared-1].isInMemory()) emptyReg(variables[ctxtTo.variables.size()+NrOfVarsDeclared-1].getReg());
      variables.erase(variables.begin()+ctxtTo.variables.size()+NrOfVarsDeclared-1);
    }
    ctxtTo = *this;
    /*for(int i = 0; i<variables.size(); i++)
    {
      moveToOriginal(variables[i].getName(), ctxtTo, Out);
    }*/

  }


};



#endif
