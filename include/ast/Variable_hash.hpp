#ifndef Variable_hash_hpp
#define Variable_hash_hpp

typedef enum VarType {IntType, VoidType, CharType, DoubleType, ShortType, LongType, FloatType, SignedType, UnsignedType, StringType} VarType;

class Variable_hash
{
  std::string name;
  VarType type;
  std::string reg; //register assigned
  int memory_address;
  bool in_memory;
public:
  Variable_hash(const std::string& name, const VarType type) : name(name), type(type) {}
  //Variable_hash(const Variable* var, std::string reg, int memory_address, bool in_memory) : name(var->getName()), type(var->getType()), reg(reg), memory_address(memory_address), in_memory(in_memory) {}
  void setlocation(const std::string& reg, int memory_address, bool in_memory) {this->reg = reg; this->memory_address= memory_address; this->in_memory = in_memory;}
  std::string getReg() const {return reg;}
  std::string getName() const {return name;}
  VarType getType() const {return type;}
  bool isInMemory() const {return in_memory;}
  int getMemAddr() const {return memory_address;}

};

#endif
