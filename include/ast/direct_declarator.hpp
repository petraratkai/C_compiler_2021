#ifndef direct_declarator_hpp
#define direct_declarator_hpp

#include <string>
#include <vector>
#include "ast_statement.hpp"
#include "ast_expression.hpp"

class DirectDecl
{
private:
  std::string id;
  std::vector<Statement*>* parameters;
  Expression* array_size;

public:
  DirectDecl(std::string id) :id(id), parameters(nullptr), array_size(nullptr) {}
  DirectDecl(std::string id, std::vector<Statement*>* parameters) : id(id), parameters(parameters), array_size(nullptr) {}
  DirectDecl(std::string id, Expression* array_size) : id(id), parameters(nullptr), array_size(array_size) {}

  std::string getId() const {return id;}
  std::vector<Statement*>* getParams() const {return parameters;}
  Expression* getArraySize() const {return array_size;}
};


#endif
