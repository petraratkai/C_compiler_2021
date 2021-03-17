#ifndef Variable_hash_hpp
#define Variable_hash_hpp

typedef enum VarType {IntType, VoidType, CharType, DoubleType, ShortType, LongType, FloatType, SignedType, UnsignedType, StringType} VarType;
typedef enum VarStorage {AutoStorage, StaticStorage, ExternStorage, TypedefStorage, RegisterStorage, NoStorage} VarStorage;
typedef enum VarQualifier {ConstQualifer, VolatileQualifier, NoQualifier } VarQualifier;
class Variable_hash
{
  std::string name;
  VarType type;
  std::string reg; //register assigned
  int memory_address;
  bool in_memory;
  VarStorage storage;
  VarQualifier qualifier;
public:
  Variable_hash(const std::string& name, const VarType type) : name(name), type(type) {storage = NoStorage; qualifier = NoQualifier;}
  Variable_hash(const std::string& name, const VarType type, const VarQualifier qualifier) : name(name), type(type), qualifier(qualifier) {storage = NoStorage;}
  Variable_hash(const std::string& name, const VarType type, const VarStorage storage) : name(name), type(type), storage(storage) {qualifier = NoQualifier;}
  Variable_hash(const std::string& name, const VarType type, const VarQualifier qualifier, const VarStorage storage) : name(name), type(type), qualifier(qualifier), storage(storage) {}

  //Variable_hash(const Variable* var, std::string reg, int memory_address, bool in_memory) : name(var->getName()), type(var->getType()), reg(reg), memory_address(memory_address), in_memory(in_memory) {}
  Variable_hash(const Variable_hash& vh)
  {
    name = vh.name;
    type = vh.type;
    qualifier = vh.qualifier;
    storage = vh.storage;
    reg = vh.reg;
    memory_address = vh.memory_address;
    in_memory = vh.in_memory;
  }
  void setlocation(const std::string& reg, int memory_address, bool in_memory) {this->reg = reg; this->memory_address= memory_address; this->in_memory = in_memory;}
  std::string getReg() const {return reg;}
  std::string getName() const {return name;}
  VarType getType() const {return type;}
  VarQualifier getQualifier() const {return qualifier;}
  VarStorage getStorage() const {return storage;}
  bool isInMemory() const {return in_memory;}
  int getMemAddr() const {return memory_address;}

};

#endif
