#include <iostream>
#include <string>

#include "../include/ast.hpp"

void opcode_to_code(const std::string& dest, const std::string& left , const std::string& right,
   const std::string& opcode, std::ostream&  Out)
{
  if(opcode =="+")
  {
      Out << "add " + dest + ", " + left + ", " + right << std::endl;
  }
  else if(opcode == "-")
  {
    Out << "sub " + dest + ", " + left + ", " + right << std::endl;
  }
  else if(opcode == "*")
  {
    Out << "mult " + left + ", " + right << std::endl;
    Out << "mflo " + dest << std::endl;
  }
  else if(opcode == "/")
  {
    Out << "div " + left + ", " + right << std::endl;
    Out << "mflo " + dest << std::endl;
  }
  else if(opcode == "%")
  {
    Out << "div " + left + ", " + right << std::endl;
    Out << "mfhi " + dest << std::endl;
  }
  else if(opcode == "==")
  {
      //left-right
      //Out << "sub " + dest + ", " + left + ", " + right << std::endl;
      //branch if equal to 0
    Out << "bne " + left + ", " + right + ", 2" << std::endl;
    Out << "addiu " + dest + ", " + "$zero, 0" << std::endl; //PC+4 and we set dest to 0, always executed right?
    //Out << "nop" <<std::endl; //is this valid??
    Out <<  "addiu " + dest + ", " + "$zero, 1" << std::endl; //if they were equal now set dest to 1
  }
  else if(opcode == "!=")
  {
    Out << "beq " + left + ", " + right + ", 8" << std::endl;
    Out << "addiu " + dest + ", " + "$zero, 0" << std::endl; //PC+4 and we set dest to 0, always executed right?
      //Out << "nop" <<std::endl; //is this valid??
    Out <<  "addiu " + dest + ", " + "$zero, 1" << std::endl; //if they were equal now set dest to 1
  }
  else if(opcode == "<")
  {
    Out << "slt " + dest + ", " + left + ", " + right << std::endl;
  }
  else if(opcode == ">")
  {
    Out << "slt " + dest + ", " + right + ", " + left << std::endl;
  }
  else if(opcode == "<=")
  {
    Out << "sub " + dest + ", " + left + ", " + right << std::endl; //want to return 1 if dest 0 or less
    Out << "bgtz " + dest + ", 8" << std::endl;
    Out << "addiu " + dest + ", " + "$zero, 0" << std::endl; //PC+4 and we set dest to 0, always executed right?
    //Out << "nop" <<std::endl; //is this valid??
    Out <<  "addiu " + dest + ", " + "$zero, 1" << std::endl;
  }
  else if(opcode == ">=")
  {
    Out << "sub " + dest + ", " + right + ", " + left << std::endl;
    Out << "bgtz " + dest + ", 8" << std::endl;
    Out << "addiu " + dest + ", " + "$zero, 0" << std::endl; //PC+4 and we set dest to 0, always executed right?
    //Out << "nop" <<std::endl; //is this valid??
    Out <<  "addiu " + dest + ", " + "$zero, 1" << std::endl;
  }
  else if(opcode == "&")
  {
    Out << "and " + dest + ", " + right + ", " + left << std::endl;
  }
  else if(opcode=="|")
  {
    Out << "or " + dest + ", " + right + ", " + left << std::endl;
  }
  else if(opcode =="^")
  {
    Out << "xor " + dest + ", " + right + ", " + left << std::endl;
  }
  else if(opcode == "~")
  {
    Out << "nor " + dest + ", " + right + ", $zero" << std::endl;
  }
  else if(opcode == "<<")
  {
    Out << "sllv " + dest + ", " + right + ", " + left << std::endl;
  }
  else if(opcode == ">>")
  {
    Out << "srlv " + dest + ", " + right + ", " + left << std::endl; //arithmetic or logical???
  }
  else if(opcode == "&&") // logical or? if a >= 1 and b >= 1
  {
    Out << "beq " + left + ", $zero, 16" << std::endl;
    Out << "addiu " + dest + ", $zero, 0" <<std ::endl;
    Out << "beq " + right + ", $zero, 8" << std::endl;
    Out << "addiu " + dest + ", $zero, 0" <<std ::endl;
    Out << "addiu " + dest + ", $zero, 1" << std::endl;
  }
  else if(opcode =="||")
  {
    Out << "bne " + left + ", $zero, 16" << std::endl;
    Out << "addiu " + dest + ", $zero, 1" <<std ::endl;
    Out << "bne " + right + ", $zero, 8" << std::endl;
    Out << "addiu " + dest + ", $zero, 1" <<std ::endl;
    Out << "addiu " + dest + ", $zero, 0" << std::endl;
  }
  else if(opcode =="!")
  {
      Out << "bne " + left + ", $zero, 8" <<std::endl; //if 0 -> need to set it to 1
      Out << "addiu " + dest + ", $zero, 0" << std::endl;
      Out << "addiu " + dest + ", $zero, 1" << std::endl;
  }
  else throw ("Invalid operator!");
  }

  void assignment_to_code(const std::string& dest, const std::string& src,
     const std::string& opcode, std::ostream&  Out)
  {
    if(opcode == "=")
    {
      Out << "addiu " + dest + ", " + src + ", 0" << std::endl;
    }
    else if(opcode == "+=")
    {
      Out << "add " + dest + ", " + dest + ", " + src <<std::endl;
    }
    else if(opcode == "-=")
    {
      Out << "sub " + dest + ", " + dest + ", " + src << std::endl;
    }
    else if(opcode == "*=")
    {
      Out << "mult " + dest + ", " + src << std::endl; //moves to lo? UNSIGNED???!!!!
      Out << "mflo " + dest << std::endl;
    }
    else if(opcode =="/=")
    {
      Out << "div " + dest + ", " + src << std::endl; //moves to lo? UNSIGNED???!!!!
      Out << "mflo " + dest << std::endl;
    }
    else if(opcode =="%=")
    {
      Out << "div " + src + ", " + dest << std::endl;
      Out << "mfhi " + dest << std::endl;
    }
    else if(opcode =="<<=")
    {
      Out << "sllv " + dest + ", " + dest + ", " + src << std::endl;
    }
    else if(opcode == ">>=")
    {
      Out << "srlv " + dest + ", " + dest + ", " + src << std::endl; //arithmetic or logical???
    }
    else if(opcode == "&=")
    {
      Out << "and " + dest + ", " + dest + ", " + src << std::endl;
    }
    else if(opcode == "|=")
    {
      Out << "or " + dest + ", " + dest + ", " + src << std::endl;
    }
    else if(opcode == "^=")
    {
      Out << "xor " + dest + ", " + dest + ", " + src << std::endl;
    }
    else if(opcode == "++post") //post Increment
    {
      Out << "addiu " + dest + ", " + src + ", 0"<< std::endl;
      Out << "addiu " + src + ", " + src + ", 1" << std::endl;
    }
    else if(opcode == "++pre")
    {
      Out << "addiu " + src + ", " + src + ", 1" << std::endl;
      Out << "addiu " + dest + ", " + src + ", 0"<< std::endl;
    }
    else if(opcode == "--post")
    {
      Out << "addiu " + dest + ", " + src + ", 0"<< std::endl;
      Out << "addiu " + src + ", " + src + ", -1" << std::endl;
    }
    else if(opcode == "--pre")
    {
      Out << "addiu " + src + ", " + src + ", -1" << std::endl;
      Out << "addiu " + dest + ", " + src + ", 0"<< std::endl;
    }
    else throw("Invalid operator!");
  }
