#ifndef ast_program_hpp
#define ast_program_hpp

#include "ast_function.hpp"


#include <vector>

class Program
{
private:
  std::vector<Function*> functions;
  //later enum + struct

public:
  Program(std::vector<Function*> functions) : functions(functions) {}
  std::vector<Function*> getFunctions() const {return functions;}
};


#endif
