#include <iostream>
#include <string>

#include "../include/ast.hpp"

void opcode_to_code_float(const std::string& dest, const std::string& left , const std::string& right,
   const std::string& opcode, std::ostream&  Out, VarType type = FloatType)
{
  std::string prec;
  if(type == FloatType)
    prec = "s";
  else //double
    prec = "d";

  if(opcode =="+")
  {
      Out << "add." + prec + " " + dest + ", " + left + ", " + right << std::endl;
  }
  else if(opcode == "-")
  {
    Out << "sub." + prec + " " + dest + ", " + left + ", " + right << std::endl;
  }
  else if(opcode == "*")
  {
    Out << "mul." + prec + " " + dest + ", " + left + ", " + right << std::endl;
    //Out << "mflo " + dest << std::endl;
  }
  else if(opcode == "/")
  {
    Out << "div. " + prec + " " + dest + ", " + left + ", " + right << std::endl;
    //Out << "mflo " + dest << std::endl;
  }
  /*else if(opcode == "%")
  {
    Out << "div " + left + ", " + right << std::endl;
    Out << "mfhi " + dest << std::endl;
  } */
  else if(opcode == "==")
  {
    Out << "c.eq." + prec + " " + left + ", " + right << std::endl;
    std::string after = makeName("aftereq");
    Out << "li." + prec + " " + dest + " " + "1.0" << std::endl;
    Out << "bclt " + after << std::endl;
    Out << "nop" << std::endl;
    Out << "li." + prec + " " + dest + " " + "0.0" << std::endl;
    Out << after + ":" << std::endl;

  }
  else if(opcode == "!=")
  {
    Out << "c.eq." + prec + " " + left + ", " + right << std::endl;
    std::string after = makeName("aftereq");
    Out << "li." + prec + " " + dest + " " + "1.0" << std::endl;
    Out << "bclf " + after << std::endl;
    Out << "nop" << std::endl;
    Out << "li." + prec + " " + dest + " " + "0.0" << std::endl;
    Out << after + ":" << std::endl;
  }
  else if(opcode == "<")
  {
    Out << "c.lt." + prec + " " + left + ", " + right << std::endl;
    std::string after = makeName("afterlt");
    Out << "li." + prec + " " + dest + " " + "1.0" << std::endl;
    Out << "bclt " + after << std::endl;
    Out << "nop" << std::endl;
    Out << "li." + prec + " " + dest + " " + "0.0" << std::endl;
    Out << after + ":" << std::endl;
  }
  else if(opcode == ">")
  {
    Out << "c.lt." + prec + " " + right + ", " + left << std::endl;
    std::string after = makeName("aftergt");
    Out << "li." + prec + " " + dest + " " + "1.0" << std::endl;
    Out << "bclt " + after << std::endl;
    Out << "nop" << std::endl;
    Out << "li." + prec + " " + dest + " " + "0.0" << std::endl;
    Out << after + ":" << std::endl;
  }
  else if(opcode == "<=")
  {
    Out << "c.le." + prec + " " + left + ", " + right << std::endl;
    std::string after = makeName("afterle");
    Out << "li." + prec + " " + dest + " " + "1.0" << std::endl;
    Out << "bclt " + after << std::endl;
    Out << "nop" << std::endl;
    Out << "li." + prec + " " + dest + " " + "0.0" << std::endl;
    Out << after + ":" << std::endl;
  }
  else if(opcode == ">=")
  {
    Out << "c.lt." + prec + " " + right + ", " + left << std::endl;
    std::string after = makeName("aftergt");
    Out << "li." + prec + " " + dest + " " + "1.0" << std::endl;
    Out << "bclt " + after << std::endl;
    Out << "nop" << std::endl;
    Out << "li." + prec + " " + dest + " " + "0.0" << std::endl;
    Out << after + ":" << std::endl;
  }
  /*else if(opcode == "&")
  {
    Out << "and " + dest + ", " + left + ", " + right << std::endl;
  }
  else if(opcode=="|")
  {
    Out << "or " + dest + ", " + left + ", " + right << std::endl;
  }
  else if(opcode =="^")
  {
    Out << "xor " + dest + ", " + left + ", " + right << std::endl;
  }
  else if(opcode == "~")
  {
    Out << "nor " + dest + ", " + right + ", $zero" << std::endl;
  }
  else if(opcode == "<<")
  {
    Out << "sllv " + dest + ", " + left + ", " + right << std::endl;
  }
  else if(opcode == ">>")
  {
    Out << "srlv " + dest + ", " + left + ", " + right << std::endl; //arithmetic or logical???
  }*/
  /*else if(opcode == "&&") // logical or? if a >= 1 and b >= 1
  {
    std::string label = makeName("and");
    //std::string label2 = makeName("and2");
        Out << "addiu " + dest + ", $zero, 0" <<std ::endl;
    Out << "beq " + left + ", $zero, " + label << std::endl;
    Out << "addiu " + dest + ", $zero, 0" <<std ::endl;
    Out << "beq " + right + ", $zero, " + label << std::endl;
    Out << "addiu " + dest + ", $zero, 0" <<std ::endl;
    Out << "addiu " + dest + ", $zero, 1" << std::endl;
    Out << label + ":" << std::endl;
  }
  else if(opcode =="||")
  {
    std::string label = makeName("or");
    Out << "addiu " + dest + ", $zero, 1" <<std ::endl;
    Out << "bne " + left + ", $zero, " + label << std::endl;
    Out << "addiu " + dest + ", $zero, 1" <<std ::endl;
    Out << "bne " + right + ", $zero, " + label << std::endl;
    Out << "addiu " + dest + ", $zero, 1" <<std ::endl;
    Out << "addiu " + dest + ", $zero, 0" << std::endl;
    Out << label + ":" << std::endl;
  }*/
  else if(opcode =="!")
  {
      std::string label = makeName("notequal");
          Out << "addiu " + dest + ", $zero, 0" << std::endl;
      Out << "bne " + right + ", $zero, " + label <<std::endl; //if 0 -> need to set it to 1
      Out << "addiu " + dest + ", $zero, 0" << std::endl;
      Out << "addiu " + dest + ", $zero, 1" << std::endl;
      Out << label + ":" << std::endl;
  }

    else if(opcode == "++")
    {
      Out << "li." + prec + " " + left + " " + "1.0" << std::endl;
      Out << "add." + prec + " " + right + ", " + left + ", " + right << std::endl;
      Out << "mov." + prec + " " + dest  + ", " + right << std::endl;
    }
    else if(opcode == "--")
    {
      Out << "li." + prec + " " + left + " " + "-1.0" << std::endl;
      Out << "add." + prec + " " + right + ", " + left + ", " + right << std::endl;
      Out << "mov." + prec + " " + dest  + ", " + right << std::endl;
    }
    else if(opcode == "++post") //post Increment
    {
      Out << "li." + prec + " " + left + " " + "1.0" << std::endl;
      Out << "mov." + prec + " "+ dest  + ", " + right << std::endl;
      Out << "add." + prec + " " + right + ", " + left + ", " + right << std::endl;
    }

    else if(opcode == "--post")
    {
      Out << "li." + prec + " " + left + " " + "-1.0" << std::endl;
      Out << "mov." + prec + " "+ dest  + ", " + right << std::endl;
      Out << "add." + prec + " " + right + ", " + left + ", " + right << std::endl;
    }

  else throw ("Invalid operator!");
  }

  void assignment_to_code_float(const std::string& dest, const std::string& src,
     const std::string& opcode, std::ostream&  Out, VarType type)
  {

    std::string prec;
    if(type == FloatType)
      prec = "s";
    else //double
      prec = "d";
    if(opcode == "=")
    {
      Out << "mov." + prec + " " + dest + ", " + src << std::endl;
    }
    else if(opcode == "+=")
    {
      Out << "add." + prec + " " + dest + ", " + src <<std::endl;
    }
    else if(opcode == "-=")
    {
      Out << "sub." + prec + " " + dest + ", " + src << std::endl;
    }
    else if(opcode == "*=")
    {
      Out << "mul." + prec + " " + dest + ", " + dest + ", "+ src << std::endl; //moves to lo? UNSIGNED???!!!!
    }
    else if(opcode =="/=")
    {
      Out << "div." + prec + " " + dest + ", " + src << std::endl; //moves to lo? UNSIGNED???!!!!
    }
    /*else if(opcode =="%=")
    {
      Out << "div " + src + ", " + dest << std::endl;
      Out << "mfhi " + dest << std::endl;
    }*/
    /*else if(opcode =="<<=")
    {
      Out << "sllv " + dest + ", " + dest + ", " + src << std::endl;
    }
    else if(opcode == ">>=")
    {
      Out << "srlv " + dest + ", " + dest + ", " + src << std::endl; //arithmetic or logical???
    }*/
    /*else if(opcode == "&=")
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
    }*/



    else
    {
     throw("Invalid operator!");
   }
  }
