#ifndef ast_function_hpp
#define ast_function_hpp

#include "ast_statements.hpp"
#include <vector>
#include <string>





class Variable_hash
{
  std::string name;
  VarType type;
  int reg; //register assigned
  int memory_address;
  bool in_memory;
public:
  Variable_hash(const std::string& name, const VarType type) : name(name), type(type) {}
  void setlocation(int reg, int memory_address, bool in_memory);
};

class Function
{
private:
  std::string name;
  CompoundStmt* body;
  std::vector<Declaration*>* parameters;
  VarType return_type;
  std::vector<Variable_hash>* local_variables;
public:
  Function(const std::string& name, CompoundStmt* body, std::vector<Declaration*>* parameters, VarType return_type) :
      name(name), body(body), parameters(parameters), return_type(return_type) {}
  CompoundStmt* getBody() const {return body;}

  std::string getName() const {return name;}

  std::vector<Variable_hash>* getVariables() const {return local_variables;}


};




#endif
