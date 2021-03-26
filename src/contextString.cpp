#include "../include/ast/Context.hpp"
#include <string>
#include <vector>


std::string Context::saveString(std::string str, std::ostream& Out)
{

  for(int i = 0; i< stack.size(); i++)
  {
    if(stack[i]=="$")
    {
      std::string regname = findFreeReg(Out);
      stack[i]=="\"" + str + "\"";
      for(int j = 1; j<str.size()-1; j++)
      {
        if(j!=0) stack[i+j]="1";
        Out << "li " + regname + ", " << (int)(str[j]) << std::endl;
        Out << "sw " + regname + ", " << (i+j)*4 << "($sp)" << std::endl;
      }
      Out << "addiu " + regname + ", $sp, " << (i)*4+4 << std::endl;
      Out << "srl " +regname + ", 2" << std::endl;
      return regname;
    }
  }
}
