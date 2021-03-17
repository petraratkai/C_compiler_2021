#ifndef direct_declarator_hpp
#define direct_declarator_hpp

#include <string>
#include <vector>
#include "ast_statement.hpp"

class DirectDecl
{
private:
  std::string id;
  std::vector<Statement*>* parameters;
  int array_size;

public:
  DirectDecl(std::string id) :id(id), parameters(nullptr), array_size(-1) {}
  DirectDecl(std::string id, std::vector<Statement*>* parameters) : id(id), parameters(parameters), array_size(-1) {}
  DirectDecl(std::string id, int array_size) : id(id), parameters(nullptr), array_size(array_size) {}

  std::string getId() const {return id;}
  std::vector<Statement*>* getParams() const {return parameters;}
  int getArraySize() const {return array_size;}
};


#endif
