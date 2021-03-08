#ifndef ast_function_hpp
#define ast_function_hpp

#include "ast_statements.hpp"
#include <vector>
#include <string>

typedef enum VarType {Int, Void, Char, Double} VarType;


class Variable_hash
{
  std::string name;
  VarType type;
  int reg; //register assigned
  int memory_address;
  bool in_memory;
};

class Function
{
private:
  std::string name;
  std::vector<Statement> body;
  std::vector<Variable_hash> parameters;
  VarType return_type;
public:
  Function(std::string name, std::vector<Statement> body, std::vector<Variable_hash> parameters, VarType return_type) :
      name(name), body(body), parameters(parameters), return_type(return_type) {}


};




#endif
