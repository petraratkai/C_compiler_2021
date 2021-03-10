#ifndef registers_hpp
#define registers_hpp

#include <map>

typedef enum RegName {v0, v1, a0, a1, a2, a3, };

class Registers
{
private:
  //names or numbers
  std::map<RegName, Expression*> regs;
public:
  //find free reg
  //set/get
  //insert variable
};

/*class Reg
{
private:
  *Expression expr;

public:
}*/

#endif
