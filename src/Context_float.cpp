#include "../include/ast/Context.hpp"


std::string Context::findFreeFReg(std::ostream& Out) //finds and reserves a register
{
  int fromindx = findFRegIndex("$t0");
  int toindx = findFRegIndex("$s7");
  for(int i = fromindx; i<=toindx; i++)
  {
    if (isEmpty(fregs[i].getName()))
    {
      fregs[i].setVarName("");
      fregs[i].setIsused(true);
      fregs[i].setCanBeStored(false);
      return fregs[i].getName();
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
    if(fregs[idx].getName()!="" && fregs[idx].CanBeStored())
    {
      saveReg(fregs[idx].getName(), Out);
      return fregs[idx].getName();
    }
  }
  return "";
}

void Context::emptyFReg(const std::string& name) //empties register with name reg DOESN'T SAVE IT
{
  int idx = findFRegIndex(name);
  fregs[idx].setVarName("");
  fregs[idx].setIsused(false);
}
