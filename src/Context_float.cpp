#include "../include/ast/Context.hpp"

bool Context::isFEmpty(const std::string& name)
{
  for(int i = 0; i< 32; i++)
  {
    if(fregs[i].getName()==name)
      return !fregs[i].isUsed();
  }
}

std::string Context::findFreeFReg(std::ostream& Out) //finds and reserves a register
{
  int fromindx = findFRegIndex("$f4");
  int toindx = findFRegIndex("$f11");
  for(int i = fromindx; i<=toindx; i=i+2)
  {
    if (isFEmpty(fregs[i].getName()))
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
