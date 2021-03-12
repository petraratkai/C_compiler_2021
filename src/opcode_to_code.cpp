#include <iostream>
#include <string>

#include "../include/ast.hpp"

void opcode_to_code(const std::string& dest, const std::string& left , const std::string& right,
   const std::string& opcode, std::ostream Out)
{
  switch (opcode)
  {
    case "+":
      Out << "add " + dest + ", " + left + ", " + right << std::endl;
      break;
    case "-":
      Out << "sub " + dest + ", " + left + ", " + right << std::endl;
      break;
    case "*"
      Out << "mult " + left + ", " + right << std::endl;
      Out << "mflo " + dest << std::endl;
      break;
    case "/":
      Out << "div " + left + ", " + right << std::endl;
      Out << "mflo " + dest << std::endl;
      break;
    case "%":
      Out << "div " + left + ", " + right << std::endl;
      Out << "mfhi " + dest << std::endl;
      break;
    case "==":
      //left-right
      //Out << "sub " + dest + ", " + left + ", " + right << std::endl;
      //branch if equal to 0
      Out << "bne " + left + ", " + right + ", 8" << std::endl;
      Out << "addiu " + dest + ", " + "$zero, 0" << std::endl; //PC+4 and we set dest to 0, always executed right?
      //Out << "nop" <<std::endl; //is this valid??
      Out <<  "addiu " + dest + ", " + "$zero, 1" << std::endl; //if they were equal now set dest to 1
      break;
    case "!=":
      Out << "beq " + left + ", " + right + ", 8" << std::endl;
      Out << "addiu " + dest + ", " + "$zero, 0" << std::endl; //PC+4 and we set dest to 0, always executed right?
      //Out << "nop" <<std::endl; //is this valid??
      Out <<  "addiu " + dest + ", " + "$zero, 1" << std::endl; //if they were equal now set dest to 1
      break;
    case "<":
      Out << "slt " + dest + ", " + left + ", " + right << std::endl;
      break;
    case ">":
      Out << "slt " + dest + ", " + right + ", " + left << std::endl;
      break;
    case "<=":
      Out << "sub " + dest ", " + left + ", " + right << std::endl; //want to return 1 if dest 0 or less
      Out << "bgz " + left + ", " + right + ", 8" << std::endl;
      Out << "addiu " + dest + ", " + "$zero, 0" << std::endl; //PC+4 and we set dest to 0, always executed right?
      //Out << "nop" <<std::endl; //is this valid??
      Out <<  "addiu " + dest + ", " + "$zero, 1" << std::endl;
      break;
    case ">=":
      Out << "sub " + dest ", " + right + ", " + left << std::endl;
      Out << "bgz " + right + ", " + left + ", 8" << std::endl;
      Out << "addiu " + dest + ", " + "$zero, 0" << std::endl; //PC+4 and we set dest to 0, always executed right?
      //Out << "nop" <<std::endl; //is this valid??
      Out <<  "addiu " + dest + ", " + "$zero, 1" << std::endl;
      break;
    case "&":
      Out << "and " + dest + ", " + right + ", " + left << std::endl;
      break;
    case "|":
      Out << "or " + dest + ", " + right + ", " + left << std::endl;
      break;
    case "^":
      Out << "xor " + dest + ", " + right + ", " + left << std::endl;
      break;
    case "~":
      Out << "nor " + dest + ", " + right + ", $zero" << std::endl;
      break;
    case "<<":
      Out << "sllv " + dest + ", " + right + ", " + left << std::endl;
      break;
    case ">>":
      Out << "srlv " + dest + ", " + right + ", " + left << std::endl; //arithmetic or logical???
      break;
    /*case "&&": // logical or? if a >= 1 and b >= 1
      //Out << ""
    case "||":
      break;
    case "!":
      break;*/



  }
}
