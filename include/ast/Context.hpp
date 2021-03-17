#ifndef registers_hpp
#define registers_hpp


#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "../ast.hpp"
//#include "ast_statement.hpp"
#include "Variable_hash.hpp"
#include "register.hpp"


const std::vector<std::string> REGNAMES = {"$zero", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9", "$s0", "$s1", "$s2", "$s3",
 "$s4", "$s5", "$s6", "$s7", "$gp", "$sp", "$fp", "$ra"};

//static int exprNr = 0;

class Context
{
private:
  //names + expressions
  std::vector<Register> regs;
  std::vector<Variable_hash> variables;
  int stackptrOffset; //???
  int sizeOfStack;
  std::vector<std::string> stack; //fixed size, never push back!
  unsigned int NrOfVarsDeclared;
public:

  Context(int sizeOfStack, std::vector<Variable_hash> global_vars)
  {
    for(int i = 0; i<REGNAMES.size(); i++)
    {
      regs.push_back(Register(REGNAMES[i]));
    }
    this->NrOfVarsDeclared = 0;
    for(int i = 0; i<sizeOfStack; i++)
    {
      stack.push_back("0");
    }
    variables = global_vars;
  }
  Context(const Context& Ctxt)
  {
    regs = Ctxt.regs;
    variables = Ctxt.variables;
    stackptrOffset = Ctxt.stackptrOffset;
    sizeOfStack = Ctxt.sizeOfStack;
    stack = Ctxt.stack;
    NrOfVarsDeclared = Ctxt.NrOfVarsDeclared;
  }
  Context& operator=(const Context& Ctxt)
  {
    regs = Ctxt.regs;
    variables = Ctxt.variables;
    stackptrOffset = Ctxt.stackptrOffset;
    sizeOfStack = Ctxt.sizeOfStack;
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

  void saveRetAddr(std::ostream& Out, int offset)
  {
    Out << "sw $ra, "<< offset << "($sp)" << std::endl;
    stack[offset/4]="$ra";
    //std::cerr<<"hello";
  }

  void loadRetAddr(std::ostream& Out, int offset)
  {
    Out << "lw $ra, "<<offset <<"($sp)" << std::endl;
  }

  void storeregs(bool savedReg, int offset, std::ostream& Out) //offset = first index in stack to save the registers
  {
    std::string fromreg, toreg;

    if(savedReg)
    {
      fromreg = "$s0";
      toreg = "$s7";
    }
    else
    {
      fromreg = "$t0";
      toreg = "$t9";
    }
          //std::cerr<<"here";
    int fromidx = findRegIndex(fromreg);
    int toidx = findRegIndex(toreg);
    int j = 0;

    for(int i = fromidx; i<=toidx; i++)
    {
      Out<<"sw " + REGNAMES[i] + ", " << offset + j << "($sp)" << std::endl;
      j+=4;
      //set the name in the stack!!
      if(savedReg)
      {
        stack[offset/4+i-fromidx] = "$s";
      }
      else
      {
        stack[offset/4+i-fromidx] ="$t";
      }
    }

  }

  void reloadregs(bool savedReg, int offset, std::ostream& Out)
  {
    std::string fromreg, toreg;
    if(savedReg)
    {
      fromreg = "$s0";
      toreg = "$s7";
    }
    else
    {
      fromreg = "$t0";
      toreg = "$t9";
    }
    int fromidx = findRegIndex(fromreg);
    int toidx = findRegIndex(toreg);
    int j = 0;
    for(int i = fromidx; i<=toidx; i++)
    {
      Out<<"lw " + REGNAMES[i] + ", " << offset + j << "($sp)" << std::endl;
      j+=4;
      //set the name in the stack!!
        stack[offset/4+i-fromidx] = "";
    }
  }


  bool isEmpty(const std::string& regname)
  {
    int indx = findRegIndex(regname);
    return !regs[indx].isUsed();
  }

  void allocateMem(int words, std::ostream& Out)
  {
    Out << "addiu $sp, $sp, " << (-1)*words*4 << std::endl;
    for(int i = 0; i<words; i++)
    {
      stack[i]="0";
    }
  }
  void freeMem(int words, std::ostream& Out)
  {
    Out << "addiu $sp, $sp, " << words*4 << std::endl;
    for(int i = 0; i<words; i++)
    {
      stack[i]="";
    }
  }
  void saveNewVar(const std::string& regname, const std::string& varName, std::ostream& Out)
  {
    //int regidx = findRegIndex(regname);
    int varidx = findVarHashIndex(varName);
    Out<<"sw " + regname + ", " << (variables[varidx].getMemAddr())*4 << "($sp)" <<std::endl;
  }
  void saveVar(const std::string& regname, std::ostream& Out)
  {
    int regidx = findRegIndex(regname);

    std::string varName = regs[regidx].getVarName();
    int varidx = findVarHashIndex(varName);
    if(!variables[varidx].isGlobal())
    {
    Out<<"sw " + regname + ", " << (variables[varidx].getMemAddr())*4 << "($sp)" <<std::endl;
    }
    else
    {
      std::string address = findFreeReg(Out);
      Out << "la " + address + ", " + variables[varidx].getName() << std::endl;
      Out << "sw " + regname + ", " + "0(" + address + ")" << std::endl; 
    }
    //emptyReg(regname);
  }
  void saveReg(const std::string& regname,  std::ostream& Out) //probably take the stack as argument
  {
    int spOffset; //has to be fixed!!
    bool found = false;
    int i = 0;
    while(!found)
    {
      if(stack[i] == "")
      {
        found = true;
        spOffset = i;
      }
    }

    int regidx = findRegIndex(regname);

    if(regs[regidx].getVarName()!="")
    {
      stack[spOffset] = regs[regidx].getVarName();
      int varidx = findVarHashIndex(regs[regidx].getVarName());
      variables[varidx].setlocation("", spOffset, true);
      Out<<"sw " + regname + ", " << spOffset*4 << "($sp)" <<std::endl;
    }
    emptyReg(regname);
  }

  std::string findFreeReg(std::ostream& Out) //finds and reserves a register
  {
    int fromindx = findRegIndex("$t0");
    int toindx = findRegIndex("$s7");
    for(int i = fromindx; i<=toindx; i++)
    {
      if (isEmpty(regs[i].getName()))
      {
        regs[i].setVarName("");
        regs[i].setIsused(true);
        regs[i].setCanBeStored(false);
        return regs[i].getName();
      }
    }
    //if not empty?
    //chose a register that contains a variable
    bool done = false;
    srand (time(NULL));
    int idx;
    while(!done)
    {
      //pick a random number
      idx = rand() % (toindx-fromindx) + fromindx;
      if(regs[idx].getName()!="" && regs[idx].CanBeStored())
      {
        saveReg(regs[idx].getName(), Out);
        return regs[idx].getName();
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

  void newVar(const std::string& varname) //only for declarations, adds new variable to variable hashes and reserves a register
  //then returns the reserved register name
  {

    variables.push_back(Variable_hash(varname, IntType));
    bool found = false;
    int i = 0;
    while(i<stack.size())
    {
      if(stack[i]=="0")
      {
        stack[i]=varname;
        found = true;
        variables[variables.size()-1].setlocation("", i, true);
        NrOfVarsDeclared++;

        return;
      }
      i++;
    }
    //variables[variables.size()-1].setlocation("", NrOfVarsDeclared, true);
      /*std::cerr<<"newvar\n";
      for(int j = 0; j< stack.size(); j++)
      {
        std::cerr<<stack[j] + " ";
      }*/
    //stack[NrOfVarsDeclared] = varname;
    //NrOfVarsDeclared++;
    /*std::string regname = findFreeReg(Out);
    if(regname!="")
    {
      int idx = findRegIndex(regname);
      regs[idx].setVarName(varname);
      regs[idx].setIsused(true);
      variables.push_back(Variable_hash(varname, IntType));
      variables[variables.size()-1].setlocation(regname, 0, false);

    }
    return regname;*/
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
    /*if(!variables[varidx].isInMemory()) //should not need
    { std::cerr<<"loadVar shouldn't get here "<<varId;
      return variables[varidx].getReg();

    }*/ //std::cerr<<varidx<<std::endl;
    std::string regname = findFreeReg(Out);
    if(regname!="")
    {
      int idx = findRegIndex(regname);
      regs[idx].setVarName(varId); //shouldn't need
      regs[idx].setIsused(true);
      if(!variables[varidx].isGlobal())
      {
      Out<<"lw "<< regname <<", " << (variables[varidx].getMemAddr()) * 4<<"($sp)"<<std::endl; //+offset!!!!
      }
      //variables[varidx].setlocation(regname, 0, false);
      else
      {
        Out<<"lw "<< regname <<", " << variables[varidx].getName() << std::endl;
      }

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


  void emptyRegifExpr(const std::string& regname,  std::ostream& Out)
  {
    int regidx = findRegIndex(regname);
    if(regs[regidx].getVarName()=="" && regs[regidx].isUsed() && regs[regidx].CanBeStored())
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
  int findInMem(std::string varname)
  {
    for(int i = 0; i<stack.size(); i++)
    {
      if(stack[i]== varname)
        return i;
    }
    std::cout<<varname + "not in mem";
    return 0;
  }
  void leaveScope(Context& ctxtTo, std::ostream& Out) //ctxtFrom won't be used anymore
  {
    //have to delete everything from this : last few variables
    //then put everything back to where they were in ctxt to
    //std::cerr<<NrOfVarsDeclared;
    for(int i = NrOfVarsDeclared; i>0; i--)
    {

      if(!variables[ctxtTo.variables.size()+i-1].isInMemory())
      {
        emptyReg(variables[ctxtTo.variables.size()+i-1].getReg());
      }
      else
      {//it is in memory

        int idxInStack = findInMem(variables[ctxtTo.variables.size()+i-1].getName());
        stack[idxInStack] = "0";
      }
      variables.erase(variables.begin()+ctxtTo.variables.size()+i-1);
    }
    ctxtTo = *this;
    /*for(int i = 0; i<variables.size(); i++)
    {
      moveToOriginal(variables[i].getName(), ctxtTo, Out);
    }*/

  }


};



#endif
