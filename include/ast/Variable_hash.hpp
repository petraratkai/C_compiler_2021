#ifndef Variable_hash_hpp
#define Variable_hash_hpp

typedef enum VarType {IntType, VoidType, CharType, DoubleType, ShortType, LongType, FloatType, SignedType, UnsignedType, StringType} VarType;
typedef enum VarStorage {AutoStorage, StaticStorage, ExternStorage, TypedefStorage, RegisterStorage} VarStorage;
typedef enum VarQualifier {ConstQualifer, VolatileQualifier} VarQualifier;
class Variable_hash
{
  std::string name;
  VarType type;
  std::string reg; //register assigned
  int memory_address;
  bool in_memory;
  bool is_global;
public:
  Variable_hash(const std::string& name, const VarType type, bool is_global=false) : name(name), type(type), is_global(is_global) {}
  //Variable_hash(const Variable* var, std::string reg, int memory_address, bool in_memory) : name(var->getName()), type(var->getType()), reg(reg), memory_address(memory_address), in_memory(in_memory) {}
  Variable_hash(const Variable_hash& vh)
  {
    name = vh.name;
    type = vh.type;
    reg = vh.reg;
    memory_address = vh.memory_address;
    in_memory = vh.in_memory;
    is_global = vh.is_global;
  }
  void setlocation(const std::string& reg, int memory_address, bool in_memory) {this->reg = reg; this->memory_address= memory_address; this->in_memory = in_memory;}
  std::string getReg() const {return reg;}
  std::string getName() const {return name;}
  VarType getType() const {return type;}
  bool isInMemory() const {return in_memory;}
  int getMemAddr() const {return memory_address;}
  bool isGlobal() const {return is_global;}

};

#endif
