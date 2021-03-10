#include <iostream>
#include <vector>

#include "../include/ast.hpp"

void insert_var(std::vector<Variable_hash>* variables, const Variable* var)
{
  Variable_hash newVar(var->getName(), var->getType());
  
}
