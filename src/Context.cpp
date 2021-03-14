#include "../include/ast/Context.hpp"
//#include
void Context::moveToOriginal( const std::string& id, Context& ctxtTo, std::ostream& Out)
{
  //we get the location from original
  Variable_hash& original = ctxtTo.variables[findVarHashIndex(id)];
  Variable_hash& newer = variables[findVarHashIndex(id)];
  std::string regname;
  if(newer.isInMemory())
  {
    if(original.isInMemory()) //both in memory
    {
      if(newer.getMemAddr()!=original.getMemAddr())
      {
        //load from memory lw regname from some addres
        regname = ctxtTo.findFreeReg();
        //saveReg(regname, Out);
        Out<<"lw "+ regname +", $sp(" << newer.getMemAddr() + ")" << std::endl; ///mem address should be sp +memAddr!!!!!!
        Out<<"sw " + regname + ", $sp(" << original.getMemAddr() +")" << std::endl;
        emptyReg(regname);
      }
    }

    else //original in register
    {
      regname = original.getReg();
      //need to check if that register is being used, if yes, need to save the contents
      int regidx = findRegIndex(regname);
      if(regs[regidx].isUsed())
      {
        //save the variable from registers[regidx] WHAT IF THE VARIABLE IS THERE FROM THE OLD CONTEXT?????
        saveReg(regname, Out);
      }
      Out<<"lw "+ regname + ", $sp(" << newer.getMemAddr() +")" <<std::endl;

    }
  }
    else //newer in register
    {
      if(original.isInMemory())
      {
        regname = newer.getReg();
        int regidx = findRegIndex(regname);
        //save register
        Out <<"sw " + regname + ", $sp(" << original.getMemAddr() + ")" <<std::endl;
        emptyReg(regname);
      }
      else //both new and original in registers
      {
        regname = original.getReg();
        //need to save original
        std::string regnamenew = newer.getReg();
        Out<<"add " + regname + ", " + regnamenew + ", $zero" <<std::endl;
        emptyReg(regnamenew);

      }
    }



  //locate the newer as well
  //load newer into a register
  //move the data from that register to target location
}
