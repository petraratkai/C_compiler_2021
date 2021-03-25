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
  bool pointer;

public:
  DirectDecl(std::string id) :id(id), parameters(nullptr), array_size(nullptr) { pointer = false;}
  DirectDecl(std::string id, std::vector<Statement*>* parameters) : id(id), parameters(parameters), array_size(nullptr) {pointer = false;}
  DirectDecl(std::string id, Expression* array_size) : id(id), parameters(nullptr), array_size(array_size) {pointer = false;}
  DirectDecl(std::string id, bool pointer) :id(id), pointer(pointer), parameters(nullptr), array_size(nullptr) {}
  DirectDecl(std::string id, std::vector<Statement*>* parameters, bool pointer) : id(id), pointer(pointer), parameters(parameters), array_size(nullptr) {}
  DirectDecl(std::string id, Expression* array_size, bool pointer) : id(id), pointer(pointer), parameters(nullptr), array_size(array_size) {}

  std::string getId() const {return id;}
  std::vector<Statement*>* getParams() const {return parameters;}
  bool IsPointer() const {return pointer;}
  Expression* getArraySize() const {return array_size;}
};


#endif
