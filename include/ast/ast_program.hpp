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
  Program() {}
  push(Function* fn) {functions.push_back(fn);}
  std::vector<Function*> getFunctions() const {return functions;}
};


#endif
