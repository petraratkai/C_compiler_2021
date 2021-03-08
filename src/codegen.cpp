#include <iostream>
#include <fstream>

#include "ast.hpp"

void CodeGen(const Statement *stmt, ofstream& Out)
{
  if(stmt->get_type()==Number)
  {
    Out<<stmt->getValue();
  }
  else if(stmt->get_type()==Variable)
  {
    
  }
  else if(stmt->get_type()==ReturnType)
  {
    //evaluate return value
    //move that value to v0


  }
}

void CompileFunct(const Function *funct)
{

}
