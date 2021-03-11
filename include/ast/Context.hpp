#ifndef registers_hpp
#define registers_hpp

#include <map>
#include <string>
#include <vector>
#include "../ast.hpp"

const std::vector<std::string> REGNAMES = {"zero", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3",
 "s4", "s5", "s6", "s7", "t8", "t9", "gp", "sp", "fp", "ra"};

/*typedef enum RegName {zero, v0, v1, a0, a1, a2, a3, t0, t1, t2, t3, t4, t5, t6, t7, s0, s1, s2, s3, s4, s5, s6, s7, t8, t9, gp, sp, fp, ra}
RegName;*/

/*std::string RegNameToString(RegName idx)
{
   return REGNAMES[(int)idx];
}*/

class Register
{
private:
  const std::string RegName;
  Expression *Expr;
  bool isused;
public:
  Register(const std::string& RegName, Expression *Expr = nullptr, bool isused = false) : RegName(RegName), Expr(Expr), isused(isused) {}
  const std::string getName() const {return RegName;}
  Expression *getExpr() const {return Expr;}
  void setExpr(Expression *Exp_param) {Expr = Exp_param;}
  bool isUsed() const {return isused;}
  void setIsused(bool isused) {this->isused = isused;}

};

class Context
{
private:
  //names + expressions
  std::vector<Register> regs;
  std::vector<Variable_hash> variables;
public:
  //find free reg
  Context()
  {
    for(int i = 0; i<30; i++)
    {
      regs.push_back(Register(REGNAMES[i]));
    }
  }

  int findIndex(const std::string& name) const
  {
    for(int i = 0; i<regs.size(); i++)
    {
      if(REGNAMES[i] == name)
        return i;
    }
    return -1;
  }

  bool isEmpty(const std::string& name)
  {
    int indx = findIndex(name);
    return !regs[indx].isUsed();
  }

  std::string findFreeReg()
  {
    int fromindx = findIndex("t0");
    int toindx = findIndex("s7");
    for(int i = fromindx; i<=toindx; i++)
    {
      if (isEmpty(regs[i].getName()))
        return regs[i].getName();
    }
    return "";
  }
  //set/get
  //insert variable
  //free register
  void emptyReg(const std::string& name) //empties register with name reg
  {
    int idx = findIndex(name);
    regs[idx].setExpr(nullptr);
    regs[idx].setIsused(false);
  }

  std::string findVar(const Variable* var)
  {
    for(int i = 0; i<variables.size(); i++)
    {
      if(variables[i].getName()==var->getName())
        return variables[i].getReg();
    }
    return "";

  }

  void newVar(Variable* var) //only for declarations
  {
    std::string regname = findFreeReg();
    if(regname!="")
    {
      int idx = findIndex(regname);
      regs[idx].setExpr(var);
      regs[idx].setIsused(true);
      variables.push_back(Variable_hash(var, regname, 0, false));
      var->setRegname(regname);
    }
    //if no free register?
    //store something else on the stack
  }
  int findVarHashIndex(Variable* var)
  {
    for (int i = 0; i<variables.size(); i++)
    {
      if(variables[i].getName() == var->getName())
        return i;
    }
    return -1;
  }
  void removeVar(Variable* var)
  {
    std::string regname = findVar(var);
    if(regname!="")
    {
      int idx = findIndex(regname);
      regs[idx].setExpr(nullptr);
      regs[idx].setIsused(false);
      variables.erase(variables.begin()+findVarHashIndex(var));
    }
  }
  const std::string insertExpr(Expression* expr)
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
  }
};



#endif
