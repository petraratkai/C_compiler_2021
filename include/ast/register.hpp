#ifndef register_hpp
#define register_hpp

#include <string>

class Register
{
private:
  std::string RegName;
  std::string varname;
  bool isused;
  bool canBeStored;
public:
  Register(const std::string& RegName, const std::string& varname ="", bool isused = false, bool canBeStored = true) : RegName(RegName), varname(varname), isused(isused), canBeStored(canBeStored) {}
  Register(const Register& reg)
  {
    RegName = reg.RegName;
    varname = reg.varname;
    isused = reg.isused;
    canBeStored = reg.canBeStored;
  }
  std::string getName() const {return RegName;}
  std::string getVarName() const {return varname;}
  void setVarName(const std::string& varname) {this->varname = varname;}
  bool isUsed() const {return isused;}
  void setIsused(bool isused) {this->isused = isused;}
  void setCanBeStored(bool canBe) {canBeStored = canBe;}
  bool CanBeStored() {return canBeStored;}

};

#endif
