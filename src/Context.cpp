#include "../include/ast/Context.hpp"
//#include
void Context::moveToOriginal( const std::string& originalid, const std::string& newerid, std::ostream& Out)
{
  //we get the location from original
  Variable_hash& original = vars[findVarHashIndex(originalid)];
  Variable_hash& newer = vars[FindVarHashIndex(newerid)];
  std::string regname;
  if(newer.isInMemory())
  {


    if(original.isInMemory()) //both in memory
    {
      if(newer.getMemAddr()!=original.getMemAddr())
      {
        //load from memory lw regname from some addres
        //
        regname = findFreeReg();
        saveReg(regname, Out);
        Out<<"lw "+ regname +", " << newer.getMemAddr() <<std::endl; ///mem address should be sp +memAddr!!!!!!
        Out<<"sw " + regname + ", " << original.getMemAddr() <<std::endl;
      }
    }

    else //original in register
    {
      regname = original.getReg();
      //need to check if that register is being used, if yes, need to save the contents
      int regidx = findIndex(regname);
      if(regs[regidx].isUsed())
      {
        //save the variable from registers[regidx]
      }
      Out<<"lw "+ regname + ", " << newer.getMemAddr() <<std::endl;

    }
  }
    else //newer in register
    {
      if(original.isInMemory())
      {

      }
      else //both new and original in registers
      {

        regname = original.getReg();
        int idx = findIndex(regname);
        //need to save original
        std::string regnamenew = newer.getReg();
        Out<<"add " + regname + ", " + regnamenew + ", zero" <<std::endl;
        emptyReg(regnamenew);
      }
    }



  //locate the newer as well
  //load newer into a register
  //move the data from that register to target location
}
