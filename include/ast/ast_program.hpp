#ifndef ast_program_hpp
#define ast_program_hpp

#include "ast_function.hpp"


#include <vector>

class Program
{
private:
  std::vector<Function*> functions;
  std::vector<Statement*> declarations;
  int size;

  //later enum + struct

public:
  Program(std::vector<Function*> functions/*, std::vector<Statement*> declarations*/) : functions(functions)/*, declarations(declarations)*/ {size = 0;}
 //   Program(std::vector<Function*> functions, int _size) : functions(functions), size(_size) {}

  Program() {}
  void push(Function* fn) {functions.push_back(fn);}
  void pushDecl(Statement* decl) {declarations.push_back(decl);}
  std::vector<Function*> getFunctions() const {return functions;}
  std::vector<Statement*> getDeclarations() const {return declarations;}
  int getSize() const {return size;}
};


#endif
