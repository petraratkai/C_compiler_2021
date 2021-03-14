#ifndef ast_function_hpp
#define ast_function_hpp

#include <vector>
#include <string>



class Function
{
private:
  std::string name;
  CompoundStmt* body;
  std::vector<Statement*>* parameters;
  VarType return_type;
  std::vector<Variable_hash>* local_variables;
public:
  Function(const std::string& name, CompoundStmt* body, std::vector<Statement*>* parameters, VarType return_type) :
      name(name), body(body), parameters(parameters), return_type(return_type) {}
  CompoundStmt* getBody() const {return body;}

  std::string getName() const {return name;}

  std::vector<Variable_hash>* getVariables() const {return local_variables;}


};




#endif
