#ifndef ast_program_hpp
#define ast_program_hpp

#include "ast_function.hpp"


#include <vector>

class Program
{
private:
  std::vector<Function*> functions;
  int size;
  //later enum + struct

public:
  Program(std::vector<Function*> functions) : functions(functions) {size =0;}
    Program(std::vector<Function*> functions, int _size) : functions(functions), size(_size) {}

  Program() {}
  void push(Function* fn) {functions.push_back(fn);}
  std::vector<Function*> getFunctions() const {return functions;}
  int getSize() const {return size;}
};


#endif
