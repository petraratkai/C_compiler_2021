#include <string>
#include <iostream>
#include <vector>
#include "../include/ast.hpp"

int sizeOf(VarType type)
{
  if(type==IntType)
  {
    return 4;
  }
  else if(type == CharType)
  {
    return 1;
  }
  else if(type == DoubleType)
  {
    return 8;
  }
  else if(type == FloatType)
  {
    return 4;
  }
  else return -1;
}
