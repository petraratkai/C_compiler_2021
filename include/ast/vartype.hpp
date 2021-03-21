#ifndef vartype_hpp
#define vartype_hpp

typedef enum VarType {IntType, VoidType, CharType, DoubleType, ShortType, LongType, FloatType, SignedType, UnsignedType, StringType} VarType;
typedef enum VarStorage {AutoStorage, StaticStorage, ExternStorage, TypedefStorage, RegisterStorage, NoStorage} VarStorage;
typedef enum VarQualifier {ConstQualifer, VolatileQualifier, NoQualifier } VarQualifier;


#endif
